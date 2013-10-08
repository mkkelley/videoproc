#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"
#include "CornerDetector.h"
#include "Recorder.h"
#include "VideoStitcher.h"
#include "Video.h"

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
    CornerDetector cd;
    auto pFunc = [&cd] (Mat& m) {
        Mat out;
        auto kps = cd.getKeyPoints(m);
        cv::drawKeypoints(m, kps, out);
        return out;
    };

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

        cam.setFunction(pFunc);

        Recorder r(&cam);
        r.record("output.avi", 100);
    } else if (string(argv[1]) == "realtime") {
        Camera cam(0);
        cam.setFunction(pFunc);
        cv::namedWindow("feed", 1);
        while(true) {
            Mat image = cam.getNextFrame();
            cv::imshow("feed", image);
            cv::waitKey(1);
        }
    } else if (string(argv[1]) == "video") {
        if (argv[2] == NULL) {
            std::cerr << "Must specify video file.\n";
            return 1;
        }

        Video v(argv[2]);
        v.setFunction(pFunc);
        cv::namedWindow("feed", 1);
        while(true) {
            Mat image = v.getNextFrame();
            cv::imshow("feed", image);
            cv::waitKey(1);
        }
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
