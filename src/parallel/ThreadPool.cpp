#include "ThreadPool.h"

using std::function;
using std::thread;

ThreadPool::ThreadPool() 
    : _numThreads(
            thread::hardware_concurrency() == 0 ?
                1 :
                thread::hardware_concurrency()
            ),
    _freeThreads(_numThreads),
    _threadsRunning(0),
    _futures(_numThreads)
{

}


void ThreadPool::cleanup() {
    for (unsigned int i = 0; i < _threadsRunning; i++) {
        if (_futures.at(i).valid()) {
            _futures.erase(_futures.begin() + i);
            ++_freeThreads;
            --_threadsRunning;
        }
    }
}
