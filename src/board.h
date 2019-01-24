#pragma once
#include <thread>
#include <chrono>
#include <atomic>
#include "events.h"

class Component;
class SpinlockBarrier;

class Board
{
public:
	static void init(Component** components, int componentCount);
	static void init(Component** components, int componentCount, int threadCount);
	static void init(Component** components, int componentCount, bool manualClock);
	static void init(Component** components, int componentCount, int threadCount, bool manualClock);
	static bool* readBuffer;
	static bool* writeBuffer;
	static bool* wipeBuffer;
	static size_t componentCount;
	enum State { Uninitialized, Stopped, Running, Stopping };
	static int getThreadCount();
	static Component** getComponents();
	static bool getManualClock();
	static State getCurrentState();
	static unsigned long long int getCurrentTick();
	static unsigned long long currentSpeed;
	static Events::Event<> tickEvent;
	static void stop();
	static void start();
	
private:
	static bool* buffer1;
	static bool* buffer2;
	static bool* buffer3;
	static int threadCount;
	static Component** components;
	static bool manualClock;
	static State currentState;
	static unsigned long long int tick;
	static std::thread** threads;
	static SpinlockBarrier* barrier;
	static std::chrono::high_resolution_clock::time_point lastCapture;
	static unsigned long long int lastCaptureTick;
};

