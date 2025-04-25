#pragma once
#include "Object.h"

class Battery : public Object {
private:
	const double Wh;
	double charge;
public:
	Battery(double latitude, double longitude, double Wh);

	double getWh() const;
	double getCharge() const;
	void setCharge(double charge);
};