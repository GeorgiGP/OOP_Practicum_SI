#include <iostream>
#include "Computer.h"
#include "Laptop.h"
int main()
{
    Laptop l(4, "a", 2, 2);
    Computer* c = &l;
    std::cout << "Hello World!\n";
}
