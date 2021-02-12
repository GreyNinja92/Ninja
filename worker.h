#pragma once

#include "task.h"
#include<memory>
#include<string>
#include<chrono>

namespace ninja { namespace worker {

	enum Status {
		ALIVE,
		RUNNING,
		DONE,
		ERROR
	}

	typedef std::function<std::shared_ptr<ninja::scheduler::NinjaScheduler>> Scheduler;

	class NinjaWorker {
		public:
			int port;
			Address& Address;
			int id;
			std::chrono::seconds checkStatusEvery;
			ninja::worker::Status status;
	};


	class NinjaWorkerManager {
	public:
		NinjaWorkerManager(
			Scheduler,
			const std::string worker_command,
			int port
			);
		~NinjaWorkerManager();

		ninja::worker::Status getStatus() {
			return ninja::worker::Status::ALIVE;
		}

		void getRunningTasks(
			std::vector<ninja::task::RunningTask>& output,
			const ninja::worker::NinjaWorker& worker
			);
		void runTask(
			const ninja::task::RunningTask& rt,
			const ninja::worker::NinjaWorker& worker
			);
		void notifyIfTasksNotRunning(
			const ninja::worker::NinjaWorker& worker
			);
		void requestSuicide(
			const ninja::worker::NinjaWorker& worker
			);
		void killTask(
			const ninja::task::RunningTask& rt,
			const ninja::worker::NinjaWorker& worker
			);

	private:
		Scheduler scheduler;

		//<Task ID, Task Status>
		std::unordered_map<std::string, std::string> Tasks;

		void killObject();

		std::chrono::seconds getStatusBySecond();
		std::chrono::seconds checkHealth();
		std::chrono::seconds notifyIdle();
		std::chrono::seconds notifyFinished();

	};
}
}