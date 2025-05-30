#include <iostream>

template <class T>
class Unique_ptr {
private:
    T* ptr;

    void moveFrom(Unique_ptr&& other) {
        this->ptr = other.ptr;
        other.ptr = nullptr;
    }

    void free() {
        delete ptr;
        ptr= nullptr;
    }
public:
    Unique_ptr(T* ptr) : ptr(ptr) {
    }

    Unique_ptr(const Unique_ptr& other) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;

    Unique_ptr(Unique_ptr&& other) {
        moveFrom(std::move(other));
    }

    Unique_ptr& operator=(Unique_ptr&& other) {
        if (this != &other)
        {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }

    T* operator->() {
        return ptr;
    }

    const T* operator->() const {
        return ptr;
    }

    const T& operator*() const {
        return *ptr;
    }

    T& operator*() {
        return *ptr;
    }

    ~Unique_ptr() {
        free();
    }
};

int main() {
    Unique_ptr<int> myPtrInt(new int(5));
    std::cout << &myPtrInt << " the ptr " << std::endl;
    std::cout << *myPtrInt << " the value " << std::endl;
}