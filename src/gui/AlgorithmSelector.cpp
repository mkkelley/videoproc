#include "AlgorithmSelector.h"

#include "Algorithms.h"

using std::map;
using std::string;
using std::vector;
using cv::Mat;

const map<string, AlgorithmSelector::transform_fn> AlgorithmSelector::_algorithms {
    {"Keypoints", &vp::analyzeFrame},
    {"Circles", &vp::drawCircles},
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
