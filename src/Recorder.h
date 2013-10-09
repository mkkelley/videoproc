#pragma once

#include <opencv2/opencv.hpp>
#include <memory>

#include "Camera.h"

class Recorder {
    public:
        Recorder(std::unique_ptr<Viewer>);
        bool record(const std::string file, int frames);
        std::unique_ptr<Viewer> close();
    private:
        std::unique_ptr<Viewer> _cam;
        const int _codec = CV_FOURCC('M', 'J', 'P', 'G');
};
