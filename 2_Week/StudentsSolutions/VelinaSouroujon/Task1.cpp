#include <iostream>
#include <fstream>
using namespace std;

void readInput(int* nums, int length)
{
	if (nums == nullptr || length <= 0)
	{
		return;
	}

	cout << "Enter " << length << " numbers: ";

	for (size_t i = 0; i < length; i++)
	{
		cin >> nums[i];
	}
}

long getDifference(ifstream& inFile)
{
	if (!inFile.is_open())
	{
		cerr << "File is not open!";
		return -1;
	}

	long sum, product;
	inFile >> sum >> product;

	return sum - product;
}

bool writeSumProduct(ofstream& outFile, const int* nums, int size)
{
	if (nums == nullptr || size <= 0)
	{
		return false;
	}
	if (!outFile.is_open())
	{
		return false;
	}

	long sum = 0;
	long product = 1;

	for (size_t i = 0; i < size; i++)
	{
		int currNum = nums[i];
		sum += currNum;
		product *= currNum;
	}

	outFile << sum << '\n';
	outFile << product << '\n';

	return true;
}

int main()
{
	const int NUMS_COUNT = 3;
	int nums[NUMS_COUNT];
	readInput(nums, NUMS_COUNT);

	ofstream outFile("result.txt");
	writeSumProduct(outFile, nums, NUMS_COUNT);
	outFile.close();

	ifstream inFile("result.txt");
	long diff = getDifference(inFile);
	inFile.close();

	cout << "Difference between sum and product: " << diff;

	return 0;
}
