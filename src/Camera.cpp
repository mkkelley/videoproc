#include "Camera.h"


Camera::Camera() : _cap(0), _fps(-1) {

}

double Camera::getFps() {
    if (_fps != -1) {
        return _fps;
    }
    if (!_cap.isOpened()) {
        return -1;
    }

    time_t start, end;
    double fps;
    double sec;
    int counter = 0;
    time(&start);
    Mat image;
    while(counter++ < 120) {
        _cap >> image;
    }
    time(&end);
    sec = difftime(end, start);
    fps = counter / sec;
    _fps = fps;
    return fps;
}

double Camera::getWidth() {
    return _cap.get(CV_CAP_PROP_FRAME_WIDTH);
}

double Camera::getHeight() {
    return _cap.get(CV_CAP_PROP_FRAME_HEIGHT);
}

cv::Size Camera::getSize() {
    return cv::Size(getWidth(), getHeight());
}

Mat Camera::getNextFrame() {
    Mat image;
    Mat image2;
    _cap >> image;
    image.copyTo(image2);
    return image2;
}

std::vector<Mat> Camera::captureVideo(int frames) {
    std::vector<Mat> out(frames);

    Mat image;
    for (int x = 0; x < frames; x++) {
        _cap >> image;
        image.copyTo(out[x]);
    }

    return out;
}
