#pragma once
#include "Object.h"
#include "Battery.h"

class ElectricalDevice : public virtual Object {
private:
	double inputVoltage;
	double consumption;
	Battery* battery;

	void copyFrom(const ElectricalDevice& other);
	void free();
public:
	ElectricalDevice(double latitude, double longitude, double inputVoltage, double consumption);
	ElectricalDevice(double latitude, double longitude, double inputVoltage, double consumption, const Battery& battery);

	ElectricalDevice(const ElectricalDevice& other);
	ElectricalDevice& operator=(const ElectricalDevice& other);
	~ElectricalDevice();

	double getInputVoltage() const;
	double getConsumption() const;
	const Battery* getBattery() const;

	void changeBattery(const Battery& battery);
	void chargeBattery(double Wh);
	void dischargeBattery(double Wh);
};