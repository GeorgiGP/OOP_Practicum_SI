#include <iostream>
#include <fstream>
#include <sstream>

const size_t COMPANY_NAME_MAX_SIZE = 25;
const size_t BUFFER_MAX_SIZE = 100;
char JOB_OFFERS_FILENAME[] = "jobOffers.dat";

struct JobOffer {
	char companyName[COMPANY_NAME_MAX_SIZE + 1];
	int numberOfCoworkers;
	int numberOfDaysOff;
	long long salary;
};

size_t getStrLength(const char* str) {
	if (str == nullptr) {
		return 0;
	}

	int count = 0;
	while (str[count] != '\0') {
		count++;
	}

	return count;
}

char* toLowerStr(const char* str) {
	if (str == nullptr) {
		return nullptr;
	}

	size_t size = getStrLength(str);

	char* result = new char[size + 1];
	for (size_t i = 0; i < size; i++) {
		if ('A' <= str[i] && str[i] <= 'Z') {
			result[i] = str[i] - 'A' + 'a';
		}
		else {
			result[i] = str[i];
		}
	}

	result[size] = '\0';
	return result;
}

size_t getFileSize(std::ifstream& stream) {
	if (!stream.is_open()) {
		return 0;
	}

	std::streampos beginningPosition = stream.tellg();

	size_t result = stream.seekg(0, std::ios::end).tellg();

	stream.seekg(beginningPosition);

	return result;
}

void copyStr(char* dest, const char* source) {
	if (dest == nullptr || source == nullptr) {
		return;
	}

	while (*source != '\0') {
		*dest = *source;
		dest++;
		source++;
	}
	*dest = *source;
}

int strCompare(const char* str1, const char* str2) {
	if (str1 == nullptr || str2 == nullptr) {
		return -2;
	}

	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 < *str2) {
			return -1;
		}
		else if (*str1 > *str2) {
			return 1;
		}

		str1++;
		str2++;
	}

	if (*str1 == '\0' && *str2 == '\0') {
		return 0;
	}

	if (*str1 == '\0') {
		return -1;
	}

	return 1;
}

void writeCompaniesInFile(const char* fileName, const JobOffer* jobOffers, size_t numberOfJobOffers) {
	if (fileName == nullptr || jobOffers == nullptr) {
		return;
	}

	std::ofstream stream(fileName, std::ios::app | std::ios::binary);

	if (!stream.is_open()) {
		return;
	}

	for (size_t i = 0; i < numberOfJobOffers; i++)
	{
		stream.write(reinterpret_cast<const char*>(&jobOffers[i]), sizeof(JobOffer));
	}
}

void enterJobOffersInFile(const char* filename) {
	if (filename == nullptr) {
		return;
	}

	size_t numberOfJobOffers;

	std::cout << "Enter the number of job offers: ";
	std::cin >> numberOfJobOffers;

	JobOffer* jobOffers = new JobOffer[numberOfJobOffers];

	std::cout << "Enter companies in format {company name} {number of coworkers} {number of days off} {salary}:" << std::endl;

	std::cin.get();

	char buffer[BUFFER_MAX_SIZE];
	for (size_t i = 0; i < numberOfJobOffers; i++)
	{
		std::cin.getline(buffer, BUFFER_MAX_SIZE);
		std::stringstream sstream(buffer);
		sstream.getline(jobOffers[i].companyName, COMPANY_NAME_MAX_SIZE + 1, ' ');
		sstream >> jobOffers[i].numberOfCoworkers;
		sstream >> jobOffers[i].numberOfDaysOff;
		sstream >> jobOffers[i].salary;
	}

	writeCompaniesInFile(filename, jobOffers, numberOfJobOffers);
}

JobOffer* readJobOffersFromFile(const char* fileName, size_t& numberOfJobOffers) {
	if (fileName == nullptr) {
		return nullptr;
	}

	std::ifstream stream(fileName, std::ios::in | std::ios::binary);

	if (!stream.is_open()) {
		return nullptr;
	}

	numberOfJobOffers = getFileSize(stream) > 0 ? getFileSize(stream) / sizeof(JobOffer) : 0;

	JobOffer* result = new JobOffer[numberOfJobOffers];

	for (size_t i = 0; i < numberOfJobOffers; i++)
	{
		stream.read(reinterpret_cast<char*>(&result[i]), sizeof(JobOffer));
	}

	return result;
}

void enterJobOfferInFile(const char* filename) {
	if (filename == nullptr) {
		return;
	}

	JobOffer jobOffers;

	std::cin.get();

	char buffer[BUFFER_MAX_SIZE];

	std::cin.getline(buffer, BUFFER_MAX_SIZE);
	std::stringstream sstream(buffer);
	sstream.getline(jobOffers.companyName, COMPANY_NAME_MAX_SIZE + 1, ' ');
	sstream >> jobOffers.numberOfCoworkers;
	sstream >> jobOffers.numberOfDaysOff;
	sstream >> jobOffers.salary;


	writeCompaniesInFile(filename, &jobOffers, 1);
}

void showOffers(const char* filename) {
	if (filename == nullptr) {
		return;
	}

	size_t numberOfJobOffers = 0;
	JobOffer* jobOffers = readJobOffersFromFile(filename, numberOfJobOffers);
	if (jobOffers == nullptr) {
		return;
	}

	for (size_t i = 0; i < numberOfJobOffers; i++)
	{
		std::cout << jobOffers[i].companyName << " " << jobOffers[i].numberOfCoworkers << " "
			<< jobOffers[i].numberOfDaysOff << " " << jobOffers[i].salary << std::endl;
	}
}

void filterOffers(const char* filename, long long salary) {
	if (filename == nullptr) {
		return;
	}

	size_t numberOfJobOffers = 0;
	JobOffer* jobOffers = readJobOffersFromFile(filename, numberOfJobOffers);
	if (jobOffers == nullptr) {
		return;
	}

	for (size_t i = 0; i < numberOfJobOffers; i++)
	{
		if (jobOffers[i].salary >= salary) {
			std::cout << jobOffers[i].companyName << " " << jobOffers[i].numberOfCoworkers << " "
				<< jobOffers[i].numberOfDaysOff << " " << jobOffers[i].salary << std::endl;
		}
	}
}

bool existOffer(const char* filepath, const char* name) {
	if (filepath == nullptr || name == nullptr) {
		return false;
	}

	size_t numberOfJobOffers = 0;
	JobOffer* jobOffers = readJobOffersFromFile(filepath, numberOfJobOffers);
	if (jobOffers == nullptr) {
		return false;
	}

	char* nameToLower = toLowerStr(name);
	char* companyNameToLower;

	for (size_t i = 0; i < numberOfJobOffers; i++)
	{
		companyNameToLower = toLowerStr(jobOffers[i].companyName);
		if (strCompare(companyNameToLower, nameToLower) == 0) {
			delete[] nameToLower;
			delete[] companyNameToLower;
			return true;
		}
		delete[] companyNameToLower;
	}

	delete[] nameToLower;
	return false;
}

void perfectOffer(const char* filePath, int maxCoworkers, int minVacancyDays, int minSalary) {
	size_t numberOfJobOffers = 0;
	JobOffer* jobOffers = readJobOffersFromFile(filePath, numberOfJobOffers);
	if (jobOffers == nullptr) {
		return;
	}

	for (size_t i = 0; i < numberOfJobOffers; i++)
	{
		if (jobOffers[i].numberOfCoworkers <= maxCoworkers && minVacancyDays <= jobOffers[i].numberOfDaysOff
			&& minSalary <= jobOffers[i].salary) {
			std::cout << jobOffers[i].companyName << " " << jobOffers[i].numberOfCoworkers << " "
				<< jobOffers[i].numberOfDaysOff << " " << jobOffers[i].salary << std::endl;
		}
	}
}

int main()
{
	//enterJobOffersInFile(JOB_OFFERS_FILENAME);
	//filterOffers(JOB_OFFERS_FILENAME, 90000);
	//std::cout << existOffer(JOB_OFFERS_FILENAME, "GreenEnergyInc.") << std::endl;
	//perfectOffer(JOB_OFFERS_FILENAME, 80, 21, 40000);

	char command = '\0';

	while (command != 'q') {
		std::cin >> command;

		switch (command)
		{
		case 'a':
			enterJobOfferInFile(JOB_OFFERS_FILENAME);
			break;
		case 'i':
			showOffers(JOB_OFFERS_FILENAME);
			break;
		case 's':
			char buffer[BUFFER_MAX_SIZE];
			std::cin.get();
			std::cin.getline(buffer, BUFFER_MAX_SIZE);
			std::cout << (existOffer(JOB_OFFERS_FILENAME, buffer) ? "Yes" : "No") << std::endl;
			break;
		case 'f':
			long long minSalary;
			std::cin >> minSalary;
			filterOffers(JOB_OFFERS_FILENAME, minSalary);
			break;
		default:
			break;
		}
	}
}