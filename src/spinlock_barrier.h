#pragma once
#include <atomic>
#include <thread>
#include <mutex>

class SpinlockBarrier
{
public:
	SpinlockBarrier(const SpinlockBarrier&) = delete;
	SpinlockBarrier& operator=(const SpinlockBarrier&) = delete;
	explicit SpinlockBarrier(unsigned int count) :
		m_count(count), m_generation(0),
		m_count_reset_value(count),
		mPostPhaseAction(nullptr)
	{
	}
	explicit SpinlockBarrier(unsigned int count, std::function<void()> postPhaseAction) :
		m_count(count), m_generation(0),
		m_count_reset_value(count),
		mPostPhaseAction(postPhaseAction)
	{
	}
	void wait()
	{
		if (m_count_reset_value <= 1) {
			if (mPostPhaseAction != nullptr)
				mPostPhaseAction();
			return;
		}

		unsigned int gen = m_generation.load();
		if (--m_count)
		{
			if (m_generation.compare_exchange_weak(gen, gen + 1))
			{
				if (mPostPhaseAction != nullptr)
				{
					mPostPhaseMutex.lock();
					mPostPhaseAction();
					mPostPhaseMutex.unlock();
				}
				m_count = m_count_reset_value;
			}
			return;
		}
		while ((gen == m_generation) && (m_count != 0))
			std::this_thread::yield();
	}
private:
	std::atomic<unsigned int> m_count;
	std::atomic<unsigned int> m_generation;
	unsigned int m_count_reset_value;
	std::function<void()> mPostPhaseAction;
	std::mutex mPostPhaseMutex;
};