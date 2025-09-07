#include <iostream>
#include <fstream>
#include <sstream>

const char FILE_FIRST_MATRIX[] = "fst.txt";
const char FILE_SECOND_MATRIX[] = "snd.txt";
const char FILE_RESULT[] = "result.txt";
const int MAX_INPUT_SIZE = 1000;

struct Matrix {
    int** content;
    size_t sizeX;
    size_t sizeY;
};

bool isMatrixActive(const Matrix& matrix) {
    return matrix.sizeX != 0 && matrix.sizeY != 0 && matrix.content != nullptr;
}

void initializeMatrixContent(Matrix& matrix) {
    matrix.content = new int* [matrix.sizeY];
    for (size_t i = 0; i < matrix.sizeY; i++) {
        matrix.content[i] = new int[matrix.sizeX];
    }
}

void deleteMatrixContent(Matrix& matrix) {
    if (!isMatrixActive(matrix)) {
        return;
    }

    for (size_t i = 0; i < matrix.sizeY; i++) {
        delete[] matrix.content[i];
    }

    delete matrix.content;
    matrix.sizeX = 0;
    matrix.sizeY = 0;
}

void printMatrixContent(const Matrix& matrix) {
    if (isMatrixActive(matrix)) {
        return;
    }

    for (size_t i = 0; i < matrix.sizeY; i++) {
        for (size_t j = 0; j < matrix.sizeX; j++) {
            std::cout << matrix.content[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

size_t countCharacters(std::ifstream& stream, char character, char breakCharacter = '\0') {
    if (!stream.is_open()) {
        std::cerr << "Error" << std::endl;
        return 0;
    }

    std::streampos pos = stream.tellg();

    size_t count = 0;
    while (true) {
        char current = stream.get();
        if (current == character && !stream.eof()) {
            count++;
        }
        else if (stream.eof() || current == breakCharacter) {
            break;
        }
    }

    stream.clear();
    stream.seekg(pos);

    return count;
}

Matrix readMatrix(const char* file) {
    if (file == nullptr) {
        std::cerr << "Error" << std::endl;
        return { nullptr, 0, 0 };
    }

    std::ifstream stream(file);

    if (!stream.is_open()) {
        std::cerr << "Error" << std::endl;
        return {nullptr, 0, 0};
    }

    Matrix result;

    result.sizeY = countCharacters(stream, '|') + 1;
    result.sizeX = countCharacters(stream, ',', '|') + 1;
    initializeMatrixContent(result);

    char str[MAX_INPUT_SIZE];

    for (size_t i = 0; i < result.sizeY; i++) {

        stream.getline(str, MAX_INPUT_SIZE, '|');

        std::stringstream stringstream(str);
        
        for (size_t j = 0; j < result.sizeX; j++) {
            stringstream >> result.content[i][j];
            stringstream.ignore();
        }
    }
    
    stream.close();

    return result;
}

void printInResult(const char* FILENAME, const Matrix& matrix) {
    if (FILENAME == nullptr || isMatrixActive(matrix)) {
        return;
    }
    
    std::ofstream stream(FILENAME);

    if (!stream.is_open()) {
        std::cerr << "Error" << std::endl;
        return;
    }

    for (size_t i = 0; i < matrix.sizeY - 1; i++)
    {
        for (size_t j = 0; j < matrix.sizeX; j++)
        {
            stream << matrix.content[i][j] << ",";
        }
        stream.seekp(-1, std::ios::cur);
        stream << "|";
    }

    for (size_t j = 0; j < matrix.sizeX - 1; j++)
    {
        stream << matrix.content[matrix.sizeY - 1][j] << ",";
    }

    stream << matrix.content[matrix.sizeY - 1][matrix.sizeX - 1];
    stream.close();
}

Matrix multiplyMatricies(const Matrix& first, const Matrix& second) {
    if (first.sizeY != second.sizeX) {
        return { nullptr, 0, 0 };
    }

    Matrix result;
    result.sizeX = first.sizeX;
    result.sizeY = second.sizeY;
    initializeMatrixContent(result);

    for (size_t i = 0; i < result.sizeY; i++)
    {
        for (size_t j = 0; j < result.sizeX; j++)
        {
            result.content[i][j] = 0;
            for (size_t k = 0; k < first.sizeY; k++)
            {
                result.content[i][j] += first.content[i][k] * second.content[k][j];
            }
        }
    }

    return result;
}

int main()
{
    Matrix firstMatrix = readMatrix(FILE_FIRST_MATRIX);
    if (!isMatrixActive(firstMatrix)) {
        return 0;
    }

    Matrix secondMatrix = readMatrix(FILE_SECOND_MATRIX);
    if (!isMatrixActive(secondMatrix)) {
        return 0;
    }

    Matrix product = multiplyMatricies(firstMatrix, secondMatrix);
    if (!isMatrixActive(product)) {
        return 0;
    }
    
    printInResult(FILE_RESULT, product);
    printMatrixContent(product);

    deleteMatrixContent(firstMatrix);
    deleteMatrixContent(secondMatrix);
    deleteMatrixContent(product);
}