#pragma once

#include <opencv2/opencv.hpp>

#include "Camera.h"

using std::string;

class Video : protected Camera {
    public:
        Video(const string);
};
