#include "Video.h"

Video::Video(const string filename) {
    _cap.open(filename);
    _fps = _cap.get(CV_CAP_PROP_FPS);
}
