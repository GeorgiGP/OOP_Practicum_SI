#include <iostream>

class Base {
protected:
    char c;
    int* x = nullptr;
    char ch;
    //void* vTable //16

    void copyFrom(const Base& other) {
        this->x = new int(*(other.x));
    }

    void free() noexcept {
        delete x;
    }
public:
    Base() {
        x = new int(5);
    }

    Base(int x) {
        this->x = new int(x);
    }

    Base& operator=(const Base& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    Base(const Base& other) {
        copyFrom(other);
    }

    virtual void fun() = 0;

    virtual Base* clone() const = 0;

    virtual ~Base() noexcept {
        free();
    }
};

class Derived : public virtual Base { //16
    int* y; //4
    //4 vTable
    //4 virtual Base
    void copyFrom(const Derived& other) {
        this->y = new int(*(other.x));
    }

    void free() noexcept {
        delete y;
    }
public:
    void fun() override {
        std::cout << "I am Deriver1::fun()\n";
    }

    Derived() {
        this->y = new int(2);
    }

    Derived& operator=(const Derived& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    Derived(const Derived& other) {
        copyFrom(other);
    }

    ~Derived() noexcept {
        free();
    }

    Base* clone() const override {
        return new Derived(*this);
    }
};

class Derived2 : public virtual Base {
    int* z;

    void copyFrom(const Derived2& other) {
        this->z = new int(*(other.z));
    }

    void free() noexcept {
        delete z;
    }
public:
    void fun() override {
        std::cout << "I am Deriver2::fun()\n";
    }

    Derived2() {
        this->z = new int();
    }

    Derived2& operator=(const Derived2& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    Derived2(const Derived2& other) {
        copyFrom(other);
    }

    ~Derived2() noexcept {
        free();
    }

    Base* clone() const override {
        return new Derived2(*this);
    }
};

class Diamond : public Derived, public Derived2 { 
public:
    Base* clone() const override {
        return new Diamond(*this);
    }

    void fun() override {
        std::cout << "I am Diamond::fun()\n";
    }
};

class AfterDiamond : public Diamond { 
public:
    int a;
    Base* clone() const override {
        return new AfterDiamond(*this);
    }

    void fun() override {
        std::cout << "I am Diamond::fun()\n";
    }
};

#include <cstdlib>
#include <crtdbg.h>
 
//Base* createOtherBase(Base* other) {
//    Derived* d = dynamic_cast<Derived*>(other);
//    if (d != nullptr)
//    {
//        return new Derived(*d);
//    }
//    Derived2* d2 = dynamic_cast<Derived2*>(other);
//    if (d != nullptr)
//    {
//        return new Derived2(*d2);
//    }
//    //...
//}
//
//class AbstractFactory {
//    virtual CarLight* create() const = 0;
//    virtual CarEngine* create() const = 0;
//
//};
//
//class FactoryJapaniseCar : public AbstractFactory{
//    CarLight* create() const override {
//
//    }
//
//    CarEngine* create() const override {
//
//    }
//};
//
//class FactoryDeutschCar : public AbstractFactory {
//    CarLight* create() const override {
//
//    }
//
//    CarEngine* create() const override {
//        return new DeutschCarEngine();
//    }
//};
////Creational Design Patterns
////1.Factory Design Pattern
//Base* factory(bool b) {
//    switch (b)
//    {
//    case true: return new FactoryJapaniseCar();
//    case false: return new FactoryDeutschCar();
//    }
//}

//2. Prototype -> clone()

//3.Abstract Factory

//4.Builder -> https://github.com/GeorgiGP/OOP_Practicum_SI/tree/main/4_Week

int main()
{ 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Base* d1 = new Derived();
    Base* d2 = new Derived2();
    Base* d3 = new Diamond();

    Base** container = new Base * [3];
    container[0] = d1;
    container[1] = d2;
    container[2] = d3;

    for (size_t i = 0; i < 3; i++)
    {
        container[i]->fun();
    }

    Base** containerCopy = new Base * [3];
    for (size_t i = 0; i < 3; i++)
    {
        containerCopy[i] = container[i]->clone();
    }

    for (size_t i = 0; i < 3; i++)
    {
        containerCopy[i]->fun();
    }

    delete containerCopy[0];
    delete containerCopy[1];
    delete containerCopy[2];
    delete d1;
    delete container;
    delete containerCopy;
    delete d2; 
    delete d3; 

    std::cout << sizeof(Base) << '\n';
    std::cout << sizeof(Derived) << '\n';
    std::cout << sizeof(Derived2) << '\n';
    std::cout << sizeof(Diamond) << '\n';
    std::cout << sizeof(AfterDiamond) << '\n';
}
