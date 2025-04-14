#pragma once
#include <fstream>

class Waffle {
private:
	static const int BRAND_MAX_LENGTH = 20;
	char brand[BRAND_MAX_LENGTH + 1];
	double weight;
	double wholesalePrice;
	double priceForClient;

public:
	Waffle();
	
	Waffle(const char* brand, double weight = 10, double wholesalePrice = 1, double priceForClient = 1.5);

	const char* getBrand() const;
	void setBrand(const char* brand);

	const double getWeight() const;
	void setWeight(double weight);

	const double getWholesalePrice() const;
	void setWholesalePrice(double wholesalePrice);

	const double getPriceForClient() const;
	void setPriceForClient(double priceForClient);

	void serializeInBinaryFile(std::ofstream& stream) const;
	void deserializeInBinaryFile(std::ifstream& stream);
};