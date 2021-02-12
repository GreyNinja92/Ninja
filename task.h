#pragma once

#include<iostream>
#include<memory>
#include<string>
#include<chrono>
#include "worker.h"

namespace ninja { namespace task {

    class RunningTask {
        public:
        const worker::NinjaWorker& worker;
        std::chrono::seconds alloted;
        std::chrono::seconds complete;
        bool isStuckInQueue = false;
        bool isComplete = false;
        std::string shellScript;


        RunningTask(
            const worker::NinjaWorker& worker,
            std::chrono::seconds currentTime,
            std::string shellScript
        );

        ~RunningTask();

    }

}
}