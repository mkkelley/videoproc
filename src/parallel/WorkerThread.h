#pragma once

#include <memory>
#include <thread>

#include "ThreadPool.h"

template <class Pool>
class WorkerThread : public std::enable_shared_from_this<WorkerThread<Pool>> {
    public:
        /**
         * Construct a WorkerThread with a pointer to the pool on which it
         * will work.
         */
        WorkerThread(const std::shared_ptr<Pool>& pool) :
            _pool(pool),
            _thread(nullptr)
        {
        }

        /**
         * Execute tasks from the associated thread pool. Notify pool of
         * destruction when _pool#execute_next_task() return false.
         */
        void run() {
            while (_pool->execute_next_task()) {

            }

            _pool->destruct_worker(this->shared_from_this());
        }

        /**
         * Join the current thread, blocking until WorkerThread::run()
         * returns.
         */
        void join() {
            _thread->join();
        }

        /**
         * Construct a WorkerThread with a pointerr to a thread pool, and start
         * execution of tasks from the pool.
         */
        static void create_and_attach(const std::shared_ptr<Pool>& p) {
            std::shared_ptr<WorkerThread> worker(new WorkerThread(p));
            worker->_thread = std::make_shared<std::thread>(
                std::thread(std::bind(&WorkerThread::run, worker))
            );
        }

    private:
        std::shared_ptr<Pool> _pool;
        std::shared_ptr<std::thread> _thread;
};
