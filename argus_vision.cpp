#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::VideoCapture cap(0);
    cv::Mat webcam;
    cv::Mat webcam_hsv,webcam_gray, webcam_blackwhite;

    int target_x = 0, target_y = 0;
   

    if (!cap.isOpened()) {
        std::cout << "Camera is not detected!" << '\n';

        return -1;

    }

    while (true) {

        cap >> webcam;

        cv::cvtColor(webcam, webcam_hsv, cv::COLOR_BGR2HSV);
        cv::cvtColor(webcam, webcam_gray, cv::COLOR_BGR2GRAY);
        cv::threshold(webcam_gray, webcam_blackwhite, 240, 255, cv::THRESH_BINARY); // gotta apply to grayscale, not hsv

        cv::Moments m = cv::moments(webcam_blackwhite, true);

        if (m.m00 > 200) { // 200 kinda good to filter noise, test more

            target_x = m.m10 / m.m00; // m00 = number of white pixels -- m10 = sum of x positions of white pixels -- m01 = sum of y positions of white pixels
            target_y = m.m01 / m.m00;

            cv::circle(webcam, cv::Point(target_x, target_y), 5, cv::Scalar(0, 0, 255), -1);

            std::cout << "TARGET DETECTED AT -> X: " << target_x << " | Y: " << target_y << std::endl;
        }

        cv::imshow("Argus X-1 Vision Test: Main Camera", webcam);
        cv::imshow("Argus X-1 Vision Test: Main Camera (HSV)", webcam_hsv);
        cv::imshow("Argus X-1 Vision Test: Main Camera (Black & White", webcam_blackwhite); 

        if (webcam.empty())
        break;

        if (cv::waitKey(33) == 27) // 1000/33 = 30fps
        break;
    }
    cv::destroyAllWindows();
    return 0;
}
