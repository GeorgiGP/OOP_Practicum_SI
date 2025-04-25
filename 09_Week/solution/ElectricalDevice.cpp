#include "ElectricalDevice.h"

void ElectricalDevice::copyFrom(const ElectricalDevice& other) {
	inputVoltage = other.inputVoltage;
	consumption = other.consumption;
	battery = new Battery(*other.battery);
}

void ElectricalDevice::free() {
	delete battery;
}

ElectricalDevice::ElectricalDevice(double latitude, double longitude, double inputVoltage, double consumption) : Object(latitude, longitude), inputVoltage(inputVoltage), consumption(consumption), battery(nullptr) {}

ElectricalDevice::ElectricalDevice(double latitude, double longitude, double inputVoltage, double consumption, const Battery& battery) : Object(latitude, longitude), inputVoltage(inputVoltage), consumption(consumption) {
	this->battery = new Battery(battery);
}

ElectricalDevice::ElectricalDevice(const ElectricalDevice& other) : Object(other) {
	copyFrom(other);
}

ElectricalDevice& ElectricalDevice::operator=(const ElectricalDevice& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

ElectricalDevice::~ElectricalDevice() {
	free();
}

double ElectricalDevice::getInputVoltage() const {
	return inputVoltage;
}

double ElectricalDevice::getConsumption() const {
	return consumption;
}

const Battery* ElectricalDevice::getBattery() const {
	return battery;
}

void ElectricalDevice::changeBattery(const Battery& battery) {
	delete this->battery;
	this->battery = new Battery(battery);
}

void ElectricalDevice::chargeBattery(double Wh) {
	if (battery) {
		battery->setCharge(battery->getCharge() + Wh / battery->getWh());

		if (battery->getCharge() > 1) {
			battery->setCharge(1);
		}
	}
}

void ElectricalDevice::dischargeBattery(double Wh) {
	if (battery) {
		battery->setCharge(battery->getCharge() - Wh / battery->getWh());

		if (battery->getCharge() < 0) {
			battery->setCharge(0);
		}
	}
}
