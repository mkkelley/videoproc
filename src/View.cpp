#include "View.h"

using std::function;
using std::vector;
using cv::Mat;

Mat View::getNextFrame() {
    Mat raw = getNextRawFrame();
    for (unsigned int i = 0; i < _filters.size(); ++i) {
        raw = _filters[i](raw);
    }
    return raw;
}

void View::addFilter(function<Mat(Mat&)> filter) {
    _filters.push_back(filter);
}
