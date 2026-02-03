#include <iostream>

int main() {
	char letter1, letter2, letter3, letter4, letter5;
	int key;

	std::cout << "---ENCRYPTION TERMINAL---" << '\n';
	std::cout << "Enter a 5-letter password" << '\n';
	std::cin >> letter1 >> letter2 >> letter3 >> letter4 >> letter5;

	std::cout << "Enter your secret key" << '\n';
	std::cin >> key;

		char result1 = letter1 + key;
		char result2 = letter2 + key;
		char result3 = letter3 + key;
		char result4 = letter4 + key;
		char result5 = letter5 + key;

		std::cout << "Here is your encrypted password: " << result1 << result2 << result3 << result4 << result5;

		return 0;
}   

