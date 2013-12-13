#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <thread>
#include <vector>

#include "FQueue.h"
#include "WorkerThread.h"

class ThreadPool {
    typedef WorkerThread<ThreadPool> worker_type;
    public:
        ThreadPool(size_t threads = 1);
        ~ThreadPool();

        template<class F>
        void submit(F&& f) volatile {
            ThreadPool* self = const_cast<ThreadPool*>(this);
            std::lock_guard<std::mutex> lock(self->_queue_lock);
            self->_queue.push(std::move(f));
            self->_task_or_terminated_event.notify_one();
        }
        bool executeNextTask() volatile;
        void wait(size_t const threshold) const volatile;
        void destructWorker(std::shared_ptr<worker_type>) volatile;
        void terminateAllWorkers() volatile;
    private:
        void cleanup();

        volatile unsigned const int _numThreads;
        volatile unsigned int _freeThreads;
        //volatile unsigned int _threadsRunning;
        volatile std::atomic<unsigned int> _threadsRunning;
        mutable std::mutex _queue_lock;
        FQueue _queue;
        mutable std::condition_variable _task_or_terminated_event;
        mutable std::condition_variable _idle_or_terminated_event;
        std::atomic<bool> _terminate_all_workers;
        std::list<std::shared_ptr<worker_type>> _terminated_workers;
};
