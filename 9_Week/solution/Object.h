#pragma once

class Object {
private:
	double latitude;
	double longitude;
public:
	Object(double latitude, double longitude);

	double getLatitude() const;
	void setLatitude(double latitude);
	double getLongitude() const;
	void setLongitude(double longitude);
};