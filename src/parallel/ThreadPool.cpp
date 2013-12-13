#include "ThreadPool.h"

using std::function;
using std::thread;
using std::shared_ptr;
using std::unique_lock;
using std::mutex;

ThreadPool::ThreadPool(size_t threads)
    : _num_threads(threads),
    _threads_running(0),
    _terminate_all_workers(false)
{
    for (int i = 0; i < _num_threads; i++) {
        ++_threads_running;
        worker_type::create_and_attach(shared_ptr<ThreadPool>(this));
    }
}

bool ThreadPool::execute_next_task() volatile {
    function<void()> fn;

    {
        ThreadPool* self = const_cast<ThreadPool*>(this);
        unique_lock<mutex> lock(self->_queue_lock);
        if (self->_terminate_all_workers) {
            return false;
        }
        while (self->_queue.empty()) {
            if (self->_terminate_all_workers) {
                return false;
            }
            --self->_threads_running;
            self->_idle_or_terminated_event.notify_all();
            self->_task_or_terminated_event.wait(lock);
            ++self->_threads_running;
        }

        fn = self->_queue.front();
        self->_queue.pop();
    }
    fn();

    return true;
}

void ThreadPool::wait(size_t const threshold) volatile const {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    unique_lock<mutex> lock(self->_queue_lock);
    if (0 == threshold) {
        while (0 != self->_threads_running || !self->_queue.empty()) {
            self->_idle_or_terminated_event.wait(lock);
        }
    } else {
        while (self->_queue.size() + self->_threads_running > threshold) {
            self->_idle_or_terminated_event.wait(lock);
        }
    }
}

void ThreadPool::terminate_all_workers() volatile {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    unique_lock<mutex> lock(self->_queue_lock);

    self->_terminate_all_workers = true;
    self->_task_or_terminated_event.notify_all();

    while (_threads_running > 0) {
        self->_idle_or_terminated_event.wait(lock);
    }

    for (auto& worker : self->_terminated_workers) {
        worker->join();
    }

    self->_terminated_workers.clear();
}

void ThreadPool::destruct_worker(shared_ptr<worker_type> worker) volatile {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    unique_lock<mutex> lock(self->_queue_lock);
    --_threads_running;
    self->_idle_or_terminated_event.notify_all();
    self->_terminated_workers.push_back(worker);
}
