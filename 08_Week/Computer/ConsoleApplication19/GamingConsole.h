#pragma once
#include "Computer.h"
class GamingConsole : public Computer
{
public:
	static const char* const type;
	static const char* const perifer;
public:
	
	const char* getType() const override;
	const char* getPerifer() const override;
};

