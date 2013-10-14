#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"
#include "CamFilter.h"
#include "CornerDetector.h"
#include "FlagParser.h"
#include "Recorder.h"
#include "VideoStitcher.h"
#include "Video.h"

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::to_string;
using std::vector;
using cv::KeyPoint;
using cv::Mat;

void showHelp() {
    cout << "Valid options include:\n"
        << "\trecord\n"
        << "\tstitch [outfilename]\n"
        << "\tcorners [infilename]\n"
        << "\n"
        << "\trealtime\n"
        << "\tvideo filename\n"
        << "\n"
        << "\t[--type=ALGO] to set the keypoint extraction technique\n";
}

int stitch(string filename) {
    VideoStitcher stitch(filename, 24);
    for (int i = 1; i <= 100; i++) {
        string num = "00";
        if (i < 10) num += to_string(0);
        num += to_string(i);
        stitch.appendImage(num + string(".png"));
    }
    return 0;
}

double findAverageSlope(const vector<KeyPoint>& kps) {
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

double findAverageX(const vector<KeyPoint>& kps) {
    double sum = 0;
    for (uint32_t i = 0; i < kps.size(); ++i) {
        sum += kps[i].pt.x;
    }
    return sum / kps.size();
}

double findAverageY(const vector<KeyPoint>& kps) {
    double sum = 0;
    for (uint32_t i = 0; i < kps.size(); ++i) {
        sum += kps[i].pt.y;
    }
    return sum / kps.size();
}

double findStdDevX(const vector<KeyPoint>& kps) {
    double sum = std::accumulate(begin(kps), end(kps), 0.0,
            [] (const double x, const KeyPoint& y) {
            return x + y.pt.x;
            });
    double m = sum / kps.size();
    double acc = 0.0;
    std::for_each(begin(kps), end(kps), [&](const KeyPoint& k) {
            acc += (k.pt.x - m) * (k.pt.x - m);
            });
    return sqrt(acc/kps.size());
}

double findStdDevY(const vector<KeyPoint>& kps) {
    double sum = std::accumulate(begin(kps), end(kps), 0.0,
            [] (const double x, const KeyPoint& y) {
            return x + y.pt.y;
            });
    double m = sum / kps.size();
    double acc = 0.0;
    std::for_each(begin(kps), end(kps), [&](const KeyPoint& k) {
            acc += (k.pt.y - m) * (k.pt.y - m);
            });
    return sqrt(acc/kps.size());
}

double findR(const vector<KeyPoint>& kps) {
    double sumX = 0;
    double sumY = 0;
    double sumX2 = 0;
    double sumY2 = 0;
    double sumXY = 0;
    for (uint32_t i = 0; i < kps.size(); ++i) {
        sumX += kps[i].pt.x;
        sumX2 += kps[i].pt.x * kps[i].pt.x;
        sumY += kps[i].pt.y;
        sumY2 += kps[i].pt.y * kps[i].pt.y;
        sumXY += kps[i].pt.x * kps[i].pt.y;
    }
    double num = kps.size() * sumXY - sumX * sumY;
    double denom = sqrt((kps.size()*sumX2 - sumX * sumX)*
            (kps.size()*sumY2 - sumY * sumY));
    return -num / denom;
}

double findLSRLSlope(const vector<KeyPoint>& kps) {
    return findR(kps) * findStdDevY(kps) / findStdDevX(kps);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        showHelp();
        return 1;
    }

    FlagParser flags(argc, argv);

    string detectorType = "";
    if (flags.isSet("type")) {
        detectorType = flags.getOption("type");
    }

    CornerDetector cd(detectorType);

    typedef pair<string, std::function<double(const vector<KeyPoint>&)>> flagFn;
    flagFn flagfns[] =
    {
        flagFn("slope", findAverageSlope),
        flagFn("avgx", findAverageX),
        flagFn("stdx", findStdDevX),
        flagFn("avgy", findAverageY),
        flagFn("stdy", findStdDevY),
        flagFn("r", findR),
        flagFn("lsrl", findLSRLSlope),
    };
    auto pFunc = [&] (Mat& m) {
        Mat out;
        auto kps = cd.getKeyPoints(m);
        bool first = true;
        for (uint32_t i = 0; i < sizeof(flagfns)/sizeof(flagfns[0]); ++i) {
            if (flags.isSet(flagfns[i].first)) {
                if (!first) {
                    cout << ", ";
                }
                cout << flagfns[i].second(kps);
                first = false;
            }
        }
        if (!first) {
            cout << endl;
        }
        cv::drawKeypoints(m, kps, out);
        return out;
    };

    if (flags.getArg(1) == "stitch") {
        if (flags.getNumArgs() < 3) {
            stitch("combine.avi");
        } else {
            stitch(flags.getArg(2));
        }
    } else if (flags.getArg(1) == "record") {
        std::unique_ptr<Camera> cam(new Camera(0));
        double fps = cam->getFps();
        cout << "FPS: "  << fps << endl;

        cv::Size inputSize = cam->getSize();
        cout << "Input Resolution: " << inputSize << endl;

        //cam->setFunction(pFunc);

        Recorder r(std::move(cam));
        r.record("output.avi", 100);
    } else if (flags.getArg(1) == "realtime") {
        std::unique_ptr<Camera> cam(new Camera(0));
        CamFilter cf(std::move(cam), pFunc);

        cv::namedWindow("feed", 1);
        do {
            Mat image = cf.getNextFrame();
            cv::imshow("feed", image);
        } while (cv::waitKey(1) != 27);
    } else if (flags.getArg(1) == "video") {
        if (flags.getNumArgs() < 3) {
            std::cerr << "Must specify video file.\n";
            return 1;
        }

        std::unique_ptr<Video> v(new Video(flags.getArg(2)));
        CamFilter cf(std::move(v), pFunc);

        cv::namedWindow("feed", 1);
        Mat image = cf.getNextFrame();
        while(!image.empty()) {
            cv::imshow("feed", image);
            cv::waitKey(1);
            image = cf.getNextFrame();
        }
    } else if (flags.getArg(1) == "analyze") {
        if (flags.getNumArgs() < 3) {
            std::cerr << "Must specify video file.\n";
            return 1;
        }

        std::unique_ptr<Video> v(new Video(flags.getArg(2)));
        CamFilter cf(std::move(v), pFunc);

        Mat image = cf.getNextFrame();
        while(!image.empty()) {
            image = cf.getNextFrame();
        }
    } else if (flags.getArg(1) == "corners") {
        Mat image;
        if (flags.getNumArgs() < 3) {
            Camera cam(0);
            image = cam.getNextFrame();
        } else {
            string filename = flags.getArg(2);
            image = cv::imread(flags.getArg(2));
            if (image.data == NULL) {
                std::cerr << "Unable to read specified file: \""
                    << filename << "\"\n";
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
    } else if (flags.getArg(1) == "test") {
        std::unique_ptr<Camera> cam(new Camera(0));
        CamFilter(std::move(cam), pFunc);

    } else {
        showHelp();
        return 1;
    }

    return 0;
}
