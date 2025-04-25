#include "Battery.h"

Battery::Battery(double latitude, double longitude, double Wh) : Object(latitude, longitude), Wh(Wh), charge(0) {}

double Battery::getWh() const {
	return Wh;
}

double Battery::getCharge() const {
	return charge;
}

void Battery::setCharge(double charge) {
	this->charge = charge;
}
