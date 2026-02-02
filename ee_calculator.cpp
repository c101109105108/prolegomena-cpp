#include <iostream>
#include <cstdlib> 
#include <string>

double calculatevoltage(double current, double resistance) {
	return current * resistance;
}

double calculatecurrent(double voltage, double resistance) {
	return voltage / resistance;
}

double calculateresistance(double voltage, double current) {
	return voltage / current;
}

double calculatepower(double voltage, double current) {
	return voltage * current;
}

void clearscreen() {
	std::cout << "\033[2J\033[H" << std::flush;
}

int main() {

	bool keepRunning = true;
	std::string userInput;
	do {

		int choice;
		int choice2;

		double resistance;
		double current;
		double voltage;
		double power;

		std::cout << "\n1. Ohm's Law Calculator\n";
		std::cout << "\n2. Power Calculator\n";
		std::cout << "\n3. Test\n";
		std::cout << "\n";
		std::cin >> choice;

		clearscreen();

		if (choice == 1) {

			std::cout << "1. Voltage Calculator\n";
			std::cout << "\n2. Current Calculator\n";
			std::cout << "\n3. Resistance Calculator\n";
			std::cout << "\n";
			std::cin >> choice2;


			clearscreen();
			if (choice2 == 1) {

				std::cout << "Enter Current (A): ";
				std::cin >> current;

				std::cout << "Enter Resistance (ohms): ";
				std::cin >> resistance;

				double result = calculatevoltage(current, resistance);
				std::cout << "Voltage is: " << result << " V" << '\n';
			}

			else if (choice2 == 2) {

				std::cout << "Enter Voltage (V): ";
				std::cin >> voltage;

				std::cout << "Enter Resistance (ohms): ";
				std::cin >> resistance;

				double result = calculatecurrent(voltage, resistance);
				std::cout << "Calculated Current is: " << result << " A" << '\n';
			}

			else if (choice2 == 3) {

				std::cout << "Enter Voltage (V): ";
				std::cin >> voltage;

				std::cout << "Enter Current (A): ";
				std::cin >> current;

				double result = calculateresistance(voltage, current);
				std::cout << "Calculated Resistance is: " << result << " ohms" << '\n';

			}

			else {
				std::cout << "Invalid Input.\n";
			}

		}

		else if (choice == 2) {

			std::cout << "Enter Voltage (V): ";
			std::cin >> voltage;

			std::cout << "Enter Current (A): ";
			std::cin >> current;

			double result = calculatepower(voltage, current);
			std::cout << "Calculated Power is: " << result << " W" << '\n';
		}

		std::cout << "\nWould you like to continue? (Yes or No): ";
		std::cin >> userInput;

		if (userInput == "yes" || userInput == "y" || userInput == "Yes" || userInput == "YES") {
			keepRunning = true;
			clearscreen();
		}
		else if (userInput == "no" || userInput == "n" || userInput == "No" || userInput == "NO") {
			keepRunning = false;
			std::cout << "Bye!\n";
		}

		else {
			std::cout << "Invalid Input.\n";
		}

	} while (keepRunning);
	return 0;
}
