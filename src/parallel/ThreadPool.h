#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>

#include "FQueue.h"
#include "WorkerThread.h"

class ThreadPool {
    typedef WorkerThread<ThreadPool> worker_type;
    public:
        ThreadPool(size_t threads = 1);

        template<class F>
        void submit(F&& f) {
            std::lock_guard<std::mutex> lock(_queue_lock);
            _queue.push(std::move(f));
            _task_or_terminated_event.notify_one();
        }
        void wait(size_t const threshold) const;
        void terminate_all_workers();

    private:
        friend class WorkerThread<ThreadPool>;
        //these functions meant to be called by WorkerThread
        bool execute_next_task();
        void destruct_worker(std::shared_ptr<worker_type>);

        unsigned const int _num_threads;
        //can be accessed and changed by multiple simultaneous threads
        std::atomic<unsigned int> _threads_running;

        mutable std::mutex _queue_lock;
        std::queue<std::function<void()>> _queue;

        mutable std::condition_variable _task_or_terminated_event;
        mutable std::condition_variable _idle_or_terminated_event;

        std::atomic<bool> _terminate_all_workers;
        std::list<std::shared_ptr<worker_type>> _terminated_workers;
};
