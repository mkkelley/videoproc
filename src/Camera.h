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
        vector<Mat> captureVideo(int frames);
        void setFunction(std::function<Mat(Mat&)>);
        Camera();
        Camera(int which);

    protected:
        VideoCapture _cap;
        double _fps;
        std::function<Mat(Mat&)> _func;
};
