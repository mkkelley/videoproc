#include "Recorder.h"

Recorder::Recorder(Camera *c) : _cam(c) {
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
