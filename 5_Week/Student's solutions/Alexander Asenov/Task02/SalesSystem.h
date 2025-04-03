#pragma once
#include "UsersDatabase.h"
#include "ProductDatabase.h"
#include "PricesDatabase.h"

class SalesSystem
{
private:
	UsersDatabase users;
	ProductsDatabase products;
	PricesDatabase prices;

public:
	SalesSystem();
	const User& getUserById(size_t userID) const;
	const Product& getProductById(size_t userID, size_t productID) const;
	State addUser(const User& user);
	State addProduct(const Product& product);
	State addPrice(const Price& price);
	State sell(size_t idFrom, size_t idTo, size_t productID, size_t quantity);
};