#include <thread>
#include <chrono>
#include <algorithm>
#include "board.h"
#include "component.h"
#include "link.h"
#include "spinlock_barrier.h"
#include "events.h"
#include "output.h"

Board::Board() {
}

Board::~Board() {
	stop();

	for (int i = 0; i < componentCount; i++) {
		delete components[i];
	}
	delete[] components;

	for (int i = 0; i < linkCount; i++) {
		delete links[i];
	}
	delete[] links;

	for (int i = 0; i < threadCount; i++) {
		delete threads[i];
	}
	delete[] threads;

	delete barrier;
	delete[] buffer1;
	delete[] buffer2;
	delete[] buffer3;
}

void Board::init(Component** components, Link** links, int componentCount, int linkCount)
{
	Board::init(components, links, componentCount, linkCount, 1);
}

void Board::init(Component** components, Link** links, int componentCount, int linkCount, int threadCount)
{
	if (currentState != Board::Uninitialized)
		return;

	this->components = components;
	this->links = links;
	this->threadCount = threadCount;
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
		tickEvent.emit(nullptr, Events::EventArgs());

		bool* readPointer(readBuffer);

		readBuffer = writeBuffer;
		writeBuffer = wipeBuffer;
		wipeBuffer = readPointer;

		tick++;
		long long diff = (std::chrono::high_resolution_clock::now() - lastCapture).count();
		if (diff > 10e8) {
			currentSpeed = ((tick - lastCaptureTick) * (unsigned long)10e8) / diff;
			lastCapture = std::chrono::high_resolution_clock::now();
			lastCaptureTick = tick;
		}

		if (!--cyclesLeft || currentState == Board::Stopping) {
			currentState = Board::Stopped;
			return;
		}
	}, 2);
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
	start(UINT64_MAX);
}

void Board::start(unsigned long long cyclesLeft)
{
	if (currentState != Board::Stopped)
		return;

	this->cyclesLeft = cyclesLeft;
	for (int i = 0; i < threadCount; i++) {
		if (threads[i] != nullptr)
			delete threads[i];

		currentState = Board::Running;
		threads[i] = new std::thread([this](int id) {
			while (true) {
				if (currentState == Board::Stopped)
					return;

				for (int i = id; i < componentCount; i += threadCount) {
					if (readBuffer[i])
						components[i]->compute();
					wipeBuffer[i] = false;
				}
				barrier->wait();

				for (int i = id; i < linkCount; i += threadCount) {
					links[i]->powered = std::any_of(links[i]->outputs, links[i]->outputs + links[i]->outputCount, [](Output* x) { return x->getPowered(); });
				}
				barrier->wait();
			}
		}, i);
	}
}
