#pragma once

#include <opencv2/opencv.hpp>
#include <memory>

#include "Camera.h"

class Recorder {
    public:
        Recorder(std::unique_ptr<Camera>);
        bool record(const std::string file, int frames);
        std::unique_ptr<Camera> close();
    private:
        std::unique_ptr<Camera> _cam;
        const int _codec = CV_FOURCC('M', 'J', 'P', 'G');
};
