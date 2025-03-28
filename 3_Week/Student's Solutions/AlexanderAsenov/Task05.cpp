#include <iostream>
#include <fstream>
#include <sstream>

const char FILE_STUDENTS[] = "students.dat";

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

class AutoResizeString {
private:
    size_t buffer = 0;
    char* content;

public:
    AutoResizeString(int buffer = 2) {
        content = new char[buffer];
        this->buffer = buffer;
    }

    ~AutoResizeString() {
        delete[] content;
    }

    char* getContent() {
        return this->content;
    }

    void setContent(const char* content) {
        if (content == nullptr) {
            return;
        }

        int newContentSize = getStrLength(content) + 1;

        if (newContentSize < this->buffer / 2) {
            while (newContentSize < this->buffer / 2)
            {
                this->buffer /= 2;
            }

            if (this->buffer == 0) {
                this->buffer = 2;
            }

            delete[] this->content;
            this->content = new char[this->buffer];
            copyStr(this->content, content);
        }
        else if (newContentSize <= this->buffer) {
            copyStr(this->content, content);
        }
        else {
            while (newContentSize > this->buffer) {
                this->buffer *= 2;
            }

            delete[] this->content;
            this->content = new char[this->buffer];
            copyStr(this->content, content);
        }
    }
};

class Student {
private:
    AutoResizeString firstName;
    AutoResizeString lastName;
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
        return this->firstName.getContent();
    }

    void setFirstName(const char* firstName) {
        this->firstName.setContent(firstName);
    }

    char* getLastName() {
        return this->lastName.getContent();
    }

    void setLastName(const char* lastName) {
        this->lastName.setContent(lastName);
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

    std::streampos startPosition = stream.tellg();

    size_t result = stream.seekg(0, std::ios::end).tellg();

    stream.seekg(startPosition);

    return result;
}

void writeOnFile(std::fstream& stream, Student& student) {
    size_t fileSize = getFileSize(stream);

    std::streampos startPosition = stream.tellg();

    size_t currentNumberOfStudents = 0;
    
    if (fileSize > 0) {
        stream.seekg(0, std::ios::beg);
        stream.read(reinterpret_cast<char*>(&currentNumberOfStudents), sizeof(size_t));
    }

    currentNumberOfStudents+=1;
    stream.seekp(0, std::ios::beg);
    stream.write(reinterpret_cast<const char*>(&currentNumberOfStudents), sizeof(size_t));

    stream.flush();

    stream.seekp(0, std::ios::end);

    size_t currentNameLength = getStrLength(student.getFirstName()) + 1;
    stream.write(reinterpret_cast<const char*>(&currentNameLength), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(student.getFirstName()), currentNameLength);

    currentNameLength = getStrLength(student.getLastName()) + 1;
    stream.write(reinterpret_cast<const char*>(&currentNameLength), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(student.getLastName()), currentNameLength);

    stream.write(reinterpret_cast<const char*>(student.getFacultyNumber()), FACULTY_NUMBER_SIZE + 1);
    
    double grade = student.getGrade();
    stream.write(reinterpret_cast<const char*>(&grade), sizeof(double));

    stream.flush();

    stream.seekg(startPosition);
}

void makeSureFileExists(const char* fileName) {
    if (fileName == nullptr) {
        return;
    }

    std::ofstream makeSureExists(fileName, std::ios::app);
}

void writeOnFile(const char* fileName, Student& student) {
    if (fileName == nullptr) {
        return;
    }

    makeSureFileExists(fileName);
    std::fstream stream(fileName, std::ios::in | std::ios::out | std::ios::binary);

    if (!stream.is_open()) {
        return;
    }

    writeOnFile(stream, student);
    stream.close();
}

void readNextStudent(std::fstream& stream, Student& next) {
    size_t sizeCurrentName = 0;
    stream.read(reinterpret_cast<char*>(&sizeCurrentName), sizeof(size_t));

    char* firstName = new char[sizeCurrentName];
    stream.read(firstName, sizeCurrentName);
    next.setFirstName(firstName);

    stream.read(reinterpret_cast<char*>(&sizeCurrentName), sizeof(size_t));
    
    char* lastName = new char[sizeCurrentName];
    stream.read(lastName, sizeCurrentName);
    next.setLastName(lastName);

    char facultyNumber[FACULTY_NUMBER_SIZE + 1];
    stream.read(facultyNumber, FACULTY_NUMBER_SIZE + 1);
    next.setFacultyNumber(facultyNumber);

    double grade;
    stream.read(reinterpret_cast<char*>(&grade), sizeof(double));
    next.setGrade(grade);
}

Student* readFile(const char* fileName, size_t& currentNumberOfRecords) {
    if (fileName == nullptr) {
        return nullptr;
    }

    makeSureFileExists(fileName);
    std::fstream stream(fileName, std::ios::in | std::ios::binary);

    if (!stream.is_open()) {
        return nullptr;
    }

    size_t sizeOfStream = getFileSize(stream);
    
    if (sizeOfStream == 0) {
        return nullptr;
    }

    stream.read(reinterpret_cast<char*>(&currentNumberOfRecords), sizeof(size_t));

    Student* result = new Student[currentNumberOfRecords];

    for (size_t i = 0; i < currentNumberOfRecords; i++)
    {
        readNextStudent(stream, result[i]);
    }

    stream.close();
    return result;
}

int main()
{
    /*Student alan("Alan", "Georgiev","12345", 5.5);
    Student ivo("Ivo", "Ivanov","12445", 4.5);
    Student ivan("Ivan", "Ivanov","12345", 3.5);
    Student hristo("Hristo", "Hristov","12245", 3.5);
    Student georgi("Georgi", "Georgiev","12145", 6);
    Student stefan("Stefan", "Hristov","12315", 5.5);

    writeOnFile(FILE_STUDENTS, alan);
    writeOnFile(FILE_STUDENTS, ivo);
    writeOnFile(FILE_STUDENTS, ivan);
    writeOnFile(FILE_STUDENTS, hristo);
    writeOnFile(FILE_STUDENTS, georgi);
    writeOnFile(FILE_STUDENTS, stefan);*/

    size_t size;
    Student* students = readFile(FILE_STUDENTS, size);

    if (students == nullptr) {
        return 0;
    }

    for (size_t i = 0; i < size; i++)
    {
        std::cout << students[i].getFirstName() << " " << students[i].getLastName() << " "
            << students[i].getFacultyNumber() << " " << students[i].getGrade() << std::endl;
    }

    delete[] students;
}