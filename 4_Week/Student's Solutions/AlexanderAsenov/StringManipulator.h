class StringManipulator {
private:
    size_t buffer;
    size_t strLength;
    char* str;
    bool errorState;

    size_t getBuffer() const;
    void setBuffer(size_t buffer);


    void copy(const StringManipulator& stringManipulator);
    void remove();
public:
    StringManipulator();
    StringManipulator(const char* str);
    StringManipulator(const char* str, size_t repeat);

    StringManipulator(const StringManipulator& stringManipulator);

    StringManipulator& operator=(const StringManipulator& stringManipulator);

    ~StringManipulator();

    const char* getStr() const;
    StringManipulator& setStr(const char* str);

    bool getErrorState() const;
    StringManipulator& clearErrorState();

    size_t getStrLength() const;

    const StringManipulator& printStr() const;

    const StringManipulator& writeInFile(const char* fileName) const;

    StringManipulator& readFromFile(const char* fileName);

    StringManipulator& concat(const StringManipulator& stringManipulator);

    StringManipulator& changeSymbol(char find, char replace);
    
    StringManipulator& changeSymbol(char find, char replace, size_t count);

    StringManipulator& insert(const char* str, size_t pos);

    StringManipulator& insert(const char* str);

    StringManipulator& removeAt(size_t pos, size_t length);

    StringManipulator upperCase();
    
    StringManipulator lowerCase();
};