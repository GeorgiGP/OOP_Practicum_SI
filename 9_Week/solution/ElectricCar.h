#pragma once
#include "ElectricalDevice.h"
#include "Car.h"

class ElectricCar : public ElectricalDevice, private Car {
public:
	ElectricCar(double latitude, double longitude, double inputVoltage, double consumption, const Battery& battery, const char* brand, const char* model, int year, double consumptionPer100km);

	double getBatteryCharge() const;
	virtual void drive(double distance) override;
	virtual void drive(const Object& other) override;
};