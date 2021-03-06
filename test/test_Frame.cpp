#include "Frame.h"

#include <opencv2/opencv.hpp>

#include "TestSet.h"

using cv::Mat;
using cv::imread;

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

    bool getR() {
        f.calculate(cd);
        return abs(f.getR() - .958744) < epsilon;
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
    tests.registerTest(test::getR, "getR");
    return tests.runTests() ? 0 : 1;
}
