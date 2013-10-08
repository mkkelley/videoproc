#include <iostream>
#include <opencv2/opencv.hpp>

#include "Camera.h"
#include "Recorder.h"
#include "VideoStitcher.h"

using std::cout;
using std::endl;
using std::to_string;

void showHelp() {
    cout << "Valid options include:\n";
    cout << "\tstitch\n";
    cout << "\trecord\n";
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
        std::cout << "FPS: "  << fps << std::endl;

        cv::Size inputSize = cam.getSize();
        std::cout << "Input Resolution: " << inputSize << std::endl;

        Recorder r(&cam);
        r.record("output.avi", 100);
    } else {
        showHelp();
        return 1;
    }
    return 0;
}
