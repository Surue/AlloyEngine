#include "gtest/gtest.h"

#include "job_system.h"
#include "../externals/Remotery/lib/Remotery.h"

TEST(JobSystem, Schedule) {

	Remotery* rmt;
	rmt_CreateGlobalInstance(&rmt);
	using namespace alloy;
	using namespace std::chrono_literals;
	
	JobSystem jobSystem;
	jobSystem.Init();

	const int nbJobs = 1000;
	
	std::vector<Job> jobs = std::vector<Job>(nbJobs);
	std::vector<bool> jobsFinished = std::vector<bool>(nbJobs);

	for(int i = 0; i < nbJobs; i++) {
		jobs[i] = Job([i]() {
			rmt_ScopedCPUSample(Test, NULL);
			std::this_thread::sleep_for((i + 1) * 10ms);
		});
	}
	
	for (int i = 0; i < nbJobs; i++) {
		jobSystem.ScheduleJob(&jobs[i], JobThreadType::WORKER);
	}

	while (true) {
		
	}

	rmt_DestroyGlobalInstance(rmt);
}