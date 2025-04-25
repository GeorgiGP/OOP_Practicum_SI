#pragma once
#include "Computer.h"
class Laptop : public Computer
{
private:
	static const char* type;
	static const char* perifer;

	char* modelLaptop;

	void free();
	void copyFrom(const Laptop& other);
public:
	Laptop(double powerCpu, const char* model, int PSU, int RAM);
	Laptop(const Laptop& other);
	Laptop& operator=(const Laptop& other);
	~Laptop();

	const char* getType() const override;
	const char* getPerifer() const override;
};

