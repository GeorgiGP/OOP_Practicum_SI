#include "User.h"
#include <iostream>

User::User()
{
	this->id = 0;
	this->name[0] = '\0';
	this->balance = 0;
}

User::User(size_t id, const char* name, double balance)
{
	this->id = id;
	strcpy_s(this->name, name);
	this->balance = balance;
}

State User::updateMoney(double factor)
{
	if (factor + this->balance < 0) 
	{
		return State::NegativeBalance;
	}

	this->balance += factor;

	return State::OK;
}

bool User::hasMoney(double args) const
{
	return this->balance >= args;
}

size_t User::getID() const
{
	return this->id;
}

double User::getBalance() const
{
	return this->balance;
}
