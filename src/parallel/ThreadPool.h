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
        void submit(F&& f) volatile {
            ThreadPool* self = const_cast<ThreadPool*>(this);
            std::lock_guard<std::mutex> lock(self->_queue_lock);
            self->_queue.push(std::move(f));
            self->_task_or_terminated_event.notify_one();
        }
        bool execute_next_task() volatile;
        void wait(size_t const threshold) const volatile;
        void destruct_worker(std::shared_ptr<worker_type>) volatile;
        void terminate_all_workers() volatile;
    private:
        void cleanup();

        volatile unsigned const int _num_threads;
        volatile std::atomic<unsigned int> _threads_running;

        mutable std::mutex _queue_lock;
        FQueue _queue;

        mutable std::condition_variable _task_or_terminated_event;
        mutable std::condition_variable _idle_or_terminated_event;

        std::atomic<bool> _terminate_all_workers;
        std::list<std::shared_ptr<worker_type>> _terminated_workers;
};
