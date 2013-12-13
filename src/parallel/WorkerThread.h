#pragma once

#include <memory>
#include <thread>

#include "ThreadPool.h"

template <class Pool>
class WorkerThread : public std::enable_shared_from_this<WorkerThread<Pool>> {
    public:
        WorkerThread(std::shared_ptr<Pool> pool) :
            _pool(pool)
        {
        }

        void run() {
            while (_pool->executeNextTask()) {

            }

            _pool->destructWorker(this->shared_from_this());
        }

        void join() {
            _thread->join();
        }

        static void createAndAttach(const std::shared_ptr<Pool>& p) {
            std::shared_ptr<WorkerThread> worker(new WorkerThread(p));
            worker->_thread = std::make_shared<std::thread>(
                std::thread(std::bind(&WorkerThread::run, worker))
            );
        }

    private:
        std::shared_ptr<Pool> _pool;
        std::shared_ptr<std::thread> _thread;
};
