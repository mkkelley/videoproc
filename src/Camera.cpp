#include "Camera.h"


Camera::Camera() : cap(0) {

}

double Camera::getFps() {
    if (!cap.isOpened()) {
        return -1;
    }

    time_t start, end;
    double fps;
    double sec;
    int counter = 0;
    time(&start);
    Mat image;
    while(counter < 120) {
        cap >> image;
        time(&end);
        ++counter;
    }
    sec = difftime(end, start);
    fps = counter / sec;
    return fps;
}

double Camera::getWidth() {
    return cap.get(CV_CAP_PROP_FRAME_WIDTH);
}

double Camera::getHeight() {
    return cap.get(CV_CAP_PROP_FRAME_HEIGHT);
}

cv::Size Camera::getSize() {
    return cv::Size(getWidth(), getHeight());
}

std::vector<Mat> Camera::captureVideo(int frames) {
    std::vector<Mat> out(frames);

    Mat image;
    for (int x = 0; x < frames; x++) {
        cap >> image;
        image.copyTo(out[x]);
    }

    return out;
}
