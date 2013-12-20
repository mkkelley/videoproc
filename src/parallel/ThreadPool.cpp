#include "ThreadPool.h"

using std::function;
using std::thread;
using std::shared_ptr;
using std::unique_lock;
using std::mutex;

ThreadPool::ThreadPool(size_t threads)
    : _num_threads(threads),
    _threads_running(0),
    _num_workers(0),
    _terminate_all_workers(false)
{
    for (unsigned int i = 0; i < _num_threads; i++) {
        ++_threads_running;
        ++_num_workers;
        worker_type::create_and_attach(this);
    }
}

ThreadPool::~ThreadPool() {
    wait(0);
    terminate_all_workers();
}

bool ThreadPool::execute_next_task() {
    function<void()> fn;

    { //enter scope to release lock before function is executed
        unique_lock<mutex> lock(_queue_lock);
        if (_terminate_all_workers) {
            return false;
        }
        while (_queue.empty()) {
            if (_terminate_all_workers) {
                return false;
            }
            --_threads_running;
            _idle_or_terminated_event.notify_all();
            _task_or_terminated_event.wait(lock);
            ++_threads_running;
        }

        fn = _queue.front();
        _queue.pop();
    }
    fn();

    return true;
}

void ThreadPool::wait(size_t const threshold) const {
    unique_lock<mutex> lock(_queue_lock);
    if (0 == threshold) {
        while (0 != _threads_running || !_queue.empty()) {
            _idle_or_terminated_event.wait(lock);
        }
    } else {
        while (_queue.size() + _threads_running > threshold) {
            _idle_or_terminated_event.wait(lock);
        }
    }
}

void ThreadPool::terminate_all_workers() {
    unique_lock<mutex> lock(_queue_lock);

    _terminate_all_workers = true;
    _task_or_terminated_event.notify_all();

    while (_num_workers > 0) {
        _idle_or_terminated_event.wait(lock);
    }

    for (auto& worker : _terminated_workers) {
        worker->join();
    }

    _terminated_workers.clear();
}

void ThreadPool::destruct_worker(shared_ptr<worker_type> worker) {
    unique_lock<mutex> lock(_queue_lock);
    --_threads_running;
    --_num_workers;
    _idle_or_terminated_event.notify_all();
    _terminated_workers.push_back(worker);
}
