#pragma once

#include <opencv2/opencv.hpp>

#include "Camera.h"

class Recorder {
    public:
        Recorder(Camera*);
        bool record(const std::string file, int frames);
    private:
        Camera *_cam;
        const int _codec = CV_FOURCC('M', 'J', 'P', 'G');
};
