#include <iostream>
#include "StringManipulator.h"

const char* FILENAME = "File.dat";

int main()
{
	StringManipulator str("str", 3);
	str.concat("Hello").concat(" ").concat("World").insert("!").insert(" ", 1).removeAt(1, 2).changeSymbol('l', 'a', 2)
		.changeSymbol('o', 'a').printStr().writeInFile(FILENAME);
	
	str.upperCase().printStr();
	str.lowerCase().printStr();

	StringManipulator newStr;
	newStr.readFromFile(FILENAME);
	newStr.printStr();
}