#include "Recorder.h"

using std::unique_ptr;

Recorder::Recorder(unique_ptr<View> c) : _cam(std::move(c)) {
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

unique_ptr<View> Recorder::close() {
    //safe because _cam internal pointer is set to null - no garbage pointer
    return std::move(_cam);
}
