#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**) {
    VideoCapture cap(0);
    if (cap.isOpened()) {
        std::cout << "Opened camera.\n";
    } else {
        std::cout << "Couldn't find.\n";
        return -1;
    }
    Size inputSize = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
                (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    //int codec = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
    //Size inputSize = Size(640, 480);
    std::cout << inputSize;
    VideoWriter outputVideo;
    //outputVideo.open("output.avi", -1, cap.get(CV_CAP_PROP_FPS), inputSize, true);
    outputVideo.open("output.avi", CV_FOURCC('X', 'V', 'I', 'D'), 15, inputSize, true);

    if (!outputVideo.isOpened()) {
        std::cout << "Problem. Couldn't open video output.";
        //return -1;
    }

    Mat image;
    bool x = true;
    int n = 0;
    namedWindow("Display Image", CV_WINDOW_AUTOSIZE);
    while (x && n < 100) {
        bool x = cap.read(image);
        outputVideo << image;
        n++;
        imshow("Display Image", image);
        //waitKey(0);
    }
    return 0;
}
