#pragma once
#include <cstring>
#include <iostream>
using namespace std;

class StringManipulator
{
private:
	char* str = nullptr;
	bool errorState = false;

	void copy(const StringManipulator& other);

public:
	StringManipulator();
	StringManipulator(const char* str);
	StringManipulator(const char* str, int n);
	StringManipulator(const StringManipulator& other);
	StringManipulator& operator=(const StringManipulator& other);
	~StringManipulator();

	const char* getStr() const;
	StringManipulator& setStr(const char* str, int n = 1);

	bool getErrorState() const;
	StringManipulator& resetErrorState();

	int getLength() const;
	const StringManipulator& printString(ostream& outputStream) const;
	const StringManipulator& writeToFile(const char* filePath) const;
	StringManipulator& readFromFile(const char* filePath);
	StringManipulator& concat(const StringManipulator& sm);
	StringManipulator& replace(char oldChar, char newChar, int n = 1);
	StringManipulator& insertAt(const char* str, int index);
	StringManipulator& insertAt(const char* str);
	StringManipulator& remove(int startIdx, int count);
	StringManipulator upperCase() const;
	StringManipulator lowerCase() const;
};
