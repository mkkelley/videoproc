#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"
#include "CornerDetector.h"
#include "Recorder.h"
#include "VideoStitcher.h"

using std::cout;
using std::endl;
using std::to_string;

void showHelp() {
    cout << "Valid options include:\n"
        << "\tstitch\n"
        << "\trecord\n"
        << "\tcorners\n";
}

int main(int argc, char **argv) {
    if (argc == 1) {
        showHelp();
        return 1;
    }
    if (string(argv[1]) == "stitch") {
        VideoStitcher stitch("combine.avi", 24);
        for (int i = 1; i <= 100; i++) {
            string num = "00";
            if (i < 10) num += to_string(0);
            num += to_string(i);
            stitch.appendImage(num + string(".png"));
        }
    } else if (string(argv[1]) == "record") {
        Camera cam(0);
        double fps = cam.getFps();
        cout << "FPS: "  << fps << endl;

        cv::Size inputSize = cam.getSize();
        cout << "Input Resolution: " << inputSize << endl;

        CornerDetector cd;
        cam.setFunction([&cd] (Mat& m) {
                Mat out;
                auto kps = cd.getKeyPoints(m);
                cv::drawKeypoints(m, kps, out);
                return out;
                });

        Recorder r(&cam);
        r.record("output.avi", 100);
    } else if (string(argv[1]) == "corners") {
        Mat image;
        if (argv[2] == nullptr) {
            Camera cam(0);
            image = cam.getNextFrame();
        } else {
            image = cv::imread(argv[2]);
            if (image.data == NULL) {
                std::cerr << "Unable to read specified file: \""
                    << argv[2] << "\"\n";
                return 1;
            }
        }
        CornerDetector cd;
        vector<KeyPoint> keyPoints = cd.getKeyPoints(image);
        Mat matches;
        cv::drawKeypoints(image, keyPoints, matches);

        cv::namedWindow("matches", 1);
        cv::imshow("matches", matches);
        cv::waitKey(0);
    } else {
        showHelp();
        return 1;
    }
    return 0;
}
