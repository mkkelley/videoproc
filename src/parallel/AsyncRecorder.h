#pragma once

#include <memory>

#include "ThreadPool.h"
#include "View.h"

/**
 * AsyncRecorder takes input from a view and records it to a file
 * asynchronously without any more effort from the user of the class. If
 * AsyncRecorder::close is called, the objct is thereafter in an invalid
 * state, with undefined behavior (you'll probably get a segfault). It launches
 * one thread on the specified ThreadPool when start is called.
 */
class AsyncRecorder {
    public:
        AsyncRecorder(std::shared_ptr<ThreadPool>, std::unique_ptr<View>);

        /**
         * Launch a thread and start getting frames from the specified view,
         * recording them to a file.
         * @param filename The path of the file to which to record. Overwrites.
         */
        bool start(std::string filename);

        /**
         * Stop recording after the current View::getNextFrame() is finished.
         */
        void stop();

        /**
         * AsyncRecorder::stop() and block until View::getNextFrame() is
         * finished.
         */
        void waitStop();

        /**
         * @return Whether or not the AsyncRecorder is recording at the moment.
         */
        bool isRecording() const;

        /**
         * Close the recorder, invalidating any further calls to start().
         */
        std::unique_ptr<View> close();
    private:
        void record(std::string filename);

        std::shared_ptr<ThreadPool> _pool;
        std::unique_ptr<View> _view;
        std::atomic<bool> _stopped;
        std::atomic<bool> _recording;
        const int _codec = CV_FOURCC('M', 'J', 'P', 'G');
};
