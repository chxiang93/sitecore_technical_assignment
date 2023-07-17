#include <iostream>
#include <string>
#include <cctype>

bool palindromeChecker(const std::string& inputString, const std::string& trashSymbolsString) {
	int leftPos = 0;
	int rightPos = inputString.length() - 1;

	while (leftPos < rightPos) {
		char leftChar = std::tolower(inputString[leftPos]);
		char rightChar = std::tolower(inputString[rightPos]);

		while (!(trashSymbolsString.find(leftChar) == std::string::npos)) {
			leftPos++;
			leftChar = std::tolower(inputString[leftPos]);
		}

		while (!(trashSymbolsString.find(rightChar) == std::string::npos)) {
			rightPos--;
			rightChar = std::tolower(inputString[rightPos]);
		}

		if (leftChar != rightChar) {
			return false;
		}

		leftPos++;
		rightPos--;
	}

	return true;
}

int main() {
	// Test Example 1
	std::string inputStr1 = "a@b!!b$a";
	std::string trashSymbols1 = "!@$";
	std::cout << "Example 1:\n";
	std::cout << "InputString: " << inputStr1;
	std::cout << "\nTrashSymbolsString: " << trashSymbols1;
	std::cout << "\nResult for example 1: " << std::boolalpha << palindromeChecker(inputStr1, trashSymbols1);

	// Test Example 2
	std::string inputStr2 = "?Aa#c";
	std::string trashSymbols2 = "#?";
	std::cout << "\n\n\nExample 2:\n";
	std::cout << "InputString: " << inputStr2;
	std::cout << "\nTrashSymbolsString: " << trashSymbols2;
	std::cout << "\nResult for example 2: " << std::boolalpha << palindromeChecker(inputStr2, trashSymbols2);

	return 0;
}