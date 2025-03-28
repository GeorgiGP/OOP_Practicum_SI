#pragma once
#include "State.h"

class User {

private:
	static const int NAME_LENGTH = 32;

	char name[NAME_LENGTH];
	size_t id;
	double balance;
public:
	User();
	User(size_t id, const char* name, double balance);
	State updateMoney(double factor);
	bool hasMoney(double args) const;
	size_t getID() const;
	double getBalance() const;
};