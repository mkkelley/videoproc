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
    CornerDetector cd;

    bool getLSRLSlope() {
        f.calculate(cd);
        return abs(f.getLSRLSlope() - 1.01) < .01;
    }

    bool getAverageSlope() {
        f.calculate(cd);
        return abs(f.getAverageSlope() - .86) < .01;
    }
}

int main(int argc, char **argv) {
    TestSet tests;
    tests.registerTest(test::getLSRLSlope, "getLSRLSlope");
    tests.registerTest(test::getAverageSlope, "getAverageSlope");
    tests.runTests();
    return 0;
}