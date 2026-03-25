#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

struct Circle {

	int x = 640, y = 560;
	int radius = 8;
};

void CircleData(Circle& data, int x, int y, int radius){
	data.x = x;
	data.y = y;
	data.radius = radius;
}


void MenuScreen() {

	cv::Mat main_menu = cv::Mat::zeros(720, 1280, CV_8UC3);

	cv::putText(main_menu, "Welcome to Game Test!", cv::Point(450, 175), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 255), 2);
	cv::putText(main_menu, "-- Press Space to Play --", cv::Point(405, 490), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 1);
	cv::putText(main_menu, "Press H to view History", cv::Point(005, 700), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 1);

	cv::namedWindow("Welcome to Game Test!", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Welcome to Game Test!", 100, 100);
	cv::setWindowProperty("Welcome to Game Test!", cv::WND_PROP_ASPECT_RATIO, cv::WINDOW_KEEPRATIO);

	while (true) {

		cv::imshow("Welcome to Game Test!", main_menu);

		if (cv::waitKey(10) == 32) {
			cv::destroyWindow("Welcome to Game Test!");
			break;
		}
	}
}

void GameScreen(Circle& data) {


	cv::Mat main_game = cv::Mat::zeros(720, 1280, CV_8UC3); 

	cv::namedWindow("Playing Game Test!", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Playing Game Test!", 100, 100);
	cv::setWindowProperty("Playing Game Test!", cv::WND_PROP_ASPECT_RATIO, cv::WINDOW_KEEPRATIO);

	while (true) {

		main_game = cv::Mat::zeros(720, 1280, CV_8UC3);

		cv::circle(main_game, cv::Point(data.x, data.y), data.radius, cv::Scalar(255, 255, 255), -1, cv::LINE_AA);

		cv::line(main_game, cv::Point(data.x, data.y), cv::Point(data.x, data.y + 40), cv::Scalar(255, 255, 255), 1, cv::LINE_8);

		cv::line(main_game, cv::Point(data.x, data.y + 20), cv::Point(data.x + 10, data.y + 25), cv::Scalar(255, 255, 255), 1, cv::LINE_8);
		cv::line(main_game, cv::Point(data.x, data.y + 20), cv::Point(data.x - 10, data.y + 25), cv::Scalar(255, 255, 255), 1, cv::LINE_8);

		cv::line(main_game, cv::Point(data.x, data.y + 40), cv::Point(data.x + 10, data.y + 50), cv::Scalar(255, 255, 255), 1, cv::LINE_8);
		cv::line(main_game, cv::Point(data.x, data.y + 40), cv::Point(data.x - 10, data.y + 50), cv::Scalar(255, 255, 255), 1, cv::LINE_8);

		cv::imshow("Playing Game Test!", main_game);

		int key = cv::waitKey(10);

		if (key == 'a') data.x -= 10;
		if (key == 'd') data.x += 10;
		if (key == 'w') data.y -= 10;
		if (key == 's') data.y += 10;

		if (key == 32) {
			cv::destroyWindow("Playing Game Test!");
		break;
		}
	}
}

int main() {

	Circle player;

	MenuScreen();
	GameScreen(player);

	return 0;
}
