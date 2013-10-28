#include "Frame.h"

using std::vector;
using cv::KeyPoint;
using cv::Mat;

Frame::Frame(Mat m) : _image(m.clone()) {

}

void Frame::calculate(CornerDetector& cd) {
    _keyPoints = cd.getKeyPoints(_image);
}

vector<KeyPoint> Frame::getKeyPoints() const {
    return _keyPoints;
}

double Frame::getAverageSlope() const {
    double almostSum = 0;
    for (uint32_t i = 0; i < _keyPoints.size(); ++i) {
        double localSum = 0;
        for (uint32_t j = 0; j < _keyPoints.size(); ++j) {
            if (i == j) continue;
            if (_keyPoints[i].pt.x == _keyPoints[j].pt.x) continue;
            localSum += (_keyPoints[i].pt.y - _keyPoints[j].pt.y) /
                (_keyPoints[i].pt.x - _keyPoints[j].pt.x);
        }
        almostSum += (localSum / (_keyPoints.size() - 1));
    }
    almostSum /= _keyPoints.size();
    return almostSum;
}

double Frame::getAverageX() const {
    double sum = 0;
    for (uint32_t i = 0; i < _keyPoints.size(); ++i) {
        sum += _keyPoints[i].pt.x;
    }
    return sum / _keyPoints.size();
}

double Frame::getAverageY() const {
    double sum = 0;
    for (uint32_t i = 0; i < _keyPoints.size(); ++i) {
        sum += _keyPoints[i].pt.y;
    }
    return sum / _keyPoints.size();
}

double Frame::getStdDevX() const {
    double sum = std::accumulate(begin(_keyPoints), end(_keyPoints), 0.0,
            [] (const double x, const KeyPoint& y) {
            return x + y.pt.x;
            });
    double m = sum / _keyPoints.size();
    double acc = 0.0;
    std::for_each(begin(_keyPoints), end(_keyPoints), [&](const KeyPoint& k) {
            acc += (k.pt.x - m) * (k.pt.x - m);
            });
    return sqrt(acc/_keyPoints.size());
}

double Frame::getStdDevY() const {
    double sum = std::accumulate(begin(_keyPoints), end(_keyPoints), 0.0,
            [] (const double x, const KeyPoint& y) {
            return x + y.pt.y;
            });
    double m = sum / _keyPoints.size();
    double acc = 0.0;
    std::for_each(begin(_keyPoints), end(_keyPoints), [&](const KeyPoint& k) {
            acc += (k.pt.y - m) * (k.pt.y - m);
            });
    return sqrt(acc/_keyPoints.size());
}

/* Equation: where E is the sum operator
 *                     n*E(x*y) - E(x)*E(y)
 * r = --------------------------------------------------
 *     √((n*E(x^2) - E(x)*E(x)) * (n*E(y^2) - E(y)*E(y)))
 */
double Frame::getR() const {
    double sumX = 0;
    double sumY = 0;
    double sumX2 = 0;
    double sumY2 = 0;
    double sumXY = 0;
    for (uint32_t i = 0; i < _keyPoints.size(); ++i) {
        int x = _keyPoints[i].pt.x;
        int y = _keyPoints[i].pt.y;
        sumX += x;
        sumX2 += x * x;
        sumY += y;
        sumY2 += y * y;
        sumXY += x * y;
    }
    double num = _keyPoints.size() * sumXY - sumX * sumY;
    double denom = sqrt((_keyPoints.size()*sumX2 - sumX * sumX)*
            (_keyPoints.size()*sumY2 - sumY * sumY));
    return -num / denom;
}

/* Equation:
 *             Sy
 * slope = r * --
 *             Sx
 */
double Frame::getLSRLSlope() const {
    return getR() * getStdDevY() / getStdDevX();
}
