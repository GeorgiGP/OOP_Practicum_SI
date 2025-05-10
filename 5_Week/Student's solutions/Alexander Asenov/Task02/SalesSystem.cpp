#include "SalesSystem.h"

SalesSystem::SalesSystem()
{
}

const User& SalesSystem::getUserById(size_t userID) const
{
    return this->users.getUserByIdConst(userID);
}

const Product& SalesSystem::getProductById(size_t userID, size_t productID) const
{
    return this->products.getProductByIdsConst(userID, productID);
}

State SalesSystem::addUser(const User& user)
{
    return this->users.addUser(user);
}

State SalesSystem::addProduct(const Product& product)
{
    if (!this->users.existUser(product.getOwnerID()))
    {
        return State::UserNotFound;
    }

    return this->products.addProduct(product);
}

State SalesSystem::addPrice(const Price& price)
{
    return this->prices.addPrice(price);
}

State SalesSystem::sell(size_t idFrom, size_t idTo, size_t productID, size_t quantity)
{
    Product& productFrom = this->products.getProductByIds(idFrom, productID);
    
    if (productFrom.getQuantity() < quantity)
    {
        return State::NotEnoughItems;
    }

    double price = this->prices.getPrice(productID);
    double totalPrice = price * quantity;
    User& from = this->users.getUserById(idFrom);
    User& to = this->users.getUserById(idTo);

    if (!to.hasMoney(totalPrice))
    {
        return State::ShortOnMoney;
    }

    if (!this->products.existProduct(idTo, productID))
    {
        State resultFromOperation = this->products.addProduct(productFrom.getName(), idTo, productFrom.getProductID(), 0);
        if(resultFromOperation != State::OK)
        {
            return resultFromOperation;
        }
    }

    Product& productTo = this->products.getProductByIds(idTo, productID);

    productFrom.updateQuantity(quantity * (-1));
    productTo.updateQuantity(quantity);
    
    from.updateMoney(totalPrice);
    to.updateMoney(totalPrice * (-1));

    return State();
}
