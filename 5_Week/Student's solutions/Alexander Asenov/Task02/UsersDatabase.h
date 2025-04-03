#pragma once
#include "User.h"

class UsersDatabase
{
private:
	static const int MAX_NUMBER_OF_USERS = 50;

	User users[MAX_NUMBER_OF_USERS];
	size_t size;
public:
	UsersDatabase();
	State addUser(const User& user);
	bool hasEnoughMoney(size_t id, double money) const;
	bool existUser(size_t id) const;
	const User& getUserByIdConst(size_t id) const;
	User& getUserById(size_t id);
};