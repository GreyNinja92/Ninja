#include "worker.h"
#include<vector>

int statusBySecondTime = 15;
std::vector<ninja::task::RunningTask>& _taskQueue;

// Somehow get the list of all running tasks with worker identifiers

namespace ninja { namespace worker {

	ninja::worker::NinjaWorker makeWorker(Address& address, int port) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1250));

		ninja::worker::NinjaWorker worker;
		worker.port = port;
		worker.address = address;
		worker.id = rand();
		worker.checkStatusEvery = statusBySecondTime;

		return worker;
	}

	NinjaWorkerManager::NinjaWorkerManager(
		Scheduler scheduler,
		const std::string worker_command,
		Address& address,
		int port){

		runInBackgroundLoop(bind(&NinjaWorkerManager::checkHealth, this));
		runInBackgroundLoop(bind(&NinjaWorkerManager::checkStatusBySecond, this));
		runInBackgroundLoop(bind(&NinjaWorkerManager::notifyIdle, this));
		runInBackgroundLoop(bind(&NinjaWorkerManager::notifyFinished, this));
	}

	NinjaWorkerManager::~NinjaWorkerManager {
		stopBackgroundTasks();
	}

	void NinjaWorkerManager::getRunningTasks(
		std::vector<ninja::task::RunningTask>& output, 
		const ninja::worker::NinjaWorker& worker) {

		for(const auto& task: runningTasks) {
			if(task != HEALTH_CHECKUP) {
				output.push_back(task);
			}
		}
	}

	void NinjaWorkerManager::runTask(
		const ninja::task::RunningTask& rt,
		const ninja::worker::NinjaWorker worker) {

		bool isHealthCheckup = rt.task == HEALTH_CHECKUP;

		if(worker.status != ninja::worker::Status::ERROR and !isHealthCheckup) {
			cout<<"\nWorker is healthy and ready to execute tasks";

		}

		if(isHealthCheckup) {
			cout<<"\nWorker is ready to undergo a health checkup";
		}

		//Mark the task as 'RUNNING'
		// Execute the task

	}

	void NinjaWorkerManager::notifyIfTaskNotRunning(
		const ninja::worker::NinjaWorker& worker) {

		//Somehow check what the worker is doing
		cout<<"WORKER IS WORKING";
	}

	void NinjaWorkerManager::requestSuicide(
		const ninja::worker::NinjaWorker& worker) {

		//Somehow kill the scheduler
		cout<<"SCHEDULER KILLED";
		_exit(1);
	}

	void NinjaWorkerManager::killTask(
		const ninja::worker::NinjaWorker& worker,
		const ninja::task::RunningTask& rt) {

		//remove that particullar task from the task queue
	}




}
}