#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"
#include "CornerDetector.h"
#include "FlagParser.h"
#include "Frame.h"
#include "Recorder.h"
#include "VideoStitcher.h"
#include "Video.h"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::to_string;
using cv::KeyPoint;
using cv::Mat;

double findAverageSlope(const Frame& f) {
    return f.getAverageSlope();
}

double findAverageX(const Frame& f) {
    return f.getAverageX();
}

double findStdDevX(const Frame& f) {
    return f.getStdDevX();
}

double findAverageY(const Frame& f) {
    return f.getAverageY();
}

double findStdDevY(const Frame& f) {
    return f.getStdDevY();
}

double findR(const Frame& f) {
    return f.getR();
}

double findLSRLSlope(const Frame& f) {
    return f.getLSRLSlope();
}

void showHelp() {
    cout << "Valid options include:\n"
        "\trecord\n"
        "\tstitch [outfilename]\n"
        "\tcorners [infilename]\n"
        "\n"
        "\trealtime\n"
        "\tvideo filename\n"
        "\n"
        "\t[--type=ALGO] to set the keypoint extraction technique\n";
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

    typedef pair<string, std::function<double(const Frame&)>> flagFn;
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
        //auto kps = cd.getKeyPoints(m);
        Frame f(m);
        f.calculate(cd);
        bool first = true;
        for (uint32_t i = 0; i < sizeof(flagfns)/sizeof(flagfns[0]); ++i) {
            //flagfns[i].first is the name of the flag. .second is the function.
            if (flags.isSet(flagfns[i].first)) {
                if (!first) {
                    cout << ", ";
                }
                cout << flagfns[i].second(f);
                first = false;
            }
        }
        if (!first) {
            cout << endl;
        }
        cv::drawKeypoints(m, f.getKeyPoints(), out);
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
        cout << "Retrieving FPS.\n";
        double fps = cam->getFps();
        cout << "FPS: "  << fps << endl;
        cout << "Beginning capture.\n";

        Recorder r(std::move(cam));
        r.record("output.avi", 100);
    } else if (flags.getArg(1) == "realtime") {
        std::unique_ptr<Camera> cam(new Camera(0));
        cout << cam->getSize() << endl;
        cam->addFilter(pFunc);

        cv::namedWindow("feed", CV_WINDOW_AUTOSIZE);
        do {
            Mat image = cam->getNextFrame();
            cv::imshow("feed", image);
        } while (cv::waitKey(1) != 27);
    } else if (flags.getArg(1) == "video") {
        if (flags.getNumArgs() < 3) {
            std::cerr << "Must specify video file.\n";
            return 1;
        }

        std::unique_ptr<Video> v(new Video(flags.getArg(2)));
        v->addFilter(pFunc);

        cv::namedWindow("feed", 1);
        Mat image =v->getNextFrame();
        while(!image.empty() && cv::waitKey(1) != 27) {
            cv::imshow("feed", image);
            image = v->getNextFrame();
        }
    } else if (flags.getArg(1) == "analyze") {
        if (flags.getNumArgs() < 3) {
            std::cerr << "Must specify video file.\n";
            return 1;
        }

        std::unique_ptr<Video> v(new Video(flags.getArg(2)));
        v->addFilter(pFunc);

        Mat image = v->getNextFrame();
        while(!image.empty()) {
            image = v->getNextFrame();
        }
    } else if (flags.getArg(1) == "test") {
        cv::namedWindow("test", CV_WINDOW_AUTOSIZE);
        int key = cv::waitKey(10);
        do {
            cout << key << endl;
            key = cv::waitKey();
            if (key >= 65536) key -= 65536;
        } while (key != 27);
    } else {
        showHelp();
        return 1;
    }

    return 0;
}
