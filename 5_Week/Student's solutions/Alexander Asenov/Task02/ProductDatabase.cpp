#include "ProductDatabase.h"

ProductsDatabase::ProductsDatabase()
{
    this->size = 0;
}

State ProductsDatabase::addProduct(const Product& product)
{
    if (this->existProduct(product.getOwnerID(), product.getProductID()))
    {
        return State::ProductInDB;
    }

    if (this->size >= this->MAX_NUMBER_OF_PRODUCTS)
    {
        return State::ProductFull;
    }

    this->products[this->size] = product;
    this->size++;
    return State::OK;
}

State ProductsDatabase::addProduct(const char* name, size_t id, size_t prodID, size_t quantity)
{
    if (name == nullptr)
    {
        return State::ProductNotFound;
    }

    return addProduct({ name, id, quantity, prodID });
}

size_t ProductsDatabase::itemsOwned(size_t id, size_t productID) const
{
    if (existProduct(id, productID))
    {
        return getProductByIdsConst(id, productID).getQuantity();
    }

    return 0;
}

State ProductsDatabase::update(size_t id, size_t productID, int update)
{
    if (!existProduct(id, productID))
    {
        return State::ProductNotFound;
    }

    Product& product = getProductByIds(id, productID);

    return product.updateQuantity(update);
}

bool ProductsDatabase::existProduct(size_t id, size_t prodID) const
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->products[i].getOwnerID() == id && this->products[i].getProductID() == prodID)
        {
            return true;
        }
    }

    return false;
}

const Product& ProductsDatabase::getProductByIdsConst(size_t id, size_t prodID) const
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->products[i].getOwnerID() == id && this->products[i].getProductID() == prodID)
        {
            return this->products[i];
        }
    }

    Product product;
    return product;
    //throw exception
}

Product& ProductsDatabase::getProductByIds(size_t id, size_t prodID)
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->products[i].getOwnerID() == id && this->products[i].getProductID() == prodID)
        {
            return this->products[i];
        }
    }

    Product product;
    return product;
    //throw exception
}