#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::VideoCapture cap(0);
    cv::Mat webcam_main;
    cv::Mat webcam_hsv,webcam_gray, webcam_binary_mask;

    int min_hue = 0, min_saturation = 0, min_value = 0;
    int max_hue = 179, max_saturation = 255, max_value = 255;
    int target_x = 0, target_y = 0;

    cv::namedWindow("Argus X-1 Vision: Color Calibration");
    cv::createTrackbar("Hue Min", "Argus X-1 Vision: Color Calibration", &min_hue, 179);
    cv::createTrackbar("Hue Max", "Argus X-1 Vision: Color Calibration", &max_hue, 179); 
    cv::createTrackbar("Sat Min", "Argus X-1 Vision: Color Calibration", &min_saturation, 255);
    cv::createTrackbar("Sat Max", "Argus X-1 Vision: Color Calibration", &max_saturation, 255);
    cv::createTrackbar("Val Min", "Argus X-1 Vision: Color Calibration", &min_value, 255);
    cv::createTrackbar("Val Max", "Argus X-1 Vision: Color Calibration", &max_value, 255);

    if (!cap.isOpened()) {
        std::cout << "[ERROR] CAMERA NOT DETECTED!" << '\n';

        return -1;

    }

    while (true) {

        cap >> webcam_main;

        cv::cvtColor(webcam_main, webcam_hsv, cv::COLOR_BGR2HSV);

        cv::Scalar lower_orange(min_hue, min_saturation, min_value);
        cv::Scalar upper_orange(max_hue, max_saturation, max_value);

        cv::inRange(webcam_hsv, lower_orange, upper_orange, webcam_binary_mask);
        cv::Moments m = cv::moments(webcam_binary_mask, true);

        if (m.m00 > 150) { 

            target_x = m.m10 / m.m00; 
            target_y = m.m01 / m.m00;

            cv::circle(webcam_main, cv::Point(target_x, target_y), 4, cv::Scalar(0, 0, 255), -1);

            std::cout << "TARGET DETECTED AT -> X: " << target_x << " | Y: " << target_y << '\n'; 
        }

        else {
            std::cout << "Searching for a target..." << '\n';
        }

        cv::imshow("Argus X-1 Vision: Main Source", webcam_main);
        cv::imshow("Argus X-1 Vision: HSV Space", webcam_hsv);
        cv::imshow("Argus X-1 Vision: Binary Mask", webcam_binary_mask);

        if (webcam_main.empty())
        break;

        if (cv::waitKey(33) == 27) 
        break;
    }
    cv::destroyAllWindows();
    return 0;
}
