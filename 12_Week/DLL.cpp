#include <iostream>

template <class T>
class DLL { 
    struct Node {
        T element;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& el) {
            element = el;
        }

        Node(T&& el) {
            element = std::move(el);
        }
    };

    Node* begin = nullptr;
    Node* end = nullptr;

    int _size = 0;

public:
    const T& front() const {
        return begin->element;
    }

    const T& back() const {
        return end->element;
    }

    bool empty() const {
        return begin == nullptr;
    }

    int size() const {
        return _size;
    }

    const T& operator[](int pos) const{
        Node* res = begin;
        for (int i = 0; i < pos; ++i) {
            res = res->next;
        }
        return res->element;
    }

    T& operator[](int pos) {
        Node* res = begin;
        for (int i = 0; i < pos; ++i) {
            res = res->next;
        }
        return res->element;
    }

    void clear() {
        Node* cur = begin;
        Node* next;
        while (cur != end) {
            next = cur->next;
            delete cur;
            cur = next;
        }
        begin = end = nullptr;
        _size = 0;
    }

    ~DLL() {
        clear();
    }

    void push_back(const T& el) {
        Node* node = new Node(el);
        node->prev = end;
        if (end == nullptr) {
            begin = end = node;
        }
        else {
            end->next = node;
            end = node;
        }
        ++_size;
    }

    void push_back(T&& el) {
        Node* node = new Node(std::move(el));
        node->prev = end;
        if (end == nullptr) {
            begin = end = node;
        }
        else {
            end->next = node;
            end = node;
        }
        ++_size;
    }

    void pop_back() {
        if (end == nullptr) {
            return;
        }
        if (_size == 1) {
            delete begin;
            begin = end = nullptr;
            _size = 0;
        }
        else {
            Node* newTail = end->prev;
            end->prev->next = nullptr;
            delete end;
            end = newTail;
            --_size;
        }
        
    }

    void push_front(const T& el) {
        Node* node = new Node(el);
        node->next = begin;
        if (begin == nullptr) {
            begin = end = node;
        }
        else {
            begin->prev = node;
            begin = node;
        }
        ++_size;
    }

    void push_front(T&& el) {
        Node* node = new Node(std::move(el));
        node->next = begin;
        if (begin == nullptr) {
            begin = end = node;
        }
        else {
            begin->prev = node;
            begin = node;
        }
        ++_size;
    }

    void pop_front() {
        if (begin == nullptr) {
            return;
        }
        if (_size == 1) {
            delete begin;
            begin = end = nullptr;
            _size = 0;
        }
        else {
            Node* newHead = begin->next;
            begin->next->prev = nullptr;
            delete begin;
            begin = newHead;
            --_size;
        }
    }
};

int main()
{
    DLL<int> dll;
    for (int i = 0; i < 10; ++i) {
        dll.push_back(i + 5);
    }

    for (int i = 0; i < dll.size(); ++i) {
        std::cout << dll[i] << std::endl;
    }

    std::cout << dll.back() << std::endl;
    std::cout << dll.front() << std::endl;
    for (int i = 0; i < 10; ++i) {
        dll[i] = 6;
    }

    for (int i = 0; i < dll.size(); ++i) {
        std::cout << dll[i] << std::endl;
    }
    std::cout << "SIZE:" << dll.size() << std::endl;
    int size = dll.size();
    for (int i = 0; i < 10; ++i) {
        dll.pop_back();
    } 
    std::cout << "SIZE:" << dll.size() << std::endl;
    for (int i = 0; i < dll.size(); ++i) {
        std::cout << dll[i] << std::endl;
    }
}
