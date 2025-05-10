#pragma once
#include "Price.h"
#include "State.h"

class PricesDatabase
{
private:
	static const size_t MAX_NUMBER_OF_PRICES = 50;

	Price prices[MAX_NUMBER_OF_PRICES];
	size_t size;
public:
	PricesDatabase();
	State addPrice(const Price& price);
	double getPrice(size_t id) const;
};