#pragma once

#include <cstring>

class StringManipulator {

private:
	char* str;
	bool errorState = false;

	void copy(const StringManipulator& other);
	void free();

public:

	StringManipulator();
	StringManipulator(const char* inputStr);
	StringManipulator(const char* inputStr, int n);

	StringManipulator(const StringManipulator& other);

	StringManipulator& operator=(const StringManipulator& other);
	
	~StringManipulator();

	char* getStr() const;
	void setStr(const char* _str);

	bool getErrorState() const;
	void setErrorState(bool errorState);

	int getStrLen();

	void printStr();

	void saveInFile(const char* fileName);

	StringManipulator& readFromFile(const char* fileName);

	StringManipulator& concatStr(const StringManipulator &other);

	StringManipulator& replaceSymbol(const char char1, const char char2);
	StringManipulator& replaceSymbol(const char char1, const char char2, int n);

	StringManipulator& insertStr(const char* _str, int postion);
	StringManipulator& insertStr(const char* _str);

	StringManipulator& removeSymbols(int n, int position);

	StringManipulator upperCase();

	StringManipulator lowerCase();

};