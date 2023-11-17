#include <opencv2/opencv.hpp>

class HandTrackingModule {
public:
    std::vector<cv::Point> findHand(cv::Mat &frame) {
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0);
        cv::threshold(frame, frame, 100, 255, cv::THRESH_BINARY);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(frame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        std::vector<cv::Point> handPoints;

        for (const auto &contour : contours) {
            double area = cv::contourArea(contour);

            if (area > 1000) {
                cv::Moments M = cv::moments(contour);
                int cx = static_cast<int>(M.m10 / M.m00);
                int cy = static_cast<int>(M.m01 / M.m00);

                handPoints.push_back(cv::Point(cx, cy));
            }
        }

        return handPoints;
    }
};

int main() {
    cv::VideoCapture video(0, cv::CAP_DSHOW);
    cv::Mat frame;

    HandTrackingModule handTracker;

    while (true) {
        video.read(frame);

        if (frame.empty()) {
            break;
        }

        std::vector<cv::Point> handPoints = handTracker.findHand(frame);

        for (const auto &point : handPoints) {
            cv::circle(frame, point, 5, cv::Scalar(0, 255, 0), -1);
        }

        cv::imshow("Hand Tracking", frame);

        if (cv::waitKey(1) == 27) {  // Pressione Esc para sair
            break;
        }
    }

    return 0;
}
