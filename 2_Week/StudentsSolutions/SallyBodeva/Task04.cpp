// Task04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

const char* COMMANDS_FILE_NAME = "inputCommands.txt";
const char* TEXT_FILE_NAME = "inputText.txt";
const char* OUTPUT_FILE_NAME = "result.txt";
const int MAX_CHAR_ARRAY_LEN = 1024;

struct MessageValues
{
	char message[MAX_CHAR_ARRAY_LEN];
	char values[MAX_CHAR_ARRAY_LEN];
};

void copyArr(const char* source, char* destMessage, char* destValue) {

	if (source == nullptr || destMessage == nullptr, destValue == nullptr)
	{
		return;
	}

	while (*source != ' ')
	{
		*destMessage = *source;

		destMessage++;
		source++;
	}
	source++;
	while (*source != '\0')
	{
		*destValue = *source;

		destValue++;
		source++;
	}
}

int getLinesCount(std::ifstream& ifs) {

	if (!ifs.is_open())
	{
		std::cout << "Error";
		return -1;
	}

	int count = 1;

	while (!ifs.eof())
	{
		if (ifs.get() == '\n')
		{
			count++;
		}
	}

	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	return count;
}

MessageValues createStruct(const char* message, const char* values) {

	if (message == nullptr || values == nullptr)
	{
		return MessageValues{};
	}

	MessageValues m;

	int ind = 0;

	while (*message != '\0')
	{
		m.message[ind++] = *message;
		message++;
	}
	m.message[ind] = '\0';

	ind = 0;

	while (*values != '\0')
	{
		m.values[ind++] = *values;
		values++;
	}

	m.values[ind] = '\0';

	return m;
}


MessageValues* readReplacement(const char* fileName, int& outputSize) {

	if (fileName == nullptr)
	{
		return nullptr;
	}

	std::ifstream file(fileName);

	if (!file.is_open())
	{
		return nullptr;
	}

	int linesCount = getLinesCount(file);
	outputSize = linesCount;
	MessageValues* m = new MessageValues[linesCount];
	int insertInd = 0;

	while (!file.eof())
	{
		char message[MAX_CHAR_ARRAY_LEN] = { ' ' };
		char values[MAX_CHAR_ARRAY_LEN] = { ' ' };

		char line[MAX_CHAR_ARRAY_LEN];

		file.getline(line, MAX_CHAR_ARRAY_LEN);

		copyArr(line, message, values);

		MessageValues mV = createStruct(message, values);

		m[insertInd++] = mV;
	}

	file.close();
	return m;
}

int getFileSize(std::ifstream& ifs) {

	if (!ifs.is_open())
	{
		std::cout << "Error";
		return -1;
	}

	ifs.seekg(0, std::ios::end);
	int lastIndex = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	return (lastIndex+1);
}

char* readText(const char* fileName) {

	if (fileName == nullptr)
	{
		return nullptr;
	}

	std::ifstream file(fileName);

	if (!file.is_open())
	{
		return nullptr;
	}
	int fileSize = getFileSize(file);
	char* text = new char[fileSize + 1];
	int ind = 0;

	while (true)
	{
		if (file.eof())
		{
			break;
		}
		text[ind++] = file.get();
	}
	text[ind] = '\0';
	file.close();
	return text;
}

char* getValue(MessageValues* m, int size, const char* message) {

	if (m == nullptr || message == nullptr)
	{
		return nullptr;
	}

	int indexOfValue = 0;
	bool isFound;
	for (int i = 0; i < size; i++)
	{
		isFound = true;
		while (message[indexOfValue] != m[i].message[indexOfValue])
		{
			isFound = false;
			break;
		}
		indexOfValue = 0;
		if (isFound)
		{
			return m[i].values;
		}
	}
	return nullptr;
}

void saveInFile(const char* fileName, const char* text, MessageValues* messages, int size) {

	if (fileName == nullptr || text == nullptr || messages == nullptr)
	{
		return;
	}

	std::ofstream file(fileName);

	if (!file.is_open())
	{
		return;
	}


	while (*text != '\0')
	{
		char symbol = *text;
		if (symbol == '{')
		{
			text++;
			if (*text == '\0')
			{
				break;
			}
			char messageToReplace[MAX_CHAR_ARRAY_LEN] = { '-' };
			int index = 0;

			while (*text != '}' && *text != '\0')
			{
				messageToReplace[index++] = *text;
				if (*text == '\0')
				{
					break;
				}
				text++;
			}


			messageToReplace[index] = '\0';

			char* replcement = getValue(messages, size, messageToReplace);

			if (replcement == nullptr)
			{
				return;
			}

			while (*replcement != '\0')
			{
				file.put(*replcement);
				replcement++;
			}

		}
		else
		{
			file.put(symbol);
		}
		text++;
	}

	file.close();
}

int main()
{
	int size = 0;
	readReplacement(COMMANDS_FILE_NAME, size);

	MessageValues* m = readReplacement(COMMANDS_FILE_NAME, size);


	char* text = readText(TEXT_FILE_NAME);

	saveInFile(OUTPUT_FILE_NAME, text, m, size);

	delete[] m;
	delete[] text;

	return 0;


}