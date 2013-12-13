#pragma once

#include <functional>
#include <queue>

class FQueue {
    public:

        FQueue()
            : _functionQueue()
        {
        }

        template <class F>
        void push(F&& f) {
            _functionQueue.push(f);
        }
        
        void pop() {
            if (_functionQueue.empty()) {
                throw std::logic_error("Pop called on empty FQueue.");
            }
            _functionQueue.pop();
        }

        bool empty() const {
            return _functionQueue.empty();
        }

        std::function<void()> front() const {
            return std::move(_functionQueue.front());
        }

        std::function<void()> back() const {
            return std::move(_functionQueue.back());
        }

        unsigned int size() const {
            return _functionQueue.size();
        }
    private:
        std::queue<std::function<void()>> _functionQueue;
};
