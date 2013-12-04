#include "PRunner.h"

#include <unistd.h>

PRunner::PRunner()
    : _queue_lock(),
    _queue(),
    _pool(),
    _stopped()
{
    start();
}

void PRunner::update() {
    while (!stopped()) {
        bool success = false;
        _queue_lock.lock();
        do {
            auto f = _queue.front();
            success = _pool.submit(f);
            if (success) {
                //std::lock_guard<std::mutex> lock(_queue_lock);
                _queue.pop();
            }
        } while (success && !stopped());
        _queue_lock.unlock();
        usleep(100);
    }
}

void PRunner::start() {
    std::thread t(std::bind(&PRunner::update, this));
    t.detach();
    _stopped.store(false);
}

void PRunner::stop() {
    _stopped.store(true);
}

bool PRunner::stopped() const {
    return _stopped.load();
}
