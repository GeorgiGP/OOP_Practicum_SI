#include <iostream>

#include "StringManipulator.h"


int main()
{
	StringManipulator test("sally");

	test.replaceSymbol('a', 'i').concatStr(" at").insertStr(" FMI").insertStr("Test- ",0);

	test.printStr();

}
