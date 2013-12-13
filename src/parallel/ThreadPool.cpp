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
    _stopped(false)
{
    for (int i = 0; i < _numThreads; i++) {
        ++_threadsRunning;
        worker_type::createAndAttach(std::shared_ptr<ThreadPool>(this));
    }
}

ThreadPool::~ThreadPool() {
    cout << "~ThreadPool()" << endl;
    _stopped = true;
    wait(0);
    cout << "end ~ThreadPool()" << endl;
}

bool ThreadPool::executeNextTask() volatile {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    std::unique_lock<std::mutex> lock(self->_queue_lock);
    if (self->_queue.empty()) {
        if (self->_stopped.load()) {
            return false;
        }
        --self->_threadsRunning;
        self->_idle_or_terminated_event.notify_all();
        self->_task_or_terminated_event.wait(
            lock,
            [self]() { return !self->_queue.empty() || self->_stopped.load();}
        );
        ++self->_threadsRunning;
    }
    while (self->_queue.empty()) {

    }

    if (self->_queue.empty() && self->_stopped.load()) return false;
    auto fn = self->_queue.front();
    self->_queue.pop();

    fn();

    return true;
}

void ThreadPool::wait(size_t const threshold) volatile const {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    std::unique_lock<std::mutex> lock(self->_queue_lock);
    while (self->_queue.size() + self->_threadsRunning > threshold) {
        cout << "qs: " << self->_queue.size();
        cout << " tr: " << self->_threadsRunning << endl;
        self->_idle_or_terminated_event.wait(lock);
    }
}
/*
void ThreadPool::terminateAllWorkers() {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    std::unique_lock<std::mutex> lock(self->_queue_lock);
}*/

void ThreadPool::destructWorker(std::shared_ptr<worker_type> worker) volatile {
    ThreadPool* self = const_cast<ThreadPool*>(this);
    //std::unique_lock<std::mutex> lock(self->_queue_lock);
    --_threadsRunning;
    self->_idle_or_terminated_event.notify_all();
    worker->join();
}
