#include "UsersDatabase.h"
#include "User.h"

UsersDatabase::UsersDatabase()
{
    this->size = 0;
}

State UsersDatabase::addUser(const User& user)
{
    if (this->size == this->MAX_NUMBER_OF_USERS)
    {
        return State::UserFull;
    }

    if (this->existUser(user.getID())) 
    {
        return State::UserInDB;
    }

    this->users[this->size] = user;
    this->size++;

    return State::OK;
}

bool UsersDatabase::hasEnoughMoney(size_t id, double money) const
{
    return getUserByIdConst(id).hasMoney(money);
}

bool UsersDatabase::existUser(size_t id) const
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->users[i].getID() == id)
        {
            return true;
        }
    }

    return false;
}

const User& UsersDatabase::getUserByIdConst(size_t id) const
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->users[i].getID() == id)
        {
            return this->users[i];
        }
    }

    //throw exception
}

User& UsersDatabase::getUserById(size_t id)
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (this->users[i].getID() == id)
        {
            return this->users[i];
        }
    }

    //throw exception
}
