#include <vector>
#include <opencv2/opencv.hpp>

#include "CornerDetector.h"

class Frame {
    public:
        double getAverageX() const;
        double getAverageY() const;
        double getStdDevX() const;
        double getStdDevY() const;
        double getR() const;
        double getLSRLSlope() const;
        double getAverageSlope() const;
        void calculate(CornerDetector& cd); 
        std::vector<cv::KeyPoint> getKeyPoints() const;
        Frame(cv::Mat);
    private:
        std::vector<cv::KeyPoint> _keyPoints;
        cv::Mat _image;
};
