#include <iostream>
#include <fstream>

const int MAX_LENGTH = 128;
const int MAX_USERS = 100;

const char USER_FILE[] = "user.txt";
const char SYSTEM_FILE[] = "system.dat";

struct User {
    char name[MAX_LENGTH];
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
};

struct System {
    bool isLoggedIn = false;
    size_t currentNumberOfUsers = 0;
    User users[MAX_USERS];
};

bool areStringsEqual(const char* str1, const char* str2) {
    while ((*str1 != '\0' || *str2 != '\0') && *str1 == *str2) {
        str1++;
        str2++;
    }

    return *str1 == '\0' && *str2 == '\0';
}

User readUser(const char* userFileName) {
    if (userFileName == nullptr) {
        return {};
    }

    std::ifstream stream(userFileName);

    if (!stream.is_open()) {
        return {};
    }

    User user;

    stream.getline(user.name, MAX_LENGTH);
    stream.getline(user.email, MAX_LENGTH);
    stream.getline(user.password, MAX_LENGTH);

    stream.close();

    return user;
}

void writeUser(const char* userFileName, User& user) {
    if (userFileName == nullptr) {
        return;
    }

    std::ofstream stream(userFileName);

    if (!stream.is_open()) {
        return;
    }

    stream << user.name;
    stream << "\n";

    stream << user.email;
    stream << "\n";

    stream << user.password;
    stream << "\n";

    stream.close();
}

void writeSystem(const char* systemFile, System& system) {
    if (systemFile == nullptr) {
        return;
    }

    std::ofstream stream(systemFile, std::ios::binary);

    if (!stream.is_open()) {
        return;
    }

    stream.write(reinterpret_cast<const char*>(&system), sizeof(System));

    stream.close();
}

void readSystem(const char* systemFile, System& system) {
    if (systemFile == nullptr) {
        return;
    }

    std::ifstream stream(systemFile, std::ios::binary);

    if (!stream.is_open()) {
        return;
    }

    stream.read(reinterpret_cast<char*>(&system), sizeof(System));

    stream.close();
}

int main()
{
    char command[MAX_LENGTH];
    bool isLogedIn = false;
    
    System system;
    readSystem(SYSTEM_FILE, system);

    while (!areStringsEqual(command, "exit")) {
        std::cout << "Enter command" << std::endl;
        std::cin.getline(command, MAX_LENGTH - 1);

        if (areStringsEqual(command, "register")) {
            if (!system.isLoggedIn) {
                if (system.currentNumberOfUsers >= MAX_USERS) {
                    std::cout << "System is full" << std::endl;
                }
                else {
                    std::cout << "Enter name" << std::endl;
                    std::cin.getline(system.users[system.currentNumberOfUsers].name, MAX_LENGTH);
                    
                    std::cout << "Enter email" << std::endl;
                    std::cin.getline(system.users[system.currentNumberOfUsers].email, MAX_LENGTH);
                    
                    std::cout << "Enter password" << std::endl;
                    std::cin.getline(system.users[system.currentNumberOfUsers].password, MAX_LENGTH);

                    system.currentNumberOfUsers++;

                    writeSystem(SYSTEM_FILE, system);

                    system.isLoggedIn = true;
                }
            }
            else {
                std::cout << "Already logged in" << std::endl;
            }
        }
        else if (areStringsEqual(command, "login")) {
            if (!system.isLoggedIn) {
                char userName[MAX_LENGTH];

                std::cout << "Enter username: " << std::endl;
                std::cin.getline(userName, MAX_LENGTH);

                for (size_t i = 0; i < system.currentNumberOfUsers; i++) {
                    if (areStringsEqual(userName, system.users[i].name)) {
                        std::cout << "Enter password" << std::endl;
                        char password[MAX_LENGTH];
                        std::cin.getline(password, MAX_LENGTH);

                        if (areStringsEqual(password, system.users[i].password)) {
                            std::cout << "Logged in" << std::endl;
                            system.isLoggedIn = true;
                        }
                        else {
                            std::cout << "Error" << std::endl;
                        }
                    }
                    else {
                        std::cout << "Error" << std::endl;
                    }
                }
            }
            else {
                std::cout << "Already logged in" << std::endl;
            }
        }
        else if (areStringsEqual(command, "logout")) {
            if (system.isLoggedIn) {
                system.isLoggedIn = false;
                std::cout << "Logged out" << std::endl;
            }
            else {
                std::cout << "Already logged out" << std::endl;
            }
        }
    }
}
