#pragma once

#include <atomic>
#include <functional>

namespace alloy {
class Job {
public:
	Job() {
		
	}
	Job(std::function<void()> function) : function_(function) {}

	void Execute() {
		function_();
		Finish();
	}

	bool IsFinished() const {
		//return unfinishedJobs_ == 0;
		return true;
	}
private:
	std::function<void()> function_;
	/*Job* parent_;
	std::atomic_int32_t unfinishedJobs_;
	char padding_[];*/

	void Finish() {
		/*unfinishedJobs_--;

		if (IsFinished())
		{
			if (parent_ != nullptr)
			{
				parent_->Finish();
			}
		}*/
	}
};
}
