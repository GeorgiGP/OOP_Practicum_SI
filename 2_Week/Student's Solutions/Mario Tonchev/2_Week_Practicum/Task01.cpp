#include <iostream>
#include <fstream>
using namespace std;

const char* FILE_NAME = "result.txt";

void SaveSumAndProduct(int num1, int num2, int num3) {
	int sum = num1 + num2 + num3;
	int product = num1 * num2 * num3;

	ofstream ofStream(FILE_NAME);

	if (!ofStream.is_open())
	{
		cout << "Error openning file!";
		return;
	}

	ofStream << sum << " " << product;

	ofStream.close();
}

void ReadResultAndGetDifference() {
	ifstream ifStream(FILE_NAME);

	if (!ifStream.is_open())
	{
		cout << "Error openning file!";
		return;
	}

	int diff = 0;
	int sum = 0;
	int product = 0;

	ifStream >> sum >> product;
	ifStream.close();

	diff = sum - product;

	cout << diff;
}

int main() {
	SaveSumAndProduct(4, 5, 6);
	ReadResultAndGetDifference();
}