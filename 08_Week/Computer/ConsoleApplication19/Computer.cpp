#include "Computer.h"
#include <cstring>
void Computer::free()
{
	delete[] modelVideoCard;
	modelVideoCard = nullptr;
}
void Computer::copyFrom(const Computer& other)
{
	setPoweCPU(other.powerCPU);
	setModelVideoCard(other.modelVideoCard);
	setPSU(other.PSU);
	setRAM(other.RAM);
}

Computer::Computer(double powerCpu, const char* model, int PSU, int RAM)
{
	setPoweCPU(powerCpu);
	setModelVideoCard(model);
	setPSU(PSU);
	setRAM(RAM);
}

Computer::Computer(const Computer& other)
{
	copyFrom(other);
}

Computer& Computer::operator=(const Computer& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Computer::~Computer()
{
	free();
}


int Computer::getRAM() const
{
	return RAM;
}

int Computer::getPSU() const
{
	return PSU;
}

const char* Computer::getModelVideoCard() const
{
	return modelVideoCard;
}

double Computer::getPoweCPU() const
{
	return powerCPU;
}

void Computer::setRAM(int RAM)
{
	this->RAM = RAM;
}

void Computer::setPSU(int PSU)
{
	this->PSU = PSU;
}

void Computer::setModelVideoCard(const char* model)
{
	this->modelVideoCard = new char[strlen(model) + 1];
	strcpy(this->modelVideoCard, model);
}

void Computer::setPoweCPU(double CPU)
{
	this->powerCPU = CPU;
}
