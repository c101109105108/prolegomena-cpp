#include <iostream>
#include <cstdlib> 
#include <string>
#include <vector>

double calculate_voltage(double i, double r) {
	return i * r;
}

double calculate_current(double v, double r) {
	return v / r;
}

double calculate_resistance(double v, double i) {
	return v / i;
}

double calculate_power(double v, double i) {
	return v * i;
}

double calculate_power_from_voltage_resistance(double v, double r) {
	return (v * v) / r;
}

double calculate_power_from_current_resistance(double i, double r) {
	return (i * i) * r;
}

void clearscreen() {
	std::cout << "\033[2J\033[H" << std::flush;
}

int main() {

	std::vector<double> history;

	bool keepRunning = true;
	std::string userInput;
	do {

		int choice;
		int choice2;
		int choice3;

		double r;
		double i;
		double v;
		double p;

		std::cout << "1. Ohm's Law Calculator\n";
		std::cout << "\n2. Power Calculator\n";
		std::cout << "\n3. View History\n";
		std::cout << "\n4. Exit\n";
		std::cout << "\n";
		std::cin >> choice;


		clearscreen();

		if (choice == 1) {

			std::cout << "1. Voltage Calculator [I * R]" << '\n';
			std::cout << "\n2. Current Calculator [V / R]" << '\n';
			std::cout << "\n3. Resistance Calculator [V / I]" << '\n';
			std::cout << "\n";
			std::cin >> choice2;


			clearscreen();
			if (choice2 == 1) {

				std::cout << "Enter Current (A): ";
				std::cin >> i;

				std::cout << "Enter Resistance (ohms): ";
				std::cin >> r;

				double result = calculate_voltage(i, r);
				std::cout << "Voltage is: " << result << " V" << '\n';
				history.push_back(result);
			}

			else if (choice2 == 2) {

				std::cout << "Enter Voltage (V): ";
				std::cin >> v;

				std::cout << "Enter Resistance (ohms): ";
				std::cin >> r;

				double result = calculate_current(v, r);
				std::cout << "Calculated Current is: " << result << " A";
				history.push_back(result);
			}

			else if (choice2 == 3) {

				std::cout << "Enter Voltage (V): ";
				std::cin >> v;

				std::cout << "Enter Current (A): ";
				std::cin >> i;

				double result = calculate_resistance(v, i);
				std::cout << "Calculated Resistance is: " << result << " ohms" << '\n';
				history.push_back(result);

			}

			else {
				clearscreen();
				std::cout << "Invalid Input.\n";
			}

		}

		else if (choice == 2) {

			std::cout << "1. Using Voltage and Resistance [V^2 / R] " << '\n';
			std::cout << "\n2. Using Current and Resistance [I^2 * R] " << '\n';
			std::cout << "\n3. Using Voltage and Current [V * I]" << '\n';
			std::cout << "\n";
			std::cin >> choice3;

			if (choice3 == 1) {

				clearscreen();

				std::cout << "Enter Voltage (V): ";
				std::cin >> v;

				std::cout << "Enter Resistance (ohms): ";
				std::cin >> r;

				double result = calculate_power_from_voltage_resistance(v, r);
				std::cout << "Power is: " << result << " W";
				history.push_back(result);
			}

			if (choice3 == 2) {

				clearscreen();

				std::cout << "Enter Current (A): ";
				std::cin >> i;

				std::cout << "Enter Resistance (ohms): ";
				std::cin >> r;

				double result = calculate_power_from_current_resistance(i, r);
				std::cout << "Power is: " << result << " W" << '\n';
				history.push_back(result);

			}
			if (choice3 == 3) {

				clearscreen();

				std::cout << "Enter Voltage (V): ";
				std::cin >> v;

				std::cout << "Enter Current (A): ";
				std::cin >> i;

				double result = calculate_power(v, i);
				std::cout << "Power is: " << result << " W";
				history.push_back(result);
			}

			else {
				clearscreen();
				std::cout << "Invalid Input.\n";
			}

		}
		else if (choice == 3) {
			std::cout << "--- Calculation History ---" << '\n';
			if (history.empty()) {
				clearscreen();
				std::cout << "No history yet :3\n";
			}
			else {
				for (double n : history) {
					std::cout << n << '\n';
				}
			}

		}
		else if (choice == 4) {
			keepRunning = false;
			std::cout << "Bye!" << '\n';
			break;
		}

		else {
			clearscreen();
			std::cout << "Invalid Input.\n";
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

	} while (keepRunning);
	return 0;
}
