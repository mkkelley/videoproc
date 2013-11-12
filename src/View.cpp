#include "View.h"

using std::function;
using cv::Mat;

Mat View::getNextFrame() {
    Mat raw = getNextRawFrame();
    if (raw.empty()) return raw;
    for (auto &filter : _filters) {
        raw = filter(raw);
    }
    return raw;
}

void View::addFilter(function<Mat(Mat&)> filter) {
    _filters.push_back(filter);
}
