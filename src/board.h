#pragma once
#include <thread>
#include <chrono>
#include <atomic>
#include "events.h"

class Component;
class SpinlockBarrier;
class Link;

class Board
{
public:
	Board();
	void init(Component** components, Link** links, int componentCount, int linkCount);
	void init(Component** components, Link** links, int componentCount, int linkCount, int threadCount);
	void init(Component** components, Link** links, int componentCount, int linkCount, bool manualClock);
	void init(Component** components, Link** links, int componentCount, int linkCount, int threadCount, bool manualClock);
	unsigned int getNextComponentIndex();
	bool* readBuffer = nullptr;
	bool* writeBuffer = nullptr;
	bool* wipeBuffer = nullptr;
	size_t componentCount = 0;
	size_t linkCount = 0;
	enum State { Uninitialized, Stopped, Running, Stopping };
	int getThreadCount();
	Component** getComponents();
	Link** getLinks();
	State getCurrentState();
	unsigned long long int getCurrentTick();
	unsigned long long currentSpeed = 0;
	Events::Event<> tickEvent;
	void stop();
	void start();
	void start(unsigned long long cyclesLeft);
	
private:
	bool* buffer1 = nullptr;
	bool* buffer2 = nullptr;
	bool* buffer3 = nullptr;
	int threadCount = 1;
	Component** components = nullptr;
	Link** links = nullptr;
	State currentState = Board::Uninitialized;
	unsigned long long int tick = 0;
	std::thread** threads = nullptr;
	SpinlockBarrier* barrier = nullptr;
	std::chrono::high_resolution_clock::time_point lastCapture;
	unsigned long long int lastCaptureTick = 0;
	unsigned int componentIndex = 0;
	unsigned long long cyclesLeft = 0;
};

