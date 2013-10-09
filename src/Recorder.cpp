#include "Recorder.h"

using std::unique_ptr;

Recorder::Recorder(unique_ptr<Camera> c) : _cam(std::move(c)) {
}

bool Recorder::record(const std::string file, int frames) {
    cv::VideoWriter outputVideo;
    outputVideo.open(file, _codec, _cam->getFps(), _cam->getSize(), true);
    if (!outputVideo.isOpened()) {
        return false;
    }

    for (int i = 0; i < frames; i++) {
        outputVideo << _cam->getNextFrame();
    }

    return true;
}

unique_ptr<Camera> Recorder::close() {
    return std::move(_cam);
}
