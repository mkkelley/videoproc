#pragma once

#include <opencv2/opencv.hpp>

using cv::Mat;
using cv::VideoWriter;
using cv::Size;
using std::string;

class VideoStitcher {
    public:
        VideoStitcher(
                const string outputFile,
                double fps,
                int codec = CV_FOURCC('M','J','P','G')
                );
        bool appendImage(Mat& image);
        bool appendImage(const string fileName);
    private:
        bool openOut(Size s);
        VideoWriter _out;
        const string _outfile;
        const double _fps;
        const int _codec;
};
