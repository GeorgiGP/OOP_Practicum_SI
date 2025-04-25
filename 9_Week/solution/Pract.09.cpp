#include <iostream>
#include "ElectricCar.h"

int main()
{
    {
        ElectricCar OB4444AP(0, 0, 400, 45, Battery(0, 0, 100000), "VW", "Golf Thunder", 2030, 190);

        {
            ElectricCar pleb(OB4444AP);
        }
    }

    _CrtDumpMemoryLeaks();
}
