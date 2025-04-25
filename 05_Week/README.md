# OOП - Практикум 21.03.2024 - Седмица 5 - Подготовка К1

**Задача 1.** Кои от следните член-функции ще се компилират и кои не?

```c++
struct A
{
    int number;
    char arr[5];
    char* ptr;

    int f1() const {
        return number;
    }

    char* f2() {
        return arr;
    }

    const char* f3() {
        return arr;
    }

    char* f4() const {
        return arr;
    }

    const char* f5() const {
        return arr;
    }

    char* f6() const {
        return ptr;
    }

    const char* f7() const {
        return ptr;
    }

    int* f8() const {
        return &number;
    }

    const int* f9() const {
        return &number;
    }
}
```

**Задача 2.** Имате печатане в конструкторите и деструкторите на всички класове. Какво ще се изведе на конзолата след изпълнение на кода?

```c++
struct A {
    A() {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }
};

struct B {
    B() {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }
};

struct X {
    A a;
    B b;

    X(): b(), a() 
    {
        cout << "X()" << endl;
    }

    ~X()
    {
        cout << "~X()" << endl;
    }
};


int main() {
    X arr1[2];
    X arr2 = new X[2];
    return 0;
}
```

**Задача 3.** Напишете getter-и и setter-и на следния клас:

*Ограничения: `price` е в интервал [100, 2000], `model` е с дължина в интервал [15, 20], като съдържа само цифри и букви.*

```c++
class Phone{
  unsigned int price;
  char model[21];
};
```

**Задача 4.** Кои твърденията са верни?
1. Можем да имаме няколко деструктора и няколко конструктора
2. Можем да имаме няколко деструктора, но само един конструктор
3. Можем да имаме няколко конструктора, но само един деструктор
4. Можем да имаме само един конструктор и само един деструктор
5. Задължително трябва да имаме експлицитно разписани конструктор и деструктор в класа
6. Ако си напишем конструктор с параметри, то default конструктор се запазва и можем да го използваме
7. Ако си напишем конструктор с параметри, то за да ползваме default конструктор трябва да го напишем и него
8. Масиви можем да създаваме само ако сме си разписали експлицитно default-ния конструктор или не сме разписвали никакви други конструктори

**Задача 5.** Кои функции ще се компилират и кои не? Има ли семантична грешка в някоя от функциите (да прави нещо, което не трябва, но да се компилира)?

```c++
class A{
    int first;
    mutable int second;

public:
    void f1()
    {
        
    };

    void f2() const 
    {     

    }

    void f3() const
    {
        f1();
    };

    void f4() 
    {
        f1();
    }

    void f5() const
    {
        first++;
    }

    void f6() const
    {
        second++;
    }

    void f7() const
    {
        int temp = first;
        temp++;
    }

    int getFirst() const
    {
        return first;
    }

    int getSecond() const
    {
        return second;
    }
};
```
