#include "CamFilter.h"

using std::unique_ptr;
using std::function;
using cv::Size;
using cv::Mat;

CamFilter::CamFilter(
        unique_ptr<Viewer> cam,
        function<Mat(Mat&)> filter) :
    _cam(std::move(cam)),
    _filter(filter)
{

}

double CamFilter::getWidth() {
    return _cam->getWidth();
}

double CamFilter::getHeight() {
    return _cam->getHeight();
}

Size CamFilter::getSize() {
    return _cam->getSize();
}

double CamFilter::getFps() {
    return _cam->getFps();
}

Mat CamFilter::getNextFrame() {
    Mat image = _cam->getNextFrame();
    return (!image.empty()) ? _filter(image) : image;
}

vector<Mat> CamFilter::captureVideo(int frames) {
    return _cam->captureVideo(frames);
}
