#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "HandTrackingModule.hpp" // Assuming you have a hand tracking module header file

int main() {
    cv::VideoCapture video(0, cv::CAP_DSHOW);

    video.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    video.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    HandDetector detector(0.8, 1);

    std::vector<int> distPixels = {300, 245, 200, 170, 145, 130, 112, 103, 93, 87, 80, 75, 70, 67, 62, 59, 57};
    std::vector<int> distCM = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
    cv::Mat coef;
    cv::polyfit(distPixels, distCM, 2, coef);

    while (true) {
        cv::Mat img;
        video.read(img);

        std::vector<Hand> hands = detector.findHands(img, false);

        if (!hands.empty()) {
            auto lmlist = hands[0].lmList;
            auto [x, y, w, h] = hands[0].bbox;
            auto [x1, y1, _] = lmlist[5];
            auto [x2, y2, _] = lmlist[17];
            auto dist = std::abs(x2 - x1);
            auto distCMT = coef.at<double>(0) * std::pow(dist, 2) + coef.at<double>(1) * dist + coef.at<double>(2);

            std::cout << dist << " " << distCMT << std::endl;
            cv::rectangle(img, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(255, 0, 255), 3);
            cv::putText(img, std::to_string(static_cast<int>(distCMT)) + " cm", cv::Point(x + 5, y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 255));
        }

        cv::imshow("Imagem", img);
        cv::waitKey(1);
    }

    return 0;
}
