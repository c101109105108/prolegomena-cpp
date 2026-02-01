#include <iostream>

int main()

{
	double resistance;
	double current;
	double voltage;

	std::cout << "Enter Current (Amps): ";
	std::cin >> current;

	std::cout << "Enter Resistance (ohms): ";
	std::cin >> resistance;

	voltage = current * resistance;

	std::cout << "Calculated Voltage is: " << voltage << "V" << '\n';

	return 0;
}
