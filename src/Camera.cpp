#include "Camera.h"

using std::vector;
using cv::Mat;
using cv::Size;

Camera::Camera() : _fps(-1) {
}

Camera::Camera(int which) : _cap(which), _fps(-1) {
    _cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    _cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
}

Camera::~Camera() {

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

Size Camera::getSize() {
    return Size(getWidth(), getHeight());
}

Mat Camera::getNextFrame() {
    Mat image;
    _cap >> image;
    return image;
}

vector<Mat> Camera::captureVideo(int frames) {
    vector<Mat> out(frames);

    Mat image;
    for (int x = 0; x < frames; x++) {
        _cap >> image;
        image.copyTo(out[x]);
    }

    return out;
}
