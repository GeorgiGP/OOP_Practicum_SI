#include <iostream>
#include <fstream>
#include <string.h>
#include "StringManipulator.h"

size_t StringManipulator::getBuffer() const
{
	return this->buffer;
}

void StringManipulator::setBuffer(size_t buffer)
{
	while (this->getStrLength() + 1 > buffer) {
		buffer *= 2;
	}

	this->buffer = buffer;
	char* prev = this->str;
	this->str = new char[buffer];

	if (prev != nullptr) {
		for (size_t i = 0; i < this->getStrLength(); i++)
		{
			this->str[i] = prev[i];
		}
		this->str[this->getStrLength()] = '\0';
		delete[] prev;
	}
}

void StringManipulator::copy(const StringManipulator& stringManipulator)
{
	this->str = nullptr;
	this->strLength = 0;
	this->setBuffer(1);
	this->errorState = stringManipulator.getErrorState();
	this->setStr(stringManipulator.getStr());
}

void StringManipulator::remove()
{
	delete[] this->str;
	this->str = nullptr;
	this->strLength = 0;
	this->errorState = true;
}

StringManipulator::StringManipulator()
{
	this->strLength = 0;
	this->str = nullptr;


	this->setStr("");
	this->clearErrorState();
}

StringManipulator::StringManipulator(const char* str)
{
	this->strLength = 0;
	this->str = nullptr;

	this->clearErrorState();
	this->setStr(str);
}

StringManipulator::StringManipulator(const char* str, size_t repeat)
{
	this->strLength = 0;
	this->str = nullptr;

	size_t strLength = strlen(str);
	char* newStr = new char[strLength * repeat + 1];
	for (size_t i = 0; i < repeat; i++)
	{
		for (size_t j = 0; j < strLength; j++)
		{
			newStr[i * strLength + j] = str[j];
		}
	}
	newStr[strLength * repeat] = '\0';

	this->clearErrorState();
	this->setStr(newStr);

	delete[] newStr;
}

StringManipulator::StringManipulator(const StringManipulator& stringManipulator)
{
	copy(stringManipulator);
}

StringManipulator& StringManipulator::operator=(const StringManipulator& stringManipulator)
{
	if (this == &stringManipulator) {
		return *this;
	}

	copy(stringManipulator);

	return *this;
}

StringManipulator::~StringManipulator()
{
	remove();
}

const char* StringManipulator::getStr() const
{
	return this->str;
}

StringManipulator& StringManipulator::setStr(const char* str)
{
	if (this->errorState) {
		return *this;
	}

	if (str == nullptr || this->errorState) {
		return *this;
	}

	size_t strLength = strlen(str);

	if (this->getBuffer() == 0 || this->str == nullptr) {
		this->setBuffer(1);
	}


	this->strLength = strLength;
	while (this->getBuffer() < strLength + 1) {
		this->setBuffer(this->getBuffer() * 2);
	}

	for (size_t i = 0; i < strLength; i++)
	{
		this->str[i] = str[i];
	}

	this->str[strLength] = '\0';
	this->strLength = strLength;

	while (this->getBuffer() / 2 > (strLength + 1) && this->getBuffer() / 2 != 0) {
		this->setBuffer(this->getBuffer() / 2);
	}

	return *this;
}

bool StringManipulator::getErrorState() const
{
	return this->errorState;
}

StringManipulator& StringManipulator::clearErrorState()
{
	this->errorState = false;
	return *this;
}

size_t StringManipulator::getStrLength() const
{
	return this->strLength;
}

const StringManipulator& StringManipulator::printStr() const
{
	if (this->errorState) {
		return *this;
	}

	std::cout << this->str << std::endl;
	return *this;
}

const StringManipulator& StringManipulator::writeInFile(const char* fileName) const
{
	if (fileName == nullptr || this->errorState) {
		return *this;
	}

	std::ofstream stream(fileName, std::ios::binary | std::ios::out);

	if (!stream.is_open()) {
		return *this;
	}

	stream.write(reinterpret_cast<const char*>(&this->strLength), sizeof(size_t));
	stream.write(this->str, this->getStrLength() + 1);

	stream.close();
	return *this;
}

StringManipulator& StringManipulator::readFromFile(const char* fileName)
{
	if (fileName == nullptr || this->errorState) {
		return *this;
	}

	std::ifstream stream(fileName, std::ios::binary | std::ios::in);

	if (!stream.is_open()) {
		return *this;
	}

	size_t strLength = 0;
	stream.read(reinterpret_cast<char*>(&strLength), sizeof(size_t));
	char* newStr = new char[strLength + 1];
	stream.read(newStr, strLength + 1);

	this->setStr(newStr);

	delete[] newStr;
	stream.close();

	return *this;
}

StringManipulator& StringManipulator::concat(const StringManipulator& stringManipulator)
{
	if (stringManipulator.getErrorState() || this->errorState) {
		return *this;
	}

	size_t sizeConcat = this->getStrLength() + stringManipulator.getStrLength();
	char* newStr = new char[sizeConcat + 1];

	for (size_t i = 0; i < this->getStrLength(); i++)
	{
		newStr[i] = this->str[i];
	}

	for (size_t i = 0; i < stringManipulator.getStrLength(); i++)
	{
		newStr[i + this->getStrLength()] = stringManipulator.getStr()[i];
	}

	newStr[this->getStrLength() + stringManipulator.getStrLength()] = '\0';
	setStr(newStr);
	delete[] newStr;
	return *this;
}

StringManipulator& StringManipulator::changeSymbol(char find, char replace)
{
	if (this->errorState) {
		return *this;
	}

	char* newStr = new char[this->getStrLength() + 1];
	strcpy_s(newStr, this->getStrLength() + 1, this->getStr());

	for (size_t i = 0; i < this->getStrLength(); i++)
	{
		if (newStr[i] == find) {
			newStr[i] = replace;
		}
	}

	this->setStr(newStr);
	delete[] newStr;
	return *this;
}

StringManipulator& StringManipulator::changeSymbol(char find, char replace, size_t count)
{
	if (this->errorState) {
		return *this;
	}

	char* newStr = new char[this->getStrLength() + 1];
	strcpy_s(newStr, this->getStrLength() + 1, this->getStr());

	for (size_t i = 0; i < this->getStrLength(); i++)
	{
		if (newStr[i] == find) {
			newStr[i] = replace;
			count--;

			if (count == 0) {
				break;
			}
		}
	}

	this->setStr(newStr);
	delete[] newStr;
	return *this;
}

StringManipulator& StringManipulator::insert(const char* str, size_t pos)
{
	if (this->errorState) {
		return *this;
	}

	if (str == nullptr || pos > this->getStrLength() + 1) {
		return *this;
	}

	size_t strLength = strlen(str);
	size_t newStrLength = strLength + this->getStrLength();
	char* newStr = new char[newStrLength + 1];
	newStr[newStrLength] = '\0';

	for (size_t i = 0, j = 0; i < newStrLength; i++)
	{
		if (i == pos) {
			for (size_t k = 0; k < strLength; k++)
			{
				newStr[i] = str[k];
				i++;
			}
			i--;
		}
		else {
			newStr[i] = this->getStr()[j];
			j++;
		}
	}

	this->setStr(newStr);
	delete[] newStr;
	return *this;
}

StringManipulator& StringManipulator::insert(const char* str)
{
	return insert(str, this->getStrLength());
}

StringManipulator& StringManipulator::removeAt(size_t pos, size_t length)
{
	if (this->errorState) {
		return *this;
	}

	char* newStr = new char[this->getStrLength() + 1];
	strcpy_s(newStr, this->getStrLength() + 1, this->getStr());

	for (size_t i = pos + length; i < this->getStrLength(); i++)
	{
		newStr[i - length] = newStr[i];
	}

	newStr[this->getStrLength() - length] = '\0';
	this->setStr(newStr);
	delete[] newStr;

	return *this;
}

StringManipulator StringManipulator::upperCase()
{
	if (this->errorState) {
		return *this;
	}

	char* newStr = new char[this->getStrLength() + 1];
	strcpy_s(newStr, this->getStrLength() + 1, this->getStr());

	for (size_t i = 0; i < this->getStrLength(); i++)
	{
		if ('a' <= newStr[i] && newStr[i] <= 'z') {
			newStr[i] = newStr[i] - 'a' + 'A';
		}
	}

	StringManipulator result(newStr);
	delete[] newStr;
	return result;
}

StringManipulator StringManipulator::lowerCase()
{
	if (this->errorState) {
		return *this;
	}

	char* newStr = new char[this->getStrLength() + 1];
	strcpy_s(newStr, this->getStrLength() + 1, this->getStr());

	for (size_t i = 0; i < this->getStrLength(); i++)
	{
		if ('A' <= newStr[i] && newStr[i] <= 'Z') {
			newStr[i] = newStr[i] - 'A' + 'a';
		}
	}

	StringManipulator result(newStr);
	delete[] newStr;
	return result;
}
