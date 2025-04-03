#pragma once
#include "Waffle.h"

class WaffleMarket
{
private:
	size_t maxWafflesCount;
	size_t wafflesCount;
	double revenue;
	double expenses;
	Waffle* waffles;

	void copy(const WaffleMarket& waffleMarket);
	void remove();
public:
	WaffleMarket(size_t maxNumberOfWaffles);
	WaffleMarket(const WaffleMarket& waffleMarket);
	WaffleMarket& operator=(const WaffleMarket& waffleMarket);
	~WaffleMarket();

	size_t getWafflesCount() const;
	size_t getMaxWafflesCount() const;
	double getRevenue() const;
	double getExpenses() const;
	const Waffle* getWaffles() const;

	void sellWaffle(const char* brand);
	void sellWaffles(size_t numberOfWafflesNeeded, const char* brand);
	bool isWaffleBrandSold(const char* brand) const;
	void buyWaffles(size_t numberOfWaffles, const char* brand);
	size_t getWafflesByBrand(const char* brand) const;
	void printWafflesCount(const char* brand) const;
	void printProfit() const;

	void serializeInBinaryFile(std::ofstream& stream) const;
	void deserializeInBinaryFile(std::ifstream& stream);
};