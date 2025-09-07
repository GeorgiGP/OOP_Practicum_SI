#include <iostream>
#include "SalesSystem.h"

int main()
{
	SalesSystem salesSystem;
	salesSystem.addUser({ 1, "Name1", 100 });
	salesSystem.addUser({ 2, "Name2", 200 });
	salesSystem.addProduct({ "Product1", 1, 10, 1 });
	salesSystem.addProduct({ "Product2", 2, 10, 2 });
	salesSystem.addPrice({ 1, 5 });
	salesSystem.addPrice({ 2, 3 });

	std::cout << salesSystem.getUserById(1).getBalance()
		<< " "
		<< salesSystem.getProductById(1, 1).getQuantity()
		<< " "
		<< salesSystem.getProductById(1, 2).getQuantity()
		<< std::endl;

	std::cout << salesSystem.getUserById(2).getBalance()
		<< " "
		<< salesSystem.getProductById(2, 1).getQuantity()
		<< " "
		<< salesSystem.getProductById(2, 2).getQuantity()
		<< std::endl;

	salesSystem.sell(1, 2, 1, 5);
	salesSystem.sell(2, 1, 2, 5);
	salesSystem.sell(2, 1, 1, 4);
	salesSystem.sell(1, 2, 2, 4);

	std::cout << salesSystem.getUserById(1).getBalance()
		<< " "
		<< salesSystem.getProductById(1, 1).getQuantity()
		<< " "
		<< salesSystem.getProductById(1, 2).getQuantity()
		<< std::endl;

	std::cout << salesSystem.getUserById(2).getBalance()
		<< " "
		<< salesSystem.getProductById(2, 1).getQuantity()
		<< " "
		<< salesSystem.getProductById(2, 2).getQuantity()
		<< std::endl;
}