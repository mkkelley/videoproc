#include "AlgorithmSelector.h"

#include "Algorithms.h"

using std::map;
using std::string;
using std::vector;
using cv::Mat;

static inline cv::Mat nothing(const cv::Mat& m) { return m; }

const map<string, AlgorithmSelector::transform_fn> AlgorithmSelector::_algorithms {
    {"None", &nothing},
    {"Keypoints", &vp::analyzeFrame},
    {"Circles", &vp::drawCircles},
    {"Ellipses", &vp::drawEllipses},
    {"Contours", &vp::drawContours},
    {"Motion", &vp::drawMotion},
    {"Ghost", &vp::drawGhost},
    {"C & M", &vp::drawContoursAndMotion},
    {"MC & M", &vp::matchContoursAndMotion},
};

AlgorithmSelector::AlgorithmSelector(QWidget* parent)
    : QComboBox(parent)
{
    for (auto it = _algorithms.begin(); it != _algorithms.end(); it++) {
        addItem(QString(it->first.c_str()));
    }
}

AlgorithmSelector::transform_fn AlgorithmSelector::getFunction() const {
    return _algorithms.at(currentText().toStdString());
}
