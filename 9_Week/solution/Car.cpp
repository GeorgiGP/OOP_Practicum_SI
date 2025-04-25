#include "Car.h"
#include <string.h>
#include <cmath>

void Car::setStr(const char* src, char*& dest) {
	delete dest;
	dest = new char[strlen(src) + 1];
	strcpy_s(dest, strlen(src) + 1, src);
}

void Car::copyFrom(const Car& other) {
	setStr(other.brand, brand);
	setStr(other.model, model);
	year = other.year;
	fuel = other.fuel;
	fuelTankCapacity = other.fuelTankCapacity;
	consumptionPer100km = other.consumptionPer100km;
}

void Car::free() {
	delete brand;
	delete model;
}

Car::Car(double latitude, double longitude, const char* brand, const char* model, int year, double fuel, double fuelTankCapacity, double consumptionPer100km) : Object(latitude, longitude), year(year), fuel(fuel), fuelTankCapacity(fuelTankCapacity), consumptionPer100km(consumptionPer100km) {
	setStr(brand, this->brand);
	setStr(model, this->model);
}

Car::Car(const Car& other) : Object(other) {
	copyFrom(other);
}

Car& Car::operator=(const Car& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Car::~Car() {
	free();
}

const char* Car::getBrand() const {
	return brand;
}

void Car::setBrand(const char* brand) {
	setStr(brand, this->brand);
}

const char* Car::getModel() const {
	return model;
}

void Car::setModel(const char* model) {
	setStr(model, this->model);
}

int Car::getYear() const {
	return year;
}

void Car::setYear(int year) {
	this->year = year;
}

double Car::getFuel() const {
	return fuel;
}

double Car::getFuelTankCapacity() const {
	return fuelTankCapacity;
}

void Car::setFuelTankCapacity(double fuelTankCapacity) {
	this->fuelTankCapacity = fuelTankCapacity;
}

double Car::getConsumptionPer100km() const {
	return consumptionPer100km;
}

void Car::setConsumptionPer100km(double consumptionPer100km) {
	this->consumptionPer100km = consumptionPer100km;
}

void Car::refuel(double liters) {
	fuel += liters;
	if (fuel > fuelTankCapacity) fuel = fuelTankCapacity;
}

void Car::drive(double distance) {
	if (fuel == 0) return;

	//change lat & lond
	fuel -= (distance / 100) * consumptionPer100km;

	if (fuel < 0) fuel = 0;
}

void Car::drive(const Object& other) {
	if (fuel == 0) return;

	double lat1 = getLatitude();
	double lon1 = getLongitude();
	double lat2 = other.getLatitude();
	double lon2 = other.getLongitude();
	double distance = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1)) * 6371;
	
	fuel -= (distance / 100) * consumptionPer100km;

	if (fuel < 0) {
		//change lat & lond
		fuel = 0;
	}
	else {
		setLatitude(other.getLatitude());
		setLongitude(other.getLongitude());
	}
}
