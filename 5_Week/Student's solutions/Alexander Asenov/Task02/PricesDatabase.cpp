#include "PricesDatabase.h"

PricesDatabase::PricesDatabase()
{
    this->size = 0;
}

State PricesDatabase::addPrice(const Price& price)
{
    if (getPrice(price.getId()) != -1) 
    {
        return State::PriceInDB;
    }

    if (this->size >= this->MAX_NUMBER_OF_PRICES)
    {
        return State::PriceFull;
    }

    this->prices[this->size] = price;
    this->size++;

    return State::OK;
}

double PricesDatabase::getPrice(size_t id) const
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->prices[i].getId() == id)
        {
            return this->prices[i].getPrice();
        }
    }

    return -1;
}