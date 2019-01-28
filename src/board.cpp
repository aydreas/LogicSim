#include <thread>
#include <chrono>
#include "board.h"
#include "component.h"
#include "spinlock_barrier.h"
#include "events.h"
#include "output.h"
#include <iostream>

Board::Board()
{
}

void Board::init(Component** components, Link** links, int componentCount, int linkCount)
{
	Board::init(components, links, componentCount, linkCount, 1, false);
}

void Board::init(Component** components, Link** links, int componentCount, int linkCount, bool manualClock)
{
	Board::init(components, links, componentCount, linkCount, 1, manualClock);
}

void Board::init(Component** components, Link** links, int componentCount, int linkCount, int threadCount)
{
	Board::init(components, links, componentCount, linkCount, threadCount, false);
}

void Board::init(Component** components, Link** links, int componentCount, int linkCount, int threadCount, bool manualClock)
{
	if (currentState != Board::Uninitialized)
		return;

	this->components = components;
	this->links = links;
	this->threadCount = threadCount;
	this->manualClock = manualClock;
	this->componentCount = componentCount;
	this->linkCount = linkCount;

	buffer1 = new bool[componentCount] { 0 };
	buffer2 = new bool[componentCount] { 0 };
	buffer3 = new bool[componentCount] { 0 };

	readBuffer = Board::buffer1;
	writeBuffer = Board::buffer2;
	wipeBuffer = Board::buffer3;
	
	currentState = Board::Stopped;

	threads = new std::thread*[threadCount] { nullptr };
	lastCapture = std::chrono::high_resolution_clock::now();

	barrier = new SpinlockBarrier(threadCount, [this]() {
		if (currentState == Board::Stopping) {
			currentState = Board::Stopped;
			return;
		}
		
		tickEvent.emit(nullptr, Events::EventArgs());

		bool* readPointer(readBuffer);

		readBuffer = writeBuffer;
		writeBuffer = wipeBuffer;
		wipeBuffer = readPointer;

		if (getManualClock()) {
			//TODO: wait for confirmation
		}

		tick++;
		long long diff = (std::chrono::high_resolution_clock::now() - lastCapture).count();
		if (diff > 10e8) {
			currentSpeed = ((tick - lastCaptureTick) * (unsigned long)10e8) / diff;
			lastCapture = std::chrono::high_resolution_clock::now();
			lastCaptureTick = tick;
		}
	});
}

unsigned int Board::getNextComponentIndex()
{
	return componentIndex++;
}

int Board::getThreadCount() {
	return threadCount;
}

Component** Board::getComponents() {
	return components;
}

Link** Board::getLinks()
{
	return links;
}

bool Board::getManualClock() {
	return manualClock;
}

Board::State Board::getCurrentState() {
	return currentState;
}

unsigned long long int Board::getCurrentTick()
{
	return tick;
}

void Board::stop() {
	if (currentState != Board::Running)
		return;

	currentState = Board::Stopping;
	for (int i = 0; i < threadCount; i++) {
		threads[i]->join();
	}
}

void Board::start() {
	if (currentState != Board::Stopped)
		return;

	for (int i = 0; i < threadCount; i++) {
		if(threads[i] != nullptr)
			delete threads[i];

		currentState = Board::Running;
		threads[i] = new std::thread([this](int id) {
			while (true) {
				if (currentState == Board::Stopped)
					return;

				for (int i = id; i < componentCount; i +=threadCount) {
					if (readBuffer[i])
						components[i]->compute();
					wipeBuffer[i] = false;
				}
				barrier->wait();
			}
		}, i);
	}
}
