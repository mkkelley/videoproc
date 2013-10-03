#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

using cv::Mat;
using cv::Size;
using cv::VideoCapture;
using std::vector;

class Camera {
    public:
        double getWidth();
        double getHeight();
        Size getSize();
        double getFps();
        Mat getNextFrame();
        virtual vector<Mat> captureVideo(int frames);
        Camera();
        virtual ~Camera();

    private:
        VideoCapture _cap;
        double _fps;
};
