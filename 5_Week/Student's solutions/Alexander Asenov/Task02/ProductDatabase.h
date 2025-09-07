#pragma once
#include "Product.h"

class ProductsDatabase
{
private:
	static const int MAX_NUMBER_OF_PRODUCTS = 50;

	Product products[MAX_NUMBER_OF_PRODUCTS];
	size_t size;
	
public:
	ProductsDatabase();
	State addProduct(const Product& product);
	State addProduct(const char* name, size_t id, size_t prodID, size_t quantitr);
	size_t itemsOwned(size_t id, size_t productID) const;
	State update(size_t id, size_t productID, int update);
	bool existProduct(size_t id, size_t prodID) const;
	const Product& getProductByIdsConst(size_t id, size_t prodID) const;
	Product& getProductByIds(size_t id, size_t prodID);
};