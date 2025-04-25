#pragma once
class Computer
{
private:
	double powerCPU;
	char* modelVideoCard;
	int PSU;
	int RAM;

	void free();
	void copyFrom(const Computer& other);
public:
	Computer(double powerCpu, const char* model, int PSU, int RAM);
	Computer(const Computer& other);
	Computer& operator=(const Computer& other);
	~Computer();

	int getRAM() const;
	int getPSU() const;
	const char* getModelVideoCard() const;
	double getPoweCPU() const;

	void setRAM(int);
	void setPSU(int);
	void setModelVideoCard(const char*);
	void setPoweCPU(double);

	virtual const char* getType() const = 0;
	virtual const char* getPerifer() const = 0;
};

