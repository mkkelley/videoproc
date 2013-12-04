#pragma once

#include <functional>
#include <queue>

class FQueue {
    public:
        template <class F>
        void push(F&& f) {
            _functionQueue.push(f);
        }
        
        std::function<void()> front_pop() {
            std::function<void()> f = _functionQueue.front();
            _functionQueue.pop();
            return f;
        }

        void pop() {
            _functionQueue.pop();
        }

        std::function<void()> front() const {
            return _functionQueue.front();
        }

        std::function<void()> back() const {
            return _functionQueue.back();
        }
    private:
        std::queue<std::function<void()>> _functionQueue;
};
