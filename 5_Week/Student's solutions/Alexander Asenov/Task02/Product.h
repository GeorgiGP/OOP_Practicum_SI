#pragma once
#include "State.h"

class Product {
private:
	static const size_t NAME_SIZE = 32;

	char name[NAME_SIZE];
	size_t ownedId;
	size_t quantity;
	size_t productId;
public:
	Product();
	Product(const char* name, size_t ownedId, size_t quantity, size_t productId);
	const char* getName() const;
	size_t getQuantity() const;
	State updateQuantity(int amount);
	size_t getProductID() const;
	size_t getOwnerID() const;
};