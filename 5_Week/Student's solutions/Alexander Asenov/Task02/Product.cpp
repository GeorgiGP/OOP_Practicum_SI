#include "Product.h"
#include<iostream>

Product::Product()
{
    this->name[0] = '\0';
    this->ownedId = 0;
    this->quantity = 0;
    this->productId = 0;
}

Product::Product(const char* name, size_t ownedId, size_t quantity, size_t productId)
{
    strcpy_s(this->name, name);
    this->ownedId = ownedId;
    this->quantity = quantity;
    this->productId = productId;
}

const char* Product::getName() const
{
    return this->name;
}

size_t Product::getQuantity() const
{
    return this->quantity;
}

State Product::updateQuantity(int amount)
{
    if (amount < 0 && this->quantity < static_cast<size_t>((amount * (-1)))) 
    {
        return State::NegativeQuantity;
    }

    this->quantity += amount;
    return State::OK;
}

size_t Product::getProductID() const
{
    return this->productId;
}

size_t Product::getOwnerID() const
{
    return this->ownedId;
}
