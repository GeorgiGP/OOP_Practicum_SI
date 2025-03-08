#include <iostream>
#include <fstream>
#include <sstream> 
#include <cstdlib>
#include <crtdbg.h>
int getCountCols(const char* data) {
	std::stringstream ss(data);
	int count = 0;
	while (!ss.eof())
	{
		int curr;
		ss >> curr;
		count++;
		if (ss.get() == '|')
		{
			return count;
		}
	}
	return count;
}
int findOccur(const char* data, char ch) {
	std::stringstream ss(data);
	int count = 0;
	while (!ss.eof())
	{
		char chCurr;
		chCurr = ss.get();
		if (ch == chCurr)
		{
			count++;
		}
	}
	return count;
}

int getCountRows(const char* data) {
	return findOccur(data, '|') + 1;
}
#pragma warning(disable: 4996)
const char* extractData(std::ifstream& ifs) {
	std::string s;
	char buff[1024];
	while (ifs.getline(buff, 1024))
	{
		s += buff;
	}
	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	char* res = new char[s.size() + 1];
	strcpy(res, s.c_str());
	return res;
}

int** createEmptyMatrix(int rows, int cols) {
	int** result = new int* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		result[i] = new int[cols] {};
	}
	return result;
}

int** extractMatrix(std::ifstream& ifs, int& rows, int& cols) {
	const char* data = extractData(ifs);
	rows = getCountRows(data);
	cols = getCountCols(data);
	delete[] data;
	int** result = createEmptyMatrix(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			ifs >> result[i][j];
			ifs.ignore();
		}
	}
	return result;
}

//For any type its the same but discussed later in the course,
//for now use only the corner case with freeMatrix(int**, ...)
template <class T>
void freeMatrix(T** matrix, int rows, int cols) {
	for (size_t i = 0; i < rows; i++)
	{
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
}

void multiplyMatrix(const char* file1, const char* file2, const char* result) {
	if (!file1 || !file2 || !result) {
		std::cerr << "Files cannot be null";
		throw std::invalid_argument("Files cannot be null from exception"); //this exits the functions
	}
	std::ifstream ifs1(file1);
	if (!ifs1.is_open()) {
		std::cerr << "File with name: " << file1 << "cannot be found";
		throw std::invalid_argument(std::string("File with name: ") + file1 + " cannot be found");
	}
	std::ifstream ifs2(file2);
	if (!ifs2.is_open()) {
		ifs1.close();
		std::cerr << "File with name: " << file2 << "cannot be found";
		throw std::invalid_argument(std::string("File with name: ") + file2 + " cannot be found");
	}
	std::ofstream ofs(result);
	if (!ofs.is_open()) {
		ifs1.close();
		ifs2.close();
		std::cerr << "File with name: " << result << "cannot be found";
		throw std::invalid_argument(std::string("File with name: ") + result + " cannot be opened"); //this exits the functions
	}
	int rows1, cols1, rows2, cols2;
	int** matrix1 = extractMatrix(ifs1, rows1, cols1);
	int** matrix2 = extractMatrix(ifs2, rows2, cols2);
	ifs1.close();
	ifs2.close();

	if (cols1 != rows2) {
		std::cerr << "Not matching cols1 and rows2";
		throw std::invalid_argument("Not matching cols1 and rows2"); //this exits the functions
	} 
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < cols2; j++) {
			int temp = 0;
			for (int k = 0; k < cols1; k++) {
				temp += matrix1[i][k] * matrix2[k][j];
			}
			ofs << temp << ',';
		}
		ofs.seekp(-1, std::ios::cur);
		ofs.put('|');
	}
	ofs.seekp(-1, std::ios::cur);
	ofs.put(' ');
	ofs.close();
	freeMatrix(matrix1, rows1, cols1);
	freeMatrix(matrix2, rows2, cols2);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try
	{
		multiplyMatrix("crit1.txt", "crit2.txt", "res.txt");
		int* a = new int(3);
	}
	catch (const std::exception& e)
	{
		std::cerr << std::endl << e.what();
	}
}