#include <iostream>
#include <fstream>

const char PLACEHOLDERS_FILE[] = "placeholder.txt";
const char VALUES_FILE[] = "values.txt";
const char OUTPUT_FILE[] = "output.txt";

const int TEXT_MAX_SIZE = 100;

bool areStringsEqual(const char* str1, const char* str2) {
	while ((*str1 != '\0' || *str2 != '\0') && *str1 == *str2) {
		str1++;
		str2++;
	}

	return *str1 == '\0' && *str2 == '\0';
}

size_t getLength(const char* str) {
	int result = 0;

	if (str == nullptr) {
		return result;
	}

	while (str[result] != '\0') {
		result++;
	}

	return result;
}

void copyString(char* destination, const char* source) {
	if (destination == nullptr || source == nullptr) {
		return;
	}

	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
}

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

char** readValuesFile(const char* valuesFile, size_t& numberOfValues) {
	std::ifstream stream(valuesFile);
	if (!stream.is_open()) {
		return nullptr;
	}

	numberOfValues = countSymbols(stream, '\n') + 1;
	char** result = new char*[numberOfValues * 2];

	char text[TEXT_MAX_SIZE];

	for (size_t i = 0; i < numberOfValues * 2; i++)
	{
		stream.getline(text, TEXT_MAX_SIZE, i % 2 == 0 ? ' ' : '\n');
		result[i] = new char[getLength(text) + 1];
		copyString(result[i], text);
	}

	stream.close();

	return result;
}


void deletePlaceholderAndValues(char** placeholdersAndValues, size_t numberOfPlaceholders) {
	for (size_t i = 0; i < numberOfPlaceholders; i++)
	{
		delete[] placeholdersAndValues[i];
	}

	delete[] placeholdersAndValues;
}


void putValuesOnPlaceholders(const char* outputFile, const char* placeholderFile, const char* valuesFile) {
	size_t numberOfPlaceholders = 0;
	char** placeholdersAndValues = readValuesFile(VALUES_FILE, numberOfPlaceholders);

	if (placeholdersAndValues == nullptr) {
		return;
	}

	std::ifstream placeholderFileReader(placeholderFile);

	if (!placeholderFileReader.is_open()) {
		deletePlaceholderAndValues(placeholdersAndValues, numberOfPlaceholders);
		return;
	}

	std::ofstream outputFileWriter(outputFile);

	if (!outputFileWriter.is_open()) {
		placeholderFileReader.close();
		deletePlaceholderAndValues(placeholdersAndValues, numberOfPlaceholders);
		return;
	}

	int currentSymbol;
	while ((currentSymbol = placeholderFileReader.get()) != EOF) {
		if (currentSymbol == '{') {
			char placeholder[TEXT_MAX_SIZE];
			placeholderFileReader.getline(placeholder, TEXT_MAX_SIZE, '}');
			for (size_t i = 0; i < numberOfPlaceholders * 2; i++)
			{
				if (areStringsEqual(placeholder, placeholdersAndValues[i])) {
					outputFileWriter << placeholdersAndValues[i + 1];
					break;
				}
			}
		}
		else {
			outputFileWriter << (char)currentSymbol;
		}
	}

	deletePlaceholderAndValues(placeholdersAndValues, numberOfPlaceholders);
	placeholderFileReader.close();
	outputFileWriter.close();
}

int main()
{
	putValuesOnPlaceholders(OUTPUT_FILE, PLACEHOLDERS_FILE, VALUES_FILE);
}