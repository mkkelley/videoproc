#pragma once

#include <memory>

#include "ThreadPool.h"
#include "View.h"

class AsyncRecorder {
    public:
        AsyncRecorder(std::shared_ptr<ThreadPool>, std::unique_ptr<View>);

        bool start(std::string filename);
        void stop();
        void waitStop();
        bool isRecording() const;
        std::unique_ptr<View> close();
    private:
        void record(std::string filename);

        std::shared_ptr<ThreadPool> _pool;
        std::unique_ptr<View> _view;
        std::atomic<bool> _stopped;
        std::atomic<bool> _recording;
        const int _codec = CV_FOURCC('M', 'J', 'P', 'G');
};
