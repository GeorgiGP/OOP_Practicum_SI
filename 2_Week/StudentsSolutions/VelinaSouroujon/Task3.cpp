#include <iostream>
#include <fstream>

using namespace std;

const int MAX_COLORS_COUNT = 128;
const char DELIMITER = '|';
const int MIN_RED = 250;

const int RED_MULTIPLIER = 65536;
const int GREEN_MULTIPLIER = 256;
const int BLUE_MULTIPLIER = 1;

const char INPUT_FILE[] = "input.txt";
const char OUTPUT_FILE[] = "output.txt";
const char OUTPUT_RED_FILE[] = "red.txt";

struct Color
{
    unsigned char red;
	unsigned char green;
	unsigned char blue;
};

bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

Color getColor(size_t number)
{
	Color color;

	color.red = number / RED_MULTIPLIER;
	color.green = (number % RED_MULTIPLIER) / GREEN_MULTIPLIER;
	color.blue = (number % GREEN_MULTIPLIER) / BLUE_MULTIPLIER;

	return color;
}

void addColorToArray(Color* colors, size_t& number, unsigned& idx, int& colorsCount)
{
	if (colors == nullptr)
	{
		return;
	}

	Color color = getColor(number);
	colors[idx] = color;
	idx++;
	colorsCount++;
	number = 0;
}

Color* readColors(ifstream& inFile, int& colorsCount)
{
	if (!inFile.is_open())
	{
		return nullptr;
	}

	colorsCount = 0;
	Color* colors = new Color[MAX_COLORS_COUNT];
	size_t currNumber = 0;
	unsigned idx = 0;
	char ch;

	while (inFile.get(ch))
	{
		if (isDigit(ch))
		{
			currNumber = (10 * currNumber) + (ch - '0');
		}
		else if (ch == DELIMITER)
		{
			addColorToArray(colors, currNumber, idx, colorsCount);

			if (idx >= MAX_COLORS_COUNT)
			{
				return colors;
			}
		}
	}
	addColorToArray(colors, currNumber, idx, colorsCount);

	return colors;
}

size_t getNumberFromColor(const Color& color)
{
	return color.red * RED_MULTIPLIER + color.green * GREEN_MULTIPLIER + color.blue * BLUE_MULTIPLIER;
}

bool allColors(const Color& color)
{
	return true;
}

bool redColors(const Color& color)
{
	return color.red > MIN_RED;
}

bool writeColorsToFile(ofstream& outFile, const Color* colors, int length, bool (*condition)(const Color&) = allColors)
{
	if (colors == nullptr || length <= 0)
	{
		return false;
	}
	if (!outFile.is_open())
	{
		return false;
	}

	bool isFirst = true;

	for (size_t i = 0; i < length; i++)
	{
		if (!condition(colors[i]))
		{
			continue;
		}

		size_t number = getNumberFromColor(colors[i]);

		if (isFirst)
		{
			isFirst = false;
		}
		else
		{
			outFile << DELIMITER;
		}
		outFile << number;
	}

	return true;
}

int main()
{
	ifstream inFile(INPUT_FILE);
	ofstream outFile(OUTPUT_FILE);
	ofstream outRedFile(OUTPUT_RED_FILE);

	if (!inFile.is_open() || !outFile.is_open() || !outRedFile.is_open())
	{
		cout << "Error opening files!" << endl;
		return -1;
	}

	int colorsCount;
	Color* colors = readColors(inFile, colorsCount);
	inFile.close();

	if (colors == nullptr)
	{
		cout << "Error reading colors!" << endl;
		return -2;
	}

	writeColorsToFile(outFile, colors, colorsCount);
	outFile.close();

	writeColorsToFile(outRedFile, colors, colorsCount, redColors);

	delete[] colors;
	outRedFile.close();

	return 0;
}
