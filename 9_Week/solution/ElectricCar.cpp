#include "ElectricCar.h"
#include <cmath>

ElectricCar::ElectricCar(double latitude, double longitude, double inputVoltage, double consumption, const Battery& battery, const char* brand, const char* model,
	int year, double consumptionPer100km) : Object(latitude, longitude), ElectricalDevice(latitude, longitude, inputVoltage, consumption, battery),
	Car(latitude, longitude, brand, model, year, 0, 0, consumptionPer100km) {}

double ElectricCar::getBatteryCharge() const {
	return getBattery()->getCharge();
}

void ElectricCar::drive(double distance) {
	if (getBatteryCharge() == 0) return;

	double WhForRequiredDistance = (distance / 100) * getConsumptionPer100km();

	dischargeBattery(WhForRequiredDistance);
	//change lat & lond or rand ones
}

void ElectricCar::drive(const Object& other) {
	if (getBatteryCharge() == 0) return;

	double lat1 = getLatitude();
	double lon1 = getLongitude();
	double lat2 = other.getLatitude();
	double lon2 = other.getLongitude();
	double distance = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1)) * 6371;

	double WhForRequiredDistance = (distance / 100) * getConsumptionPer100km();

	if (WhForRequiredDistance > getBatteryCharge() * getBattery()->getWh()) {
		//change lat & lond or rand ones
	} else {
		setLatitude(other.getLatitude());
		setLongitude(other.getLongitude());
	}

	dischargeBattery(WhForRequiredDistance);
}
