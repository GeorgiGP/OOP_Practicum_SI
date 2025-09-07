// Task03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

const char* FILE_NAME = "test.txt";
const char* OUTPUT_RED_FILE = "red.txt";
const size_t MAX_BUFFER_LEN = 256;
const size_t RED_CODE = 65536;
const size_t GREEN_CODE = 256;

struct Color
{
	int Red;
	int Green;
	int Blue;
};

int convertToInt(char symbol) {
	return symbol - '0';
}

int getNumsCount(std::ifstream& ifs) {

	if (!ifs.is_open())
	{
		std::cout << "Error";
		return -1;
	}

	int count = 1;

	while (!ifs.eof())
	{
		if (ifs.get() == '|')
		{
			count++;
		}
	}

	return count;
}

size_t* readNums(std::ifstream& ifs, int& arraySize) {

	if (!ifs.is_open())
	{
		std::cout << "Error";
		return nullptr;
	}

	char buffer[MAX_BUFFER_LEN];

	ifs.getline(buffer, MAX_BUFFER_LEN);

	ifs.seekg(0, std::ios::beg);

	int numbersCount = getNumsCount(ifs);

	ifs.clear();

	ifs.seekg(0, std::ios::beg);

	size_t* nums = new size_t[numbersCount];
	int insertIndex = 0;



	for (int i = 0; i < numbersCount; i++)
	{
		size_t currentNum = 0;
		char symbol = ifs.get();
		while (symbol != '|' && !ifs.eof())
		{
			currentNum *= 10;
			currentNum += convertToInt(symbol);
			symbol = ifs.get();
		}
		nums[insertIndex++] = currentNum;
	}
	arraySize = numbersCount;
	return nums;
}

Color* getColors(size_t* nums, int arrSize) {

	if (nums == nullptr)
	{
		return nullptr;
	}

	Color* colors = new Color[arrSize];
	int insertIndex = 0;
	for (int i = 0; i < arrSize; i++)
	{
		int red = nums[i] / RED_CODE;
		nums[i] = nums[i] - (red * RED_CODE);
		int green = nums[i] / GREEN_CODE;
		int blue = nums[i] - (green * GREEN_CODE);
		Color c = { red, green,blue };

		colors[insertIndex++] = c;
	}

	return colors;
}

void printColors( Color* colors, int arrSize) {

	if (colors== nullptr)
	{
		return;
	}

	std::ofstream file(FILE_NAME, std::ios::out | std::ios::app);

	if (!file.is_open()) {
		return;
	}

	file << std::endl;
	for (int i = 0; i < arrSize; i++)
	{
		file << "RGB = R(" << colors[i].Red << ") + G(" << colors[i].Green << ") + B(" << colors[i].Blue << ")" << std::endl;
	}
	file.close();
}

void printRedColor(Color* colors, int arrSize) {

	if (colors == nullptr)
	{
		return;
	}

	std::ofstream file(OUTPUT_RED_FILE);

	if (!file.is_open()) {
		return;
	}

	for (int i = 0; i < arrSize; i++)
	{
		if (colors[i].Red > 250)
		{
			file << "RGB = R(" << colors[i].Red << ") + G(" << colors[i].Green << ") + B(" << colors[i].Blue << ")" << std::endl;
		}
	}
	file.close();
}


int main()
{
	std::ifstream file(FILE_NAME);

	int length = 0;
	size_t* nums = readNums(file, length);

	file.close();

	Color* colors = getColors(nums,length);

	file.close();

	delete[] nums;

	printColors(colors,length);

	printRedColor(colors, length);

	delete[] colors;

}
