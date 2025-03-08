#include <iostream>
#include <fstream>

const size_t COUNT_OF_NUMBERS = 3;
const char OUTPUT_FILE[] = "result.txt";

void readArray(int* arr, size_t length) {
	if (arr == nullptr || length == 0) {
		return;
	}

	for (size_t i = 0; i < length; i++)
	{
		std::cin >> arr[i];
	}
}

int getSumOfArray(int* arr, size_t length) {
	if (arr == nullptr || length == 0) {
		return 0;
	}

	int result = 0;
	for (size_t i = 0; i < length; i++)
	{
		result += arr[i];
	}

	return result;
}

int getProductOfArray(int* arr, size_t length) {
	if (arr == nullptr || length == 0) {
		return 0;
	}

	int result = 1;
	for (size_t i = 0; i < length; i++)
	{
		result *= arr[i];
	}

	return result;
}

void printSumAndProductInFile(std::ofstream& stream, int sum, int product) {
	if (!stream.is_open()) {
		return;
	}

	stream << sum << " " << product;
}

void writeSumAndProduct() {
	int arr[COUNT_OF_NUMBERS];

	readArray(arr, COUNT_OF_NUMBERS);
	int sum = getSumOfArray(arr, COUNT_OF_NUMBERS);
	int product = getProductOfArray(arr, COUNT_OF_NUMBERS);

	std::ofstream stream(OUTPUT_FILE);
	printSumAndProductInFile(stream, sum, product);
	stream.close();
}

void printDifferenceOnConsole() {
	int sum;
	int product;

	std::ifstream stream(OUTPUT_FILE);
	stream >> sum >> product;
	stream.close();

	std::cout << sum - product << std::endl;
}

int main() {
	writeSumAndProduct();
	printDifferenceOnConsole();
}