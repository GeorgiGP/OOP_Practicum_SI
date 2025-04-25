#pragma once
#include "Object.h"

class Car : public virtual Object {
private:
	char* brand;
	char* model;
	int year;
	double fuel;
	double fuelTankCapacity;
	double consumptionPer100km;

	void setStr(const char* src, char*& dest);
	void copyFrom(const Car& other);
	void free();
public:
	Car(double latitude, double longitude, const char* brand, const char* model, int year, double fuel, double fuelTankCapacity, double consumptionPer100km);

	Car(const Car& other);
	Car& operator=(const Car& other);
	~Car();

	const char* getBrand() const;
	void setBrand(const char* brand);
	const char* getModel() const;
	void setModel(const char* model);
	int getYear() const;
	void setYear(int year);
	double getFuel() const;
	double getFuelTankCapacity() const;
	void setFuelTankCapacity(double fuelTankCapacity);
	double getConsumptionPer100km() const;
	void setConsumptionPer100km(double consumptionPer100km);

	void refuel(double liters);
	virtual void drive(double distance);
	virtual void drive(const Object& other);
};