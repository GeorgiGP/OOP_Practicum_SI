#include "StringManipulator.h"
#include <iostream>
#include <cstring>
#include <fstream>

StringManipulator::StringManipulator()
{
	this->str = new char[1];
	str[0] = '\0';
	this->errorState = false;
}

StringManipulator::StringManipulator(const char* inputStr)
{
	if (inputStr == nullptr)
	{
		this->str = new char[1];
		str[0] = '\0';
	}
	else
	{
		int size = strlen(inputStr);

		this->str = new char[size + 1];

		strcpy_s(this->str, size + 1, inputStr);

		this->str[size] = '\0';
	}
}

StringManipulator::StringManipulator(const char* inputStr, int n)
{
	if (inputStr == nullptr || n <= 0)
	{
		this->str = new char[1];
		str[0] = '\0';
	}
	else
	{
		int size = strlen(inputStr);
		int totalsize = strlen(inputStr) * n + 1;
		str = new char[totalsize];

		int ind = 0;
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				str[ind++] = inputStr[j];
			}
		}

		this->str[ind] = '\0';
	}

	this->errorState = false;

}

StringManipulator::StringManipulator(const StringManipulator& other)
{
	copy(other);
}

StringManipulator& StringManipulator::operator=(const StringManipulator& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}


StringManipulator::~StringManipulator()
{
	free();
}

void StringManipulator::copy(const StringManipulator& other)
{
	int size = strlen(other.str) + 1;
	this->str = new char[size];

	strcpy_s(this->str, size, other.str);

	this->errorState = other.errorState;
}

void StringManipulator::free()
{
	delete[] this->str;
	str = nullptr;
}

char* StringManipulator::getStr() const
{
	return this->str;
}

void StringManipulator::setStr(const char* _str)
{
	free();
	int size = strlen(_str) + 1;
	this->str = new char[size];

	strcpy_s(this->str, size, _str);
}

bool StringManipulator::getErrorState() const
{
	return this->errorState;
}

void StringManipulator::setErrorState(bool errorState)
{
	this->errorState = errorState;
}

int StringManipulator::getStrLen()
{
	return strlen(this->str);
}

void StringManipulator::printStr()
{
	if (!this->errorState)
	{
		std::cout << this->str;
	}
}

void StringManipulator::saveInFile(const char* fileName)
{
	if (!this->errorState)
	{
		std::ofstream file(fileName, std::ios::out | std::ios::binary);

		if (!file.is_open())
		{
			this->errorState = true;
			return;
		}

		int size = getStrLen();

		file.write(reinterpret_cast<const char*> (&size), sizeof(int));
		file.write(this->str, size);
	}
}

StringManipulator& StringManipulator::readFromFile(const char* fileName)
{
	if (!this->errorState)
	{
		std::ifstream file(fileName, std::ios::in | std::ios::binary);

		if (!file.is_open())
		{
			this->errorState = true;
			return *this;
		}

		int size = 0;
		file.read(reinterpret_cast<char*> (&size), sizeof(int));
		this->str = new char[size + 1];

		char* fileData = new char[size];

		file.read(fileData, size);

		strcpy_s(this->str, size, fileData);

		delete[] fileData;

		this->str[size] = '\0';

		bool fileErrorState = false;

		file.read(reinterpret_cast<char*>(&fileErrorState), sizeof(fileErrorState));

		this->errorState = fileErrorState;
	}

	return *this;
}

StringManipulator& StringManipulator::concatStr(const StringManipulator& other)
{
	if (!this->errorState)
	{
		if (other.str == nullptr)
		{
			return *this;
		}
		int oldSize = getStrLen();
		int otherSize = strlen(other.getStr());
		int newSize = oldSize + otherSize;

		char* newStr = new char[newSize + 1];
		strcpy_s(newStr, newSize + 1, this->str);
		strcat_s(newStr, newSize + 1, other.getStr());

		free();

		this->str = newStr;
	}
	return *this;
}

StringManipulator& StringManipulator::replaceSymbol(const char char1, const char char2)
{
	if (!this->errorState)
	{
		int size = getStrLen();

		for (size_t i = 0; i < size; i++)
		{
			if (this->str[i] == char1)
			{
				this->str[i] = char2;
			}
		}
	}
	return *this;
}

StringManipulator& StringManipulator::replaceSymbol(const char char1, const char char2, int n)
{
	if (!this->errorState)
	{
		int replacementCount = 0;
		int size = getStrLen();

		for (size_t i = 0; i < size; i++)
		{
			if (this->str[i] == char1 && replacementCount != n)
			{
				this->str[i] = char2;
				replacementCount++;
			}
		}
	}
	return *this;
}

StringManipulator& StringManipulator::insertStr(const char* _str, int postion)
{

	if (!this->errorState)
	{
		if (_str == nullptr || postion < 0 || postion >(strlen(this->str)))
		{
			return *this;
		}

		int oldSize = getStrLen();
		int newSize = oldSize + strlen(_str) + 1;

		char* newValue = new char[newSize];

		if (postion == 0)
		{
			strcpy_s(newValue, newSize, _str);
			strcat_s(newValue, newSize, this->str);
		}
		else if (postion == oldSize)
		{
			strcpy_s(newValue, newSize, this->str);
			strcat_s(newValue, newSize, _str);
		}
		else
		{
			strncpy_s(newValue, newSize, this->str, postion);
			strcat_s(newValue, newSize, _str);
			strcat_s(newValue, newSize, this->str + postion);
		}

		this->str = newValue;
	}
	return *this;
}

StringManipulator& StringManipulator::insertStr(const char* _str)
{
	if (!this->errorState)
	{
		if (_str == nullptr)
		{
			return *this;
		}

		int oldSize = getStrLen();
		int newSize = oldSize + strlen(_str) + 1;

		char* newValue = new char[newSize];
		strcpy_s(newValue, newSize, this->str);
		strcat_s(newValue, newSize, _str);

		free();

		this->str = newValue;
	}
	return *this;
}

StringManipulator& StringManipulator::removeSymbols(int n, int position)
{
	if (!this->errorState)
	{
		int oldSize = getStrLen();

		if (n < 0 || position < 0 || position > oldSize)
		{
			return *this;
		}

		if (position + n > oldSize)
		{
			n = oldSize;
		}

		int newSize = position + oldSize - n + 1;

		char* newValue = new char[newSize];

		int ind = 0;
		for (size_t i = 0; i < position; i++)
		{
			newValue[ind++] = this->str[i];
		}

		for (size_t i = position + n; i < oldSize; i++)
		{
			newValue[ind++] = this->str[i];
		}

		newValue[ind] = '\0';

		free();

		this->str = newValue;
	}
	return *this;
}

StringManipulator StringManipulator::upperCase()
{
	if (!this->errorState)
	{
		int strSize = getStrLen();

		int diff = 'a' - 'A';

		StringManipulator copyObj(*this);

		for (size_t i = 0; i < strSize; i++)
		{
			if (copyObj.str[i] >= 'a' && copyObj.str[i] <= 'z')
			{
				copyObj.str[i] -= diff;
			}
		}
		return copyObj;
	}
	return StringManipulator("");
}

StringManipulator StringManipulator::lowerCase()
{
	if (!this->errorState)
	{
		int strSize = getStrLen();

		int diff = 'a' - 'A';

		StringManipulator copyObj(*this);

		for (size_t i = 0; i < strSize; i++)
		{
			if (copyObj.str[i] >= 'A' && copyObj.str[i] <= 'Z')
			{
				copyObj.str[i] += diff;
			}
		}

		return copyObj;
	}
	return StringManipulator("");
}
