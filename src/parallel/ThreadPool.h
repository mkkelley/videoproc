#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <queue>

#include "WorkerThread.h"

/**
 * A pool of asynchronous workers to run functions that are submitted. The
 * number of workers can be specified in the constructor, defaults to one.
 * Best use-case is longer running functions, shorter ones might be better
 * executed sequentially.
 */
class ThreadPool : public std::enable_shared_from_this<ThreadPool> {
    typedef WorkerThread<ThreadPool> worker_type;
    public:
        /**
         * Construct a ThreadPool and a number of worker threads.
         * @param threads The number of worker threads to construct.
         */
        ThreadPool(size_t threads = 1);


        void start();

        /**
         * Submit a function to be run asynchronously at a later time.
         * ThreadPool::wait(0) must be called to ensure that all submitted
         * function are actully run.
         * @param f The function to run. Must be void(). Lambdas, result of
         * std::bind, and real functions are all fine. Must not throw an
         * exception.
         */
        template<class F>
        void submit(F&& f) {
            std::lock_guard<std::mutex> lock(_queue_lock);
            _queue.push(std::move(f));
            _task_or_terminated_event.notify_one();
        }

        /**
         * Block until the combined number of active tasks and queued tasks
         * goes below the threshold value.
         * @param threshold The maximum number of active and inactive tasks at
         * which the function will return.
         */
        void wait(size_t const threshold) const;

        /**
         * Terminate all workers after each finishes the task on which it is
         * working. Does not clear the queue.
         */
        void terminate_all_workers();

    private:
        friend class WorkerThread<ThreadPool>;
        /**
         * This function executes the next task in the queue, or blocks until
         * a new task is added or a termination is called. There is no evident
         * reason for anything besides WorkerThread::run to call this function.
         *
         * Exception safety: basic - std::bad_function_call might occur if the
         * passed function is invalid, and it will be discarded from the queue.
         *
         * @return False if the thread is terminated, true otherwise.
         */
        bool execute_next_task();

        /**
         * Send a notification for an idle or terminated worker and add the
         * worker to a list to be sequentially joined.
         *
         * @param w The worker to destroy.
         */
        void destruct_worker(std::shared_ptr<worker_type> w);

        /** Maximum number of workers to run. */
        unsigned const int _num_threads;
        /** Number of threads currently running or waiting. */
        std::atomic<unsigned int> _threads_running;
        std::atomic<unsigned int> _num_workers;

        mutable std::mutex _queue_lock;
        std::queue<std::function<void()>> _queue;

        mutable std::condition_variable _task_or_terminated_event;
        mutable std::condition_variable _idle_or_terminated_event;

        std::atomic<bool> _terminate_all_workers;
        /** List of terminated workers that can be sequentially joined. */
        std::list<std::shared_ptr<worker_type>> _terminated_workers;
};
