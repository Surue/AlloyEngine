#include "gtest/gtest.h"

#include "job_system.h"
#include "profiler.h"

TEST(JobSystem, Schedule) {

	alloy::Profiler profiler;
	using namespace alloy;
	using namespace std::chrono_literals;
	
	JobSystem jobSystem;
	jobSystem.Init();

	const int nbJobs = 1000;
	
	std::vector<Job> jobs = std::vector<Job>(nbJobs);
	std::vector<bool> jobsFinished = std::vector<bool>(nbJobs);

	for(int i = 0; i < nbJobs; i++) {
		jobs[i] = Job([i]() {
			BeginProfiling(sleepy);
			std::this_thread::sleep_for((i + 1) * 10ms);
			EndProfiling();
		});
	}
	
	for (int i = 0; i < nbJobs; i++) {
		jobSystem.ScheduleJob(&jobs[i], JobThreadType::WORKER);
	}

	while (true) {
		
	}
}