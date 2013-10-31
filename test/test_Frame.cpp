#include "Frame.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "TestSet.h"

using cv::KeyPoint;
using cv::Mat;
using cv::imread;
using std::cout;
using std::endl;
using std::ostream_iterator;

namespace test {

    Mat image = imread("test1.png", CV_LOAD_IMAGE_COLOR);
    Frame f(image);
    CornerDetector cd("PyramidGFTT");

    const double epsilon = .0001;

    bool getLSRLSlope() {
        f.calculate(cd);
        return abs(f.getLSRLSlope() - 1.0098) < 10 * epsilon;
    }

    bool getAverageSlope() {
        f.calculate(cd);
        return abs(f.getAverageSlope() - .856296) < epsilon;
    }

    bool getAverageX() {
        f.calculate(cd);
        return abs(f.getAverageX() - 3.3) < epsilon;
    }

    bool getAverageY() {
        f.calculate(cd);
        return abs(f.getAverageY() - 5.5) < epsilon;
    }

    bool getStdDevX() {
        f.calculate(cd);
        return abs(f.getStdDevX() - 2.0025) < epsilon;
    }

    bool getStdDevY() {
        f.calculate(cd);
        return abs(f.getStdDevY() - 2.1095) < epsilon;
    }
}

int main(int argc, char **argv) {
    TestSet tests;
    tests.registerTest(test::getLSRLSlope, "getLSRLSlope");
    tests.registerTest(test::getAverageSlope, "getAverageSlope");
    tests.registerTest(test::getAverageX, "getAverageX");
    tests.registerTest(test::getAverageY, "getAverageY");
    tests.registerTest(test::getStdDevX, "getStdDevX");
    tests.registerTest(test::getStdDevY, "getStdDevY");
    return tests.runTests();
}