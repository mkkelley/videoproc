#include "AsyncRecorder.h"

#include <unistd.h>

using std::shared_ptr;
using std::string;
using std::unique_ptr;

AsyncRecorder::AsyncRecorder(shared_ptr<ThreadPool> pool,
                             unique_ptr<View> view)
    : _pool(std::move(pool)),
    _view(std::move(view)),
    _stopped(true),
    _recording(false)
{

}

void AsyncRecorder::record(string filename) {
    cv::VideoWriter output(filename, _codec, _view->getFps(), _view->getSize(), true);

    _recording = true;
    while (!_stopped) {
        output.write(_view->getNextFrame());
    }
    _recording = false;
}

bool AsyncRecorder::start(string filename) {
    if (!_stopped) {
        return false;
    }
    _stopped = false;

    _pool->submit(std::bind(&AsyncRecorder::record, this, filename));
    return true;
}

void AsyncRecorder::stop() {
    _stopped = true;
}

void AsyncRecorder::waitStop() {
    stop();
    while (_recording) {
        usleep(5000);
    }
}

bool AsyncRecorder::isRecording() const {
    return _recording;
}

unique_ptr<View> AsyncRecorder::close() {
    waitStop();
    return std::move(_view);
}
