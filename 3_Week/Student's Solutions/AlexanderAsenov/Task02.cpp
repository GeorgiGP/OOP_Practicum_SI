#include <iostream>
#include <fstream>

const char FILENAME[] = "file.txt";

void replaceCharInFile(const char* fileName, char find, char replace) {
    if (fileName == nullptr) {
        return;
    }

    std::fstream stream(fileName, std::ios::in | std::ios::out);

    if (!stream.is_open()) {
        std::cerr << "Error" << std::endl;
        return;
    }

    char currentChar;
    while (stream.get(currentChar)) {
        if (currentChar == find) {
            stream.seekp(-1, std::ios::cur);
            stream << replace;
            stream.flush();
        }
    }

    stream.close();
}

int main()
{
    replaceCharInFile(FILENAME, 'a', 'b');
}