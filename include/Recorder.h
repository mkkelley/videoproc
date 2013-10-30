#pragma once

#include <opencv2/opencv.hpp>
#include <memory>

#include "Camera.h"

class Recorder {
    public:
        Recorder(std::unique_ptr<View>);
        bool record(const std::string file, int frames);
        std::unique_ptr<View> close();
    private:
        std::unique_ptr<View> _cam;
        const int _codec = CV_FOURCC('M', 'J', 'P', 'G');
};
