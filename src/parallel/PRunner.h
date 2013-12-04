#include "FQueue.h"

#include <mutex>
#include "ThreadPool.h"

/**
 * Please note that this class is __not__ meant for launching many small
 * functions. The interval between polls may, in many cases, eclipses the time
 * it may take for such a function to run. Use it for heavy processing.
 */
class PRunner {
    public:
        template<class F, class... Args>
        void add(F&& f, Args&&... args) {
            std::lock_guard<std::mutex> lock(_queue_lock);
            _queue.push(std::bind(f, args...));
        }

        template<class F>
        void add(F&& f) {
            std::lock_guard<std::mutex> lock(_queue_lock);
            _queue.push(f);
        }

        PRunner();
        void start();
        void stop();
        bool stopped() const;
    private:
        void update();

        std::mutex _queue_lock;
        FQueue _queue;
        ThreadPool _pool;
        std::atomic<bool> _stopped;
};
