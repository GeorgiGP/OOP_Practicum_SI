#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class DataBase {
    int data = -1;
public:
    int getData() const {
        return data;
    }

    void setData(int data) {
        if (data < 0)
        {
            throw std::invalid_argument("Must be positive!");
        }
        this->data = data;
    }
};

class Singleton {
    static DataBase db;
public:
    Singleton() = default;
    Singleton(const Singleton& other) = delete;

    static DataBase& getInstance() {
        return db;
    }
};


class Person {
    int data = -1;
public:
    int getData() const {
        return data;
    }

    void setData(int data) {
        if (data < 0)
        {
            throw std::invalid_argument("Must be positive!");
        }
        this->data = data;
    }

    virtual void f() = 0;
};

class Teacher : public Person {
    int data = -1;
public:
    int getData() const {
        return data;
    }

    void setData(int data) {
        if (data < 0)
        {
            throw std::invalid_argument("Must be positive!");
        }
        this->data = data;
    }

    void f() override {
        std::cout << "I am Teacher!\n";
    }
};

class Student : public Person {
    int data = -1;
public:
    int getData() const {
        return data;
    }

    void setData(int data) {
        if (data < 0)
        {
            throw std::invalid_argument("Must be positive!");
        }
        this->data = data;
    }

    void f() override {
        std::cout << "I am Student!\n";
    }
};

class Factory {
    static Person* create(const char* str) {
        if (!strcmp(str, "Teacher")) {
            return new Teacher();
        }
        if (!strcmp(str, "Student")) {
            return new Student();
        }
        throw std::invalid_argument("Can't recognize class!");
    }
};


class CustomException : public runtime_error {
public:
    CustomException(const char* context) : runtime_error(context) {

    }

    CustomException(const std::string& context) : runtime_error(context) {

    }
};


class FactoryMethod {
    ifstream ifs;
public:
    FactoryMethod(const char* fileName) : ifs(fileName) {
        if (!ifs.is_open())
        {
            throw CustomException(string("Can't open file!") + fileName);
        }
    }
   
    Person* create() {
        if (ifs.eof()) {
            throw invalid_argument("EOF!");
        }
        char b;
        ifs.get(b);
        if (b == '1') {
            return new Teacher();
        }
        if (b == '0') {
            return new Student();
        }
        return nullptr;
    }
};

enum class Color {
    Yellow,
    White
};

class Lights {
    Color _color;

public:
    Lights(Color color) : _color(color) {}

    const char* color() const {
        switch (_color)
        {
        case Color::Yellow:
            return "Yellow";
        case Color::White:
            return "White";
        default:
            throw std::invalid_argument("Invalid Color");
        }
        return nullptr;
    }
};

class StWheel {
    bool isLeft;
public:

    StWheel(bool isLeft) : isLeft(isLeft) {}
    
    const char* side() const {
        return isLeft ? "left" : "rigth";
    }
};
class Car {
    Lights lights;
    StWheel wheel;

public:
    Car(const StWheel& wheel, const Lights& lights) : wheel(wheel), lights(lights) {}
    string toString() const {
        return string("Car has: Lights with color -> ") + lights.color() + " and streering wheel on " + wheel.side() + " side!\n";
    }
};

class BGFactory;
class JapanFactory;

class CarFactory {
public:
    virtual Car* create() const = 0;
};

class BGFactory : public CarFactory {
public:
    Car* create() const override {
        return new Car({ true }, { Color::White });
    }
};

class JapanFactory : public CarFactory {
public:
    Car* create() const override {
        return new Car({ false }, { Color::Yellow });
    }
};

static CarFactory* createFactory(const char* str) {
    if (!strcmp(str, "BG"))
    {
        return new BGFactory();
    }
    if (!strcmp(str, "Japan"))
    {
        return new JapanFactory();
    }
    throw invalid_argument("Invalid Country!");
}

int main()
{
    Car* car1 = createFactory("BG")->create();
    Car* car2 = createFactory("Japan")->create();
    std::cout << car1->toString();
    std::cout << car2->toString(); 
    delete car1;
    delete car2;
} 
