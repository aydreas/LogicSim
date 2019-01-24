#pragma once
#include <mutex>
#include <condition_variable>

class Barrier {
public:
	explicit Barrier(std::size_t iCount) :
		mThreshold(iCount),
		mCount(iCount),
		mGeneration(0),
		mPostPhaseAction(nullptr) {
	}

	explicit Barrier(std::size_t iCount, std::function<void()> postPhaseAction) :
		mThreshold(iCount),
		mCount(iCount),
		mGeneration(0),
		mPostPhaseAction(postPhaseAction) {
	}

	void wait() {
		std::unique_lock<std::mutex> lLock{ mMutex };
		auto lGen = mGeneration;
		if (!--mCount) {
			if(mPostPhaseAction != nullptr)
				mPostPhaseAction();
			mGeneration++;
			mCount = mThreshold;
			mCond.notify_all();
		}
		else {
			mCond.wait(lLock, [this, lGen] { return lGen != mGeneration; });
		}
	}

private:
	std::mutex mMutex;
	std::condition_variable mCond;
	std::size_t mThreshold;
	std::size_t mCount;
	std::size_t mGeneration;
	std::function<void()> mPostPhaseAction;
};

