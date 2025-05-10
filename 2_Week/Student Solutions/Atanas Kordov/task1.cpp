#include <iostream>
#include <fstream>

using namespace std;

void writeSumAndMult(int num1, int num2, int num3, ofstream& outFile)
{
    if (!outFile.is_open())
    {
        cerr << "Can't open file.";
        return;
    }

    int sum = num1 + num2 + num3;
    int mul = num1 * num2 * num3;

    outFile << sum << " " << mul << "\n";
    outFile.close();
}

void readSub(ifstream& inFile)
{
    if (!inFile.is_open())
    {
        cerr << "Can't open file.";
        return;
    }

    int num1, num2;

    inFile >> num1 >> num2;

    cout << num1 - num2;

    inFile.close();
}