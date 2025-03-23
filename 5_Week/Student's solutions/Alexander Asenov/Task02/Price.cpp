#include "Price.h"
#include "State.h"

Price::Price()
{
    this->price = 0;
    this->productId = 0;
}

Price::Price(size_t productId, double price)
{
    this->productId = productId;
    this->price = price > 0 ? price : 0;
}

double Price::getPrice() const
{
    return this->price;
}

size_t Price::getId() const
{
    return this->productId;
}

State Price::updatePrice(double amount)
{
    if (this->price + amount < 0) 
    {
        return State::NegativeBalance;
    }

    this->price += amount;
    return State::OK;
}
