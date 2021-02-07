#pragma once

#include <mutex>
#include <thread>
#include <vector>

#include <job.h>

#include <iostream>

namespace alloy {

struct JobQueue {
	std::mutex mutex;
	std::condition_variable cv;
	std::vector<Job*> jobs;
};

enum class JobThreadType : uint8_t {
	MAIN = 0,
	RENDER,
	WORKER
};

class JobSystem {
public:
	JobSystem() {
		
	}

	void Init() {
		workers_.resize(std::thread::hardware_concurrency());
		std::cout << "Create " << std::thread::hardware_concurrency() << " workers\n";
		isRunning = true;

		for(int i = 0; i < workers_.capacity(); i++) {
			if(i == static_cast<int>(JobThreadType::MAIN)) {
				workers_[i] = std::thread([this, i]() {Work(mainJobQueues_); });
			}else if (i == static_cast<int>(JobThreadType::MAIN)) {
				workers_[i] = std::thread([this, i]() {Work(renderJobQueues_); });
			}else {
				workers_[i] = std::thread([this, i]() {Work(workerJobQueues_); });
			}
		}
	}

	void ScheduleJob(Job* job, const JobThreadType type) {
		switch (type) {
		case JobThreadType::MAIN: {
			std::lock_guard<std::mutex> lock(mainJobQueues_.mutex);
			mainJobQueues_.jobs.push_back(job);
			mainJobQueues_.cv.notify_one();
		}
			break;
		case JobThreadType::RENDER: {
			std::lock_guard<std::mutex> lock(renderJobQueues_.mutex);
			renderJobQueues_.jobs.push_back(job);
			renderJobQueues_.cv.notify_one();
		}
			break;
		case JobThreadType::WORKER: {
			std::lock_guard<std::mutex> lock(workerJobQueues_.mutex);
			workerJobQueues_.jobs.push_back(job);
			workerJobQueues_.cv.notify_one();
		}
			break;
		default: ;
		}
	}

	void Work(JobQueue& jobQueue) {
		std::cout << "Work()\n";
		while(isRunning) {
			Job* job;

			//Critical
			{
				std::unique_lock<std::mutex> lock(jobQueue.mutex);

				if(!jobQueue.jobs.empty()) {
					std::cout << "Not empty()\n";
					job = jobQueue.jobs.front();
					jobQueue.jobs.erase(jobQueue.jobs.cbegin());
					lock.unlock();

					//Check for dependencies
				}else {
					lock.unlock();
					continue;
				}
			}

			job->Execute();
		}
	}

	void Destroy() {
		isRunning = false;
	}
private:
	std::vector<std::thread> workers_;
	JobQueue mainJobQueues_;
	JobQueue renderJobQueues_;
	JobQueue workerJobQueues_;

	std::atomic_bool isRunning = false;
};
}
