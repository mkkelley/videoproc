#include "ThreadPool.h"

#include <unistd.h>
#include "Debug.h"

using std::function;
using std::thread;

ThreadPool::ThreadPool(
       size_t threads
        ) 
    : _numThreads(threads),
    _freeThreads(_numThreads),
    _threadsRunning(0),
    _terminate_all_workers(false)
{
    for (int i = 0; i < _numThreads; i++) {
        ++_threadsRunning;
        worker_type::createAndAttach(std::shared_ptr<ThreadPool>(this));
    }
}

ThreadPool::~ThreadPool() {
}

bool ThreadPool::executeNextTask() volatile {
    std::function<void()> fn;

    {
        ThreadPool* self = const_cast<ThreadPool*>(this);
        std::unique_lock<std::mutex> lock(self->_queue_lock);
        if (self->_terminate_all_workers) {
            return false;
        }
        while (self->_queue.empty()) {
            if (self->_terminate_all_workers) {
                return false;
            }
            --self->_threadsRunning;
            self->_idle_or_terminated_event.notify_all();
            self->_task_or_terminated_event.wait(lock);
            ++self->_threadsRunning;
        }

        fn = self->_queue.front();
        self->_queue.pop();
    }
    fn();

    return true;
}

void ThreadPool::wait(size_t const threshold) volatile const {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    std::unique_lock<std::mutex> lock(self->_queue_lock);
    if (0 == threshold) {
        while (0 != self->_threadsRunning || !self->_queue.empty()) {
            self->_idle_or_terminated_event.wait(lock);
        }
    } else {
        while (self->_queue.size() + self->_threadsRunning > threshold) {
            self->_idle_or_terminated_event.wait(lock);
        }
    }
}

void ThreadPool::terminateAllWorkers() volatile {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    std::unique_lock<std::mutex> lock(self->_queue_lock);

    self->_terminate_all_workers = true;
    self->_task_or_terminated_event.notify_all();

    while (_threadsRunning > 0) {
        self->_idle_or_terminated_event.wait(lock);
    }

    for (auto& worker : self->_terminated_workers) {
        worker->join();
    }

    self->_terminated_workers.clear();
}

void ThreadPool::destructWorker(std::shared_ptr<worker_type> worker) volatile {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    std::unique_lock<std::mutex> lock(self->_queue_lock);
    --_threadsRunning;
    self->_idle_or_terminated_event.notify_all();
    self->_terminated_workers.push_back(worker);
}
