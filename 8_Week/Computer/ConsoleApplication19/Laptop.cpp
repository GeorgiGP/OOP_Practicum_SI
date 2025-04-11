#include "Laptop.h"
#include <cstring>
const char* Laptop::type = "Laptop";
const char* Laptop::perifer = "mouse pad, keyboard, Monitor";

void Laptop::free()
{
	delete[] modelLaptop;
	modelLaptop = nullptr;
}

void Laptop::copyFrom(const Laptop& other)
{
	modelLaptop = new char[strlen(other.modelLaptop) + 1];
	strcpy(modelLaptop, other.modelLaptop);
}

Laptop::Laptop(double powerCpu, const char* model, int PSU, int RAM) : Computer(powerCpu, model, PSU, RAM)
{
}

Laptop::Laptop(const Laptop& other) : Computer(other)
{
	copyFrom(other);
}

Laptop& Laptop::operator=(const Laptop& other)
{
	if (this != &other) {
		Computer::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

Laptop::~Laptop()
{
	free();
}

const char* Laptop::getType() const
{
	return type;
}

const char* Laptop::getPerifer() const
{
	return perifer;
}
