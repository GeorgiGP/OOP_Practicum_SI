#include <iostream>
#include <fstream>
#include "StringManipulator.h"
using namespace std;

bool isInRange(int value, int from, int to)
{
	return value >= from && value <= to;
}

int getOccurrencesCount(const char* str, char ch)
{
	if (str == nullptr)
	{
		return -1;
	}

	int count = 0;

	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ch)
		{
			count++;
		}
	}

	return count;
}

char charToLower(char ch)
{
	if (isInRange(ch, 'A', 'Z'))
	{
		return ch + ('a' - 'A');
	}

	return ch;
}

char charToUpper(char ch)
{
	if (isInRange(ch, 'a', 'z'))
	{
		return ch + ('A' - 'a');
	}

	return ch;
}

char* modifyStr(char* str, char (*modify)(char))
{
	if (str == nullptr || modify == nullptr)
	{
		return nullptr;
	}

	int length = strlen(str);
	char* newStr = new char[length + 1];
	newStr[length] = '\0';

	for (size_t i = 0; i < length; i++)
	{
		newStr[i] = modify(str[i]);
	}

	return newStr;
}

StringManipulator::StringManipulator()
	: StringManipulator("")
{

}

StringManipulator::StringManipulator(const char* str)
	: StringManipulator(str, 1)
{

}

StringManipulator::StringManipulator(const char* str, int n)
{
	setStr(str, n);
}

StringManipulator::StringManipulator(const StringManipulator& other)
{
	copy(other);
}

StringManipulator& StringManipulator::operator=(const StringManipulator& other)
{
	copy(other);
	return *this;
}

StringManipulator::~StringManipulator()
{
	delete[] str;
	str = nullptr;
}

void StringManipulator::copy(const StringManipulator& other)
{
	if (this != &other)
	{
		setStr(other.str);
		errorState = other.errorState;
	}
}

const char* StringManipulator::getStr() const
{
	if (errorState)
	{
		return nullptr;
	}

	return str;
}

StringManipulator& StringManipulator::setStr(const char* str, int n)
{
	if (errorState || str == nullptr || n <= 0)
	{
		return *this;
	}

	if (this->str != nullptr)
	{
		delete[] this->str;
	}

	int length = strlen(str);
	int totalLength = n * length;
	this->str = new char[totalLength + 1];
	this->str[totalLength] = '\0';

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			int idx = i * length + j;
			this->str[idx] = str[j];
		}
	}

	return *this;
}

bool StringManipulator::getErrorState() const
{
	return errorState;
}

StringManipulator& StringManipulator::resetErrorState()
{
	errorState = false;
	return *this;
}

int StringManipulator::getLength() const
{
	if (errorState)
	{
		return -1;
	}

	return strlen(str);
}

const StringManipulator& StringManipulator::printString(ostream& outputStream) const
{
	if (errorState || (!outputStream.good()))
	{
		return *this;
	}

	outputStream << str;
	return *this;
}

const StringManipulator& StringManipulator::writeToFile(const char* filePath) const
{
	if (errorState || filePath == nullptr)
	{
		return *this;
	}

	ofstream outFile(filePath, ios::out | ios::binary);
	if (!outFile.is_open())
	{
		return *this;
	}

	int length = strlen(str);
	outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
	outFile.write(str, length);
	outFile.write(reinterpret_cast<const char*>(&errorState), sizeof(errorState));

	outFile.close();

	return *this;
}

StringManipulator& StringManipulator::readFromFile(const char* filePath)
{
	if (errorState || filePath == nullptr)
	{
		return *this;
	}

	ifstream inFile(filePath, ios::in | ios::binary);
	if (!inFile.is_open())
	{
		return *this;
	}

	int strLength;
	inFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));

	delete[] str;
	str = new char[strLength + 1];
	str[strLength] = '\0';

	inFile.read(str, strLength);
	inFile.read(reinterpret_cast<char*>(&errorState), sizeof(errorState));

	inFile.close();

	return *this;
}

StringManipulator& StringManipulator::concat(const StringManipulator& sm)
{
	if (errorState || sm.errorState || sm.str == nullptr)
	{
		return *this;
	}

	int currStrLength = getLength();
	int otherStrLength = strlen(sm.str);
	int totalLength = currStrLength + otherStrLength;

	char* newStr = new char[totalLength + 1];
	newStr[totalLength] = '\0';
	int newStrIndex = 0;

	for (size_t i = 0; i < currStrLength; i++)
	{
		newStr[newStrIndex] = str[i];
		newStrIndex++;
	}

	for (size_t i = 0; i < otherStrLength; i++)
	{
		newStr[newStrIndex] = sm.str[i];
		newStrIndex++;
	}

	delete[] str;
	str = newStr;

	return *this;
}

StringManipulator& StringManipulator::replace(char oldChar, char newChar, int n)
{
	if (errorState || n <= 0)
	{
		return *this;
	}

	int occurrencesCount = getOccurrencesCount(str, oldChar);
	int originalStrLength = getLength();
	int length = originalStrLength + (n - 1) * occurrencesCount;

	char* newStr = new char[length + 1];
	newStr[length] = '\0';
	int newStrIdx = 0;

	for (size_t i = 0; i < originalStrLength; i++)
	{
		if (str[i] != oldChar)
		{
			newStr[newStrIdx] = str[i];
			newStrIdx++;
			continue;
		}

		for (size_t j = 0; j < n; j++)
		{
			newStr[newStrIdx] = newChar;
			newStrIdx++;
		}
	}

	delete[] str;
	str = newStr;

	return *this;
}

StringManipulator& StringManipulator::insertAt(const char* str, int index)
{
	if (errorState || str == nullptr || index < 0)
	{
		return *this;
	}

	int originalStrLength = getLength();
	if (index > originalStrLength)
	{
		return *this;
	}

	int insertedStrLength = strlen(str);
	int totalLength = originalStrLength + insertedStrLength;

	char* newStr = new char[totalLength + 1];
	newStr[totalLength] = '\0';
	int newStrIdx = 0;

	for (size_t i = 0; i < index; i++)
	{
		newStr[newStrIdx] = this->str[i];
		newStrIdx++;
	}

	for (size_t i = 0; i < insertedStrLength; i++)
	{
		newStr[newStrIdx] = str[i];
		newStrIdx++;
	}

	for (size_t i = index; i < originalStrLength; i++)
	{
		newStr[newStrIdx] = this->str[i];
		newStrIdx++;
	}

	delete[] this->str;
	this->str = newStr;

	return *this;
}

StringManipulator& StringManipulator::insertAt(const char* str)
{
	if (errorState || str == nullptr)
	{
		return *this;
	}

	return insertAt(str, getLength());
}

StringManipulator& StringManipulator::remove(int startIdx, int count)
{
	if (errorState || startIdx < 0 || count < 0)
	{
		return *this;
	}

	int originalStrLength = getLength();
	int newLength = originalStrLength - count;
	if (newLength < 0)
	{
		return *this;
	}

	char* newStr = new char[newLength + 1];
	newStr[newLength] = '\0';
	int newStrIdx = 0;

	for (size_t i = 0; i < startIdx; i++)
	{
		newStr[newStrIdx] = str[i];
		newStrIdx++;
	}

	for (size_t i = startIdx + count; i < originalStrLength; i++)
	{
		newStr[newStrIdx] = str[i];
		newStrIdx++;
	}

	delete[] str;
	str = newStr;

	return *this;
}

StringManipulator StringManipulator::upperCase() const
{
	StringManipulator sm;
	if (errorState)
	{
		return sm;
	}

	char* strToUpper = modifyStr(str, charToUpper);
	sm.setStr(strToUpper);
	delete[] strToUpper;

	return sm;
}

StringManipulator StringManipulator::lowerCase() const
{
	StringManipulator sm;
	if (errorState)
	{
		return sm;
	}

	char* strToLower = modifyStr(str, charToLower);
	sm.setStr(strToLower);
	delete[] strToLower;

	return sm;
}

int main()
{
	StringManipulator sm1, sm2("love"), sm3("<3", 3);

	sm1.setStr("Hallo").replace('a', 'e').insertAt(", ").concat(sm2).insertAt("!").concat(sm3).printString(cout);

	return 0;
}
