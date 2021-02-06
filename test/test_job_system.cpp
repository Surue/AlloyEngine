#include "gtest/gtest.h"

#include "job_system.h"

TEST(JobSystem, Schedule) {
	using namespace alloy;
	using namespace std::chrono_literals;
	
	JobSystem jobSystem;
	jobSystem.Init();

	const int nbJobs = 10;
	
	std::vector<Job> jobs = std::vector<Job>(nbJobs);
	std::vector<bool> jobsFinished = std::vector<bool>(nbJobs);

	for(int i = 0; i < nbJobs; i++) {
		jobs[i] = Job([i]() {
			//std::this_thread::sleep_for((i + 1) * 10ms);
			std::cout << "ici\n";
		});
	}
	
	for (int i = 0; i < nbJobs; i++) {
		std::cout << "ScheduleJob()\n";
		jobSystem.ScheduleJob(&jobs[i], JobThreadType::WORKER);
	}
}