#include <iostream>
#include <fstream>
using namespace std;

struct Color {
	int red;
	int green;
	int blue;
};

int GetNumbersInFileCount(ifstream& ifStream) {
	if (!ifStream.is_open())
	{
		return -1;
	}

	int count = 0;
	char buffer[100];

	while (ifStream.getline(buffer, 100, '|'))
	{
		count++;
	}

	return count;
}

Color* GetRgbValuesFromFile(ifstream& ifStream) {
	if (!ifStream.is_open())
	{
		return nullptr;
	}

	int nums = GetNumbersInFileCount(ifStream);

	ifStream.clear();
	ifStream.seekg(0, ios::beg);

	Color* colors = new Color[nums];

	char currentRGBCode[100];
	int cntr = 0;

	while (ifStream.getline(currentRGBCode, 100, '|'))
	{
		int RGBCodeAsNum = atoi(currentRGBCode);

		colors[cntr].red = RGBCodeAsNum / 65536;
		colors[cntr].green = (RGBCodeAsNum % 65536) / 256;
		colors[cntr++].blue = RGBCodeAsNum % 256;
	}

	return colors;
}

void SaveColorsToFile(ofstream& ofStream, Color* colors, int size) {
	if (!ofStream.is_open())
	{
		cout << "Error" << endl;
		return;
	}

	if (colors == nullptr)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		int rgbCode = (colors[i].red * 65536) + (colors[i].green * 256) + colors[i].blue;
		ofStream << rgbCode << '|';
	}
}

void SaveRedNuanceColorsToFile(ofstream& ofStream, Color* colors, int size) {
	if (!ofStream.is_open())
	{
		cout << "Error" << endl;
		return;
	}

	if (colors == nullptr)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		if (colors[i].red > 250)
		{
			int rgbCode = (colors[i].red * 65536) + (colors[i].green * 256) + colors[i].blue;
			ofStream << rgbCode << '|';
		}
	}
}

int main() {
	//Reading values from file
	const char FILE_NAME[] = "Colors.txt";
	ifstream ifStream(FILE_NAME);

	Color* result = GetRgbValuesFromFile(ifStream);

	ifStream.close();
	delete[] result;

	//Saving values to file
	const int COLORS_SIZE = 3;
	Color colors[COLORS_SIZE] = { {123, 43, 12}, {57, 200, 108}, {14, 5, 60} };

	ofstream ofStream(FILE_NAME, ios::app);
	SaveColorsToFile(ofStream, colors, COLORS_SIZE);

	ofStream.close();

	//Saving only values with red greater than 250 to file
	const char RED_FILE_NAME[] = "red.txt";

	Color colors2[COLORS_SIZE] = { {250, 43, 12}, {249, 200, 108}, {251, 5, 60} };

	ofstream ofStreamRed(RED_FILE_NAME, ios::app);
	SaveRedNuanceColorsToFile(ofStreamRed, colors2, COLORS_SIZE);

	ofStreamRed.close();
}