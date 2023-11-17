#ifndef HANDTRACKINGMODULE_HPP
#define HANDTRACKINGMODULE_HPP

#include <opencv2/opencv.hpp>

class HandTrackingModule {
public:
    std::vector<cv::Point> findHand(cv::Mat &frame);
};

#endif // HANDTRACKINGMODULE_HPP
