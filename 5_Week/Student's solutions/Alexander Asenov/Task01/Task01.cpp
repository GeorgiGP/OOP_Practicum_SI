#include <iostream>
#include "Waffle.h"
#include "WaffleMarket.h"

const char* FILENAME = "file.dat";
const char* BRAND_NAME = "insert brand name";

int main() {
	WaffleMarket waffleMarket(1000);

	waffleMarket.buyWaffles(1000, BRAND_NAME);
	waffleMarket.sellWaffles(900, BRAND_NAME);

	waffleMarket.printProfit();
	
	std::ofstream writeStream(FILENAME, std::ios::binary | std::ios::out);

	if (!writeStream.is_open()) 
	{
		return 0;
	}

	waffleMarket.serializeInBinaryFile(writeStream);

	writeStream.close();

	std::ifstream readStream(FILENAME, std::ios::binary | std::ios::in);

	if (!readStream.is_open())
	{
		return 0;
	}

	WaffleMarket waffleMarketRead(10);

	waffleMarketRead.deserializeInBinaryFile(readStream);

	waffleMarketRead.printProfit();

	readStream.close();
}