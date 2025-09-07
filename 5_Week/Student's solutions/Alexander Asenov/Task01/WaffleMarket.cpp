#include "WaffleMarket.h"
#include <iostream>

void WaffleMarket::copy(const WaffleMarket& waffleMarket)
{
    this->maxWafflesCount = waffleMarket.getMaxWafflesCount();
    this->wafflesCount = waffleMarket.getWafflesCount();
    this->revenue = waffleMarket.getRevenue();
    this->expenses = waffleMarket.getExpenses();
    this->waffles = new Waffle[this->getWafflesCount()];

    if (this->maxWafflesCount < this->wafflesCount)
    {
        this->wafflesCount = this->maxWafflesCount;
    }

    for (size_t i = 0; i < this->wafflesCount; i++)
    {
        waffles[i] = waffleMarket.getWaffles()[i];
    }
}

void WaffleMarket::remove()
{
    delete[] this->waffles;
    this->waffles = nullptr;
}

WaffleMarket::WaffleMarket(size_t maxWafflesCount)
{
    this->maxWafflesCount = maxWafflesCount;
    this->wafflesCount = 0;
    this->revenue = 0;
    this->expenses = 0;
    this->waffles = new Waffle[maxWafflesCount];
}

WaffleMarket::WaffleMarket(const WaffleMarket& waffleMarket)
{
    copy(waffleMarket);
}

WaffleMarket& WaffleMarket::operator=(const WaffleMarket& waffleMarket)
{
    if (this != &waffleMarket) {
        remove();
        copy(waffleMarket);
    }

    return *this;
}

WaffleMarket::~WaffleMarket()
{
    remove();
}

size_t WaffleMarket::getWafflesCount() const
{
    return this->wafflesCount;
}

size_t WaffleMarket::getMaxWafflesCount() const
{
    return this->maxWafflesCount;
}

double WaffleMarket::getRevenue() const
{
    return this->revenue;
}

double WaffleMarket::getExpenses() const
{
    return this->expenses;
}

const Waffle* WaffleMarket::getWaffles() const
{
    return this->waffles;
}

void WaffleMarket::sellWaffle(const char* brand)
{
    this->sellWaffles(1, brand);
}

void WaffleMarket::sellWaffles(size_t numberOfWafflesNeeded, const char* brand)
{
    size_t numberOfWafflesInStock = getWafflesByBrand(brand);

    if (numberOfWafflesNeeded > numberOfWafflesInStock) {
        return;
    }

    this->wafflesCount -= numberOfWafflesNeeded;

    for (size_t i = 0, j = 0; i < this->wafflesCount; i++)
    {
        while (strcmp(this->waffles[i].getBrand(), brand) == 0 && numberOfWafflesNeeded > 0) 
        {
            j++;
            numberOfWafflesNeeded--;
            this->revenue += this->waffles[i].getPriceForClient();
        }

        this->waffles[i] = this->waffles[i + j];
    }
}

bool WaffleMarket::isWaffleBrandSold(const char* brand) const
{
    for (size_t i = 0; i < this->wafflesCount; i++)
    {
        if (strcmp(this->waffles[i].getBrand(), brand) == 0) 
        {
            return true;
        }
    }
    return false;
}

void WaffleMarket::buyWaffles(size_t numberOfWaffles, const char* brand)
{
    if (this->wafflesCount + numberOfWaffles > this->maxWafflesCount)
    {
        return;
    }

    Waffle waffle(brand);
    for (size_t i = 0; i < numberOfWaffles; i++)
    {
        this->waffles[i + this->wafflesCount] = waffle;
        this->expenses += waffle.getWholesalePrice();
    }
    this->wafflesCount += numberOfWaffles;
}

size_t WaffleMarket::getWafflesByBrand(const char* brand) const
{
    size_t result = 0;
    for (size_t i = 0; i < this->wafflesCount; i++)
    {
        if (strcmp(this->waffles[i].getBrand(), brand) == 0) 
        {
            result++;
        }
    }

    return result;
}

void WaffleMarket::printWafflesCount(const char* brand) const
{
    std::cout << getWafflesByBrand(brand) << std::endl;
}

void WaffleMarket::printProfit() const
{
    std::cout << (this->revenue - this->expenses) << std::endl;
}

void WaffleMarket::serializeInBinaryFile(std::ofstream& stream) const
{
    if (!stream.is_open()) 
    {
        return;
    }

    size_t maxWafflesCount;
    size_t wafflesCount;
    double revenue;
    double expenses;
    Waffle* waffles;
    stream.write(reinterpret_cast<const char*>(&this->maxWafflesCount), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(&this->wafflesCount), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(&this->revenue), sizeof(double));
    stream.write(reinterpret_cast<const char*>(&this->expenses), sizeof(double));
    
    for (size_t i = 0; i < this->wafflesCount; i++)
    {
        this->waffles[i].serializeInBinaryFile(stream);
    }
}

void WaffleMarket::deserializeInBinaryFile(std::ifstream& stream)
{
    stream.read(reinterpret_cast<char*>(&this->maxWafflesCount), sizeof(size_t));
    stream.read(reinterpret_cast<char*>(&this->wafflesCount), sizeof(size_t));
    stream.read(reinterpret_cast<char*>(&this->revenue), sizeof(double));
    stream.read(reinterpret_cast<char*>(&this->expenses), sizeof(double));

    this->waffles = new Waffle[this->maxWafflesCount];

    if (this->maxWafflesCount < this->wafflesCount)
    {
        this->wafflesCount = this->maxWafflesCount;
    }

    for (size_t i = 0; i < this->wafflesCount; i++)
    {
        this->waffles[i].deserializeInBinaryFile(stream);
    }
}
