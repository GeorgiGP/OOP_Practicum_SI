#include "GamingConsole.h"

const char* GamingConsole::type = new char[10];
strcpy(GamingConsole::type, "Gaming Console");

const char* GamingConsole::perifer = "Joystick, Monitor";

const char* GamingConsole::getType() const
{
	return type;
}

const char* GamingConsole::getPerifer() const
{
	return perifer;
}


