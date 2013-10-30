#pragma once

#include <opencv2/opencv.hpp>

#include "Camera.h"

using std::string;

class Video : public Camera {
    public:
        Video(const string);
};
