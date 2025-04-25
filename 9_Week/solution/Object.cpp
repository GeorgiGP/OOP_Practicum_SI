#include "Object.h"

Object::Object(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

double Object::getLatitude() const {
    return latitude;
}

void Object::setLatitude(double latitude) {
    this->latitude = latitude;
}

double Object::getLongitude() const {
    return longitude;
}

void Object::setLongitude(double longitude) {
    this->longitude = longitude;
}
