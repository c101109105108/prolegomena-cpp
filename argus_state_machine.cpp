#include <argus.vision.h>
#include <argus.core.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <thread>
#include <fstream>
#include <pigpio.h>  

constexpr int gpio_x = 12;
constexpr int gpio_y = 13;

enum ArgusState {

	IDLE,
	SCAN,
	TRACK,
	LOCKED,
};

int main() {

	std::cout << "[SYSTEM] INITIALIZING..." << '\n';

	ControlState pid_core;
	ArgusState initializing_state = IDLE;

	if (gpioInitialise() < 0) {
		std::cerr << "[SYSTEM] PIGPIO COULD NOT BE INITIALIZED" << '\n'; //if crashes cout is too late
		return -1;
	}

	cv::VideoCapture cap(0);

	if (!cap.isOpened()) {
		std::cerr << "[SYSTEM] CAMERA COULDD NOT BE INITIALIZED" << '\n';
		gpioTerminate();
		return -1;
	}

	gpioServo(gpio_x, 1365);
	gpioServo(gpio_y, 1365);

	int min_hue = 0, max_hue = 179; //test
	int min_sat = 0, max_sat = 255;
	int min_val = 0, max_val = 255;

	auto start_time = std::chrono::steady_clock::now();
	auto last_time = start_time;

	std::cout << "ARGUS IS READY TO SCAN" << '\n';

	while (true) {

	auto current_time = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = current_time - last_time;
	double dt = diff.count();
	last_time = current_time;

	VisionState vision_data = processFrame(cap, min_hue, max_hue, min_sat, max_sat, min_val, max_val);

	switch (initializing_state){
