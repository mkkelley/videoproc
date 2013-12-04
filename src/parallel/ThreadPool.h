#pragma once

#include <functional>
#include <future>
#include <thread>
#include <vector>

class ThreadPool {
    public:
        ThreadPool();

        template<class F>
        bool submit(F&& f) {
            cleanup();
            if (_freeThreads == 0) {
                return false;
            }

            // Packaging f is necessary in order to get the future so that
            // a finished thread can be detected.
            std::packaged_task<void()> task(f);
            _futures.push_back(
                std::move(
                    task.get_future()
                )
            );

            std::thread thread(std::move(task));
            thread.detach();

            --_freeThreads;
            ++_threadsRunning;
            return true;
        }
    private:
        void cleanup();

        unsigned const int _numThreads;
        unsigned int _freeThreads;
        unsigned int _threadsRunning;
        std::vector<std::future<void>> _futures;
};
