#pragma once
#include <opencv2/opencv.hpp>

struct VisionState {
    float target_x = 0, target_y = 0;
    float laser_x = 0, laser_y = 0;
    double target_area = 0, laser_area = 0;
    bool target_detected = false;
    bool laser_detected = false;
    bool locked = false;
    cv::Mat frame;
    cv::Mat hsv;
    cv::Mat target_mask;
    cv::Mat laser_mask;
};

VisionState processFrame(cv::VideoCapture& cap,
    int min_hue, int max_hue,
    int min_sat, int max_sat,
    int min_val, int max_val);
