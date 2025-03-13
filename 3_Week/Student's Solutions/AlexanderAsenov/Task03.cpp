#include <iostream>
#include <fstream>
#include <sstream>

const char FILE_STUDENTS[] = "students.csv";

const size_t NAME_MAX_SIZE = 16; 
const size_t FACULTY_NUMBER_SIZE = 5;
const size_t MAX_RECORDS_NUMBER = 1024;
const size_t BUFFER_MAX_SIZE = 100;

enum HairColor {
	brown,
	black,
	blond,
	red,
	white
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
	HairColor hairColor;
	double grade;

public:
    Student() {

    }

    Student(const char* firstName, const char* lastName, const char* facultyNumber,
        HairColor hairColor, double grade) {
        setFirstName(firstName);
        setLastName(lastName);
        setFacultyNumber(facultyNumber);
        setHairColor(hairColor);
        setGrade(grade);
    }

    char* getFirstName() {
        return this->firstName;
    }

    void setFirstName(const char* firstName) {
        if (getStrLength(firstName) > NAME_MAX_SIZE) {
            return;
        }

        copyStr(this->firstName, firstName);
    }

    char* getLastName() {
        return this->lastName;
    }

    void setLastName(const char* lastName) {
        if (getStrLength(lastName) > NAME_MAX_SIZE) {
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
    
    HairColor getHairColor() {
        return this->hairColor;
    }

    void setHairColor(HairColor hairColor) {
        this->hairColor = hairColor;
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

size_t countCharacters(std::fstream& stream, char character, char breakCharacter = '\0') {
    if (!stream.is_open()) {
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

std::stringstream encodeStudent(Student& student) {
    std::stringstream str;

    str << student.getFirstName() << "," << student.getLastName() << "," << student.getFacultyNumber()
        << "," << student.getHairColor() << "," << student.getGrade();

    return str;
}

Student decodeStudent(std::stringstream& stream) {
    Student result;

    char buffer[BUFFER_MAX_SIZE];

    stream.getline(buffer, BUFFER_MAX_SIZE, ',');
    result.setFirstName(buffer);

    stream.getline(buffer, BUFFER_MAX_SIZE, ',');
    result.setLastName(buffer);

    stream.getline(buffer, BUFFER_MAX_SIZE, ',');
    result.setFacultyNumber(buffer);

    int hairColor;
    stream >> hairColor;
    result.setHairColor(HairColor(hairColor));

    stream.ignore();
    
    double grade;
    stream >> grade;
    result.setGrade(grade);

    return result;
}

void writeOnFile(const char* fileName, Student& student) {
    if (fileName == nullptr) {
        return;
    }

    std::fstream stream(fileName, std::ios::in | std::ios::out | std::ios::app);

    if (!stream.is_open()) {
        return;
    }

    int currentNumberOfRecords = getFileSize(stream) > 0 ? countCharacters(stream, '\n') + 1 : 0;

    if (currentNumberOfRecords >= MAX_RECORDS_NUMBER) {
        stream.close();
        return;
    }

    stream.seekp(0, std::ios::end);

    std::stringstream encodedStudent = encodeStudent(student);
    
    if (currentNumberOfRecords != 0) {
        stream << '\n';
    }

    char current;
    while (encodedStudent.get(current)) {
        stream << current;
    }
}

Student* readFile(const char* fileName, size_t& currentNumberOfRecords) {
    if (fileName == nullptr) {
        return nullptr;
    }

    std::fstream stream(fileName, std::ios::in);

    if (!stream.is_open()) {
        return nullptr;
    }

    currentNumberOfRecords = getFileSize(stream) > 0 ? countCharacters(stream, '\n') + 1 : 0;

    Student* result = new Student[currentNumberOfRecords];

    char buffer[BUFFER_MAX_SIZE];
    for (size_t i = 0; i < currentNumberOfRecords; i++)
    {
        stream.getline(buffer, BUFFER_MAX_SIZE);
        std::stringstream stringstream(buffer);

        result[i] = decodeStudent(stringstream);
    }

    stream.close();
    return result;
}

int main()
{
    /*Student alan("Alan", "Georgiev","12345", HairColor::black, 5.5);
    Student ivo("Ivo", "Ivanov","12445", HairColor::blond, 4.5);
    Student ivan("Ivan", "Ivanov","12345", HairColor::black, 3.5);
    Student hristo("Hristo", "Hristov","12245", HairColor::red, 3.5);
    Student georgi("Georgi", "Georgiev","12145", HairColor::white, 6);
    Student stefan("Stefan", "Hristov","12315", HairColor::brown, 5.5);

    writeOnFile(FILE_STUDENTS, alan);
    writeOnFile(FILE_STUDENTS, ivo);
    writeOnFile(FILE_STUDENTS, ivan);
    writeOnFile(FILE_STUDENTS, hristo);
    writeOnFile(FILE_STUDENTS, georgi);
    writeOnFile(FILE_STUDENTS, stefan);*/

    size_t size;
    Student* students = readFile(FILE_STUDENTS, size);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << students[i].getFirstName() << " " << students[i].getLastName() << " "
            << students[i].getFacultyNumber() << " " << students[i].getHairColor() << " "
            << students[i].getGrade() << std::endl;
    }

    delete[] students;
}