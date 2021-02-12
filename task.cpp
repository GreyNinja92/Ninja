#include "task.h"

namespace ninja { namespace task {

        RunningTask::RunningTask(
            const worker::NinjaWorker &worker,
            std::chrono::seconds currentTime,
            std::string shellScript)
        {
            this->worker = kworker;
            this->alloted = currentTime;
            this->shellScript = shellScript;
        }

    RunningTask::~RunningTask {
        exit(1);
    }

}}