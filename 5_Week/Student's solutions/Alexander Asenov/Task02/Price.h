#pragma once
#include "State.h";

class Price
{
private:
	size_t productId;
	double price;
public:
	Price();
	Price(size_t productId, double price);
	double getPrice() const;
	size_t getId() const;
	State updatePrice(double amount);
};