//TO BE DONE!
#include <iostream>

class FileSystemEntity {
private:
    char* name;
protected:
    FileSystemEntity* parent;
private:
    void free() {
        delete name;
        name = nullptr;
    }

    void copyFrom(const FileSystemEntity& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }
public:
    FileSystemEntity(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name); 
    }

    FileSystemEntity(const FileSystemEntity& other) {
        copyFrom(other);
    }

    FileSystemEntity& operator=(const FileSystemEntity& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;

    }

    virtual ~FileSystemEntity() {
        free();
    }
};

class Directory : public FileSystemEntity {
private:
    void copyFrom(const Directory& other) {

    }

    void free() {
        for (size_t i = 0; i < count; ++i) {
            delete files[i];
        }
        delete[] files;
    }

public:
    Directory(const char* name) : FileSystemEntity(name) {
        parent = this;
    }

    Directory(Directory* parentDir, const char* name) : FileSystemEntity(name) {
        parent = parentDir;
    }

    Directory(const Directory& other) {
        copyFrom(other);
    }

    Directory& operator=(const Directory& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~Directory() {
        free();
    }
};

class SingleFile : public FileSystemEntity{
private:
    int size;

public:
    SingleFile(Directory* parentDir, const char* name, int size) : FileSystemEntity(name) {
        parent = parentDir;
        this->size = size;
    }

    SingleFile(const char* name, int size) : FileSystemEntity(name) {
        this->size = size;
        parent = this;
    }
};

class ContainerFiles {
    FileSystemEntity** files;
    int count = 0;
    int capacity = 8;
};
int main()
{
    std::cout << "Hello World!\n";
}
