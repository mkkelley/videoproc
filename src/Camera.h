#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "Viewer.h"

using cv::Mat;
using cv::Size;
using cv::VideoCapture;
using std::vector;

class Camera : public Viewer {
    public:
        double getWidth();
        double getHeight();
        Size getSize();
        double getFps();
        Mat getNextFrame();
        vector<Mat> captureVideo(int frames);
        Camera();
        Camera(int which);

    protected:
        VideoCapture _cap;
        double _fps;
};
