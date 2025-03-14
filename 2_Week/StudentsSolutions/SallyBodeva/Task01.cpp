// Task01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

const char* FILE_NAME = "result.txt";

void writeSumAndProduct(int a, int b, int c) {

	std::ofstream file(FILE_NAME);

	if (!file.is_open())
	{
		std::cout << "Error";
		return;
	}

	int sum = a + b + c;
	int product = a * b * c;

	file << sum << std::endl;
	file << product;

	file.close();
}

void printDiff(const char* fileName) {

	if (fileName == nullptr)
	{
		return;
	}

	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "Error";
		return;
	}

	int product;
	int sum;

	file >> sum;
	file >> product;

	int diff =  sum - product;

	std::cout << "The diff is: "  << diff;

	file.close();
}

int main()
{
	std::cout << "Please enter three whole numbers: ";

	int a, b, c;
	std::cin >> a >> b >> c;

	writeSumAndProduct(a,b,c);

	printDiff(FILE_NAME);

}
