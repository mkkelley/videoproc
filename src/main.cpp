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
using std::map;

void showHelp() {
    cout << "Valid options include:\n"
        << "\tcorners [infilename]\n"
        << "\trealtime\n"
        << "\trecord\n"
        << "\tstitch [outfilename]\n"
        << "\tvideo filename\n";
}

int stitch(char* filename) {
    string out;
    if (filename != NULL) {
        out = filename;
    } else {
        out = "combine.avi";
    }
    VideoStitcher stitch(out, 24);
    for (int i = 1; i <= 100; i++) {
        string num = "00";
        if (i < 10) num += to_string(0);
        num += to_string(i);
        stitch.appendImage(num + string(".png"));
    }
    return 0;
}

double findRegressionSlope(const vector<KeyPoint>& kps) {
    double almostSum = 0;
    for (uint32_t i = 0; i < kps.size(); ++i) {
        double localSum = 0;
        for (uint32_t j = 0; j < kps.size(); ++j) {
            if (i == j) continue;
            if (kps[i].pt.x == kps[j].pt.x) continue;
            localSum += (kps[i].pt.y - kps[j].pt.y) /
                (kps[i].pt.x - kps[j].pt.x);
        }
        almostSum += (localSum / (kps.size() - 1));
    }
    almostSum /= kps.size();
    return almostSum;
}

map<string, string> parseFlags(vector<string>& args) {
    map<string, string> options;
    for (uint8_t i = 0; i < args.size(); i++) {
        if (args[i].find("--") != 0) {
            continue;
        }
        uint8_t eqIndex = args[i].find("=");
        if (eqIndex == -1) {
            std::cerr << "Invalid option: " << args[i] << endl;
            exit(1);
        }
        options[args[i].substr(2, eqIndex - 2)] = args[i].substr(eqIndex + 1);
        args.erase(args.begin() + i);
        --i;
    }
    return options;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        showHelp();
        return 1;
    }

    vector<string> args(argc);
    for (int i = 1; i < argc; i++) {
        args[i] = argv[i];
    }

    map<string, string> options = parseFlags(args);

    string detectorType = "";
    if (options.find("type") != options.end()) {
        detectorType = options["type"];
    }

    CornerDetector cd(detectorType);

    auto pFunc = [&cd] (Mat& m) {
        Mat out;
        auto kps = cd.getKeyPoints(m);
        cout << findRegressionSlope(kps) << endl;
        cv::drawKeypoints(m, kps, out);
        return out;
    };

    if (string(argv[1]) == "stitch") {
        stitch(argv[2]);
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
        uint32_t fnum=1;
        do {
            cout << fnum++ << ", ";
            Mat image = cam.getNextFrame();
            cv::imshow("feed", image);
        } while (cv::waitKey(1) != 1048603);
    } else if (string(argv[1]) == "video") {
        if (argv[2] == NULL) {
            std::cerr << "Must specify video file.\n";
            return 1;
        }

        Video v(argv[2]);
        v.setFunction(pFunc);
        cv::namedWindow("feed", 1);
        int fnum = 1;
        while(true) {
            cout << fnum++ << ", ";
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
