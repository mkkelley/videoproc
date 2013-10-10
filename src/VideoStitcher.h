#pragma once

#include <opencv2/opencv.hpp>

class VideoStitcher {
    public:
        VideoStitcher(
                const std::string outputFile,
                double fps,
                int codec = CV_FOURCC('M','J','P','G')
                );
        bool appendImage(cv::Mat& image);
        bool appendImage(const std::string fileName);
    private:
        bool openOut(cv::Size s);
        cv::VideoWriter _out;
        const std::string _outfile;
        const double _fps;
        const int _codec;
};
