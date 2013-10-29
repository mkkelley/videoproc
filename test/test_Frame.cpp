#include "Frame.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <iterator>

using cv::KeyPoint;
using cv::Mat;
using cv::imread;
using std::cout;
using std::endl;
using std::ostream_iterator;

int main(int argc, char **argv) {
    Mat image = imread("test1.png", CV_LOAD_IMAGE_COLOR);
    /*
    cv::namedWindow("test", CV_WINDOW_AUTOSIZE);
    cv::imshow("test", image);
    cv::waitKey(0);
    */
    Frame f(image);
    CornerDetector cd;
    f.calculate(cd);
    cout << f.getLSRLSlope() << endl;
    cout << f.getAverageSlope() << endl;
    auto kps = f.getKeyPoints();
    for (std::vector<KeyPoint>::size_type i = 0; i < kps.size(); i++) {
        cout << kps[i].pt << endl;
    }
    //std::cout << f.getKeyPoints() << std::endl;
    return 0;
}
