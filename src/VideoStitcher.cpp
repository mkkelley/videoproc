#include "VideoStitcher.h"

using std::string;
using cv::imread;
using cv::Mat;
using cv::Size;

VideoStitcher::VideoStitcher(
        string outputFile,
        double fps,
        int codec) :
    _outfile(std::move(outputFile)),
    _fps(fps),
    _codec(codec)
{
    
}

bool VideoStitcher::openOut(Size s) {
    if (_out.isOpened()) {
        return true;
    }

    bool success = _out.open(_outfile, _codec, _fps, s, true);
    return success;
}

bool VideoStitcher::appendImage(const Mat& image) {
    if (!openOut(image.size())) {
        return false;
    }

    _out.write(image);
    return true;
}

bool VideoStitcher::appendImage(string fileName) {
    Mat image = imread(fileName, CV_LOAD_IMAGE_COLOR);
    if (!openOut(image.size())) {
        return false;
    }

    _out.write(image);
    return true;
}
