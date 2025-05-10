#include "Waffle.h"

Waffle::Waffle()
{

}

Waffle::Waffle(const char* brand, double weight, double wholesalePrice, double priceForClient)
{
    this->setBrand(brand);
    this->setWeight(weight);
    this->setWholesalePrice(wholesalePrice);
    this->setPriceForClient(priceForClient);
}

const char* Waffle::getBrand() const
{
    return this->brand;
}

void Waffle::setBrand(const char* brand)
{
    size_t sizeOfNewBrandName = strlen(brand);

    if (sizeOfNewBrandName > this->BRAND_MAX_LENGTH) {
        return;
    }

    strcpy_s(this->brand, static_cast<rsize_t>(this->BRAND_MAX_LENGTH) + 1, brand);
}

const double Waffle::getWeight() const
{
    return this->weight;
}

void Waffle::setWeight(double weight)
{
    if (weight < 0) {
        return;
    }

    this->weight = weight;
}

const double Waffle::getWholesalePrice() const
{
    return this->wholesalePrice;
}

void Waffle::setWholesalePrice(double wholesalePrice)
{
    if (wholesalePrice < 0) {
        return;
    }

    this->wholesalePrice = wholesalePrice;
}

const double Waffle::getPriceForClient() const
{
    return this->priceForClient;
}

void Waffle::setPriceForClient(double priceForClient)
{
    if (priceForClient < 0) {
        return;
    }

    this->priceForClient = priceForClient;
}

void Waffle::serializeInBinaryFile(std::ofstream& stream) const
{
    if (!stream.is_open()) {
        return;
    }

    stream.write(this->brand, this->BRAND_MAX_LENGTH);
    stream.write(reinterpret_cast<const char*>(&this->weight), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(&this->wholesalePrice), sizeof(double));
    stream.write(reinterpret_cast<const char*>(&this->priceForClient), sizeof(double));
}

void Waffle::deserializeInBinaryFile(std::ifstream& stream)
{
    if (!stream.is_open()) {
        return;
    }

    stream.read(this->brand, this->BRAND_MAX_LENGTH);
    stream.read(reinterpret_cast<char*>(&this->weight), sizeof(size_t));
    stream.read(reinterpret_cast<char*>(&this->wholesalePrice), sizeof(double));
    stream.read(reinterpret_cast<char*>(&this->priceForClient), sizeof(double));
}