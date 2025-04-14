
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>

const char FILENAME[] = "file.txt";
const char REDFILE[] = "red.txt";
const size_t MAX_DIGITS_COUNT_IN_COLOR_CODE = 9;

const size_t RED_CONSTANT = 1 << 16;
const size_t GREEN_CONSTANT = 1 << 8;

const size_t MIN_RED_VALUE = 251;

struct Color {
	size_t red;
	size_t green;
	size_t blue;
};

size_t countSymbols(std::ifstream& stream, char symbol) {
	if (!stream.is_open()) {
		return 0;
	}

	std::streampos positionStart = stream.tellg();

	size_t numberOfSymbols = 0;
	int currentSymbol;
	while ((currentSymbol = stream.get()) != EOF) {
		if (symbol == (char)currentSymbol) {
			numberOfSymbols++;
		}
	}

	stream.clear();
	stream.seekg(positionStart);

	return numberOfSymbols;
}

size_t fromStringToNatural(const char* str) {
	if (str == nullptr) {
		return 0;
	}

	size_t result = 0;
	while (*str != '\0') {
		result *= 10;
		result += *str - '0';
		str++;
	}

	return result;
}

size_t encryptColor(Color& color) {
	return color.red * RED_CONSTANT + color.green * GREEN_CONSTANT + color.blue;
}

Color decryptColor(size_t colorCode) {
	size_t blue = colorCode % GREEN_CONSTANT;
	colorCode -= blue;

	size_t green = (colorCode % RED_CONSTANT) / GREEN_CONSTANT;
	colorCode -= green;

	size_t red = colorCode / RED_CONSTANT;

	return { red, green, blue };
}

Color readColor(std::ifstream& stream) {
	if (!stream.is_open()) {
		return {0, 0, 0};
	}

	char str[MAX_DIGITS_COUNT_IN_COLOR_CODE];
	stream.getline(str, MAX_DIGITS_COUNT_IN_COLOR_CODE, '|');

	return decryptColor(fromStringToNatural(str));
}

Color* readFromFile(std::ifstream& stream, size_t& colorsLength) {
	if (!stream.is_open()) {
		return nullptr;
	}

	std::streampos positionStart = stream.tellg();

	size_t numberOfColors = countSymbols(stream, '|') + 1;
	Color* colors = new Color[numberOfColors];

	for (size_t i = 0; i < numberOfColors - 1; i++) {
		colors[i] = readColor(stream);
	}

	colors[numberOfColors - 1] = readColor(stream);

	stream.clear();
	stream.seekg(positionStart);

	colorsLength = numberOfColors;
	return colors;
}

void writeColors(std::ofstream& stream, Color* colors, int colorsLength) {
	if (!stream.is_open() || colors == nullptr) {
		return;
	}

	std::streampos pos = stream.tellp();

	for (size_t i = 0; i < colorsLength - 1; i++) {
		stream << encryptColor(colors[i]) << '|';
	}

	stream << encryptColor(colors[colorsLength - 1]);

	stream.clear();
	stream.seekp(pos);
}

void writeColorsRed(std::ofstream& stream, Color* colors, int colorsLength) {
	if (!stream.is_open() || colors == nullptr) {
		return;
	}

	std::streampos pos = stream.tellp();

	size_t i = 0;

	for (i = 0; i < colorsLength; i++) {
		if (colors[i].red >= MIN_RED_VALUE) {
			stream << encryptColor(colors[i]);
			i++;
			break;
		}
	}

	for (; i < colorsLength; i++) {
		if (colors[i].red >= MIN_RED_VALUE) {
			stream << '|' <<  encryptColor(colors[i]);
		}
	}

	stream.clear();
	stream.seekp(pos);
}

void printColors(Color* colors, int colorsLength) {
	if (colors == nullptr) {
		return;
	}

	for (size_t i = 0; i < colorsLength; i++) {
		std::cout << "(" << colors[i].red << ", "
			<< colors[i].green << ", " << colors[i].blue << ")" << std::endl;
	}
}

int getRandom(int min, int max) {
	return rand() % (max - min) + min;
}

int main()
{
	srand(time(0));

	size_t colorsLength = 10;
	Color* colors = new Color[colorsLength];
	
	for (size_t i = 0; i < colorsLength; i++) {
		colors[i].red = getRandom(0, 256);
		colors[i].green = getRandom(0, 256);
		colors[i].blue = getRandom(0, 256);
	}

	std::ofstream writeStream(FILENAME);
	writeColors(writeStream, colors, colorsLength);
	writeStream.close();

	std::ofstream writeStreamRed(REDFILE);
	writeColorsRed(writeStreamRed, colors, colorsLength);
	writeStreamRed.close();

	printColors(colors, colorsLength);

	delete[] colors;

	std::cout << std::endl;

	std::ifstream readStream(FILENAME);
	colors = readFromFile(readStream, colorsLength);
	printColors(colors, colorsLength);
	readStream.close();
}