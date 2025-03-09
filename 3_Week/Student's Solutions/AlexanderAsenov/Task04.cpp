#include <iostream>
#include <fstream>
#include <sstream>

const char FILE_STUDENTS[] = "students.dat";

const size_t NAME_MAX_SIZE = 16; 
const size_t FACULTY_NUMBER_SIZE = 5;
const size_t BUFFER_MAX_SIZE = 100;

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

class Student {
private:
    char firstName[NAME_MAX_SIZE + 1];
    char lastName[NAME_MAX_SIZE + 1];
    char facultyNumber[FACULTY_NUMBER_SIZE + 1];
    double grade;

public:
    Student() {

    }

    Student(const char* firstName, const char* lastName, const char* facultyNumber,
        double grade) {
        setFirstName(firstName);
        setLastName(lastName);
        setFacultyNumber(facultyNumber);
        setGrade(grade);
    }

    char* getFirstName() {
        return this->firstName;
    }

    void setFirstName(const char* firstName) {
        if (firstName == nullptr || getStrLength(firstName) > NAME_MAX_SIZE) {
            return;
        }

        copyStr(this->firstName, firstName);
    }

    char* getLastName() {
        return this->lastName;
    }

    void setLastName(const char* lastName) {
        if (lastName == nullptr || getStrLength(lastName) > NAME_MAX_SIZE) {
            return;
        }

        copyStr(this->lastName, lastName);
    }

    char* getFacultyNumber() {
        return this->facultyNumber;
    }

    void setFacultyNumber(const char* faculyNumber) {
        if (getStrLength(faculyNumber) != FACULTY_NUMBER_SIZE) {
            return;
        }

        copyStr(this->facultyNumber, faculyNumber);
    }

    double getGrade() {
        return this->grade;
    }

    void setGrade(double grade) {
        this->grade = grade;
    }
};

size_t getFileSize(std::fstream& stream) {
    if (!stream.is_open()) {
        return 0;
    }

    std::streampos beginningPosition = stream.tellg();

    size_t result = stream.seekg(0, std::ios::end).tellg();

    stream.seekg(beginningPosition);

    return result;
}

void writeOnFile(const char* fileName, const Student& student) {
    if (fileName == nullptr) {
        return;
    }

    std::fstream stream(fileName, std::ios::out | std::ios::binary | std::ios::app);

    if (!stream.is_open()) {
        return;
    }

    stream.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    stream.close();
}

Student* readFile(const char* fileName, size_t& currentNumberOfRecords) {
    if (fileName == nullptr) {
        return nullptr;
    }

    std::fstream stream(fileName, std::ios::in | std::ios::binary);

    if (!stream.is_open()) {
        return nullptr;
    }

    size_t sizeOfStream = getFileSize(stream);
    currentNumberOfRecords = sizeOfStream / sizeof(Student);
    Student* result = new Student[currentNumberOfRecords];

    for (size_t i = 0; i < currentNumberOfRecords; i++)
    {
        stream.read(reinterpret_cast<char*>(&result[i]), sizeof(Student));
    }

    stream.close();
    return result;
}

int main()
{
    Student alan("Alan", "Georgiev","12345", 5.5);
    Student ivo("Ivo", "Ivanov","12445",  4.5);
    Student ivan("Ivan", "Ivanov","12345",  3.5);
    Student hristo("Hristo", "Hristov","12245", 3.5);
    Student georgi("Georgi", "Georgiev","12145", 6);
    Student stefan("Stefan", "Hristov","12315", 5.5);

    writeOnFile(FILE_STUDENTS, alan);
    writeOnFile(FILE_STUDENTS, ivo);
    writeOnFile(FILE_STUDENTS, ivan);
    writeOnFile(FILE_STUDENTS, hristo);
    writeOnFile(FILE_STUDENTS, georgi);
    writeOnFile(FILE_STUDENTS, stefan);

    size_t size;
    Student* students = readFile(FILE_STUDENTS, size);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << students[i].getFirstName() << " " << students[i].getLastName() << " "
            << students[i].getFacultyNumber() << " " << students[i].getGrade() << std::endl;
    }

    delete[] students;
}