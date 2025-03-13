#include <iostream>
#include <fstream>
using namespace std;

const int USER_FIELD_SIZE = 128;
const int SYSTEM_USERS_SIZE = 100;
const int BUFFER_SIZE = 256;

struct User {
	char username[USER_FIELD_SIZE];
	char email[USER_FIELD_SIZE];
	char password[USER_FIELD_SIZE];
};

struct System {
	User users[SYSTEM_USERS_SIZE];
	int size = 0;
};

char* FindCharInString(const char* str, char ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
		{
			return (char*)str;
		}
		str++;
	}

	if (ch == '\0')
	{
		return (char*)str;
	}

	return nullptr;
}
char* StrTok(char* str, const char* delimiters)
{
	//This function splits a given string into parts (tokens) separated by a delimeter.
	static char* nextToken = nullptr;

	if (str != nullptr)
	{
		nextToken = str;
	}

	if (nextToken == nullptr)
	{
		return nullptr;
	}

	char* tokenStart = nextToken;
	while (*tokenStart && FindCharInString(delimiters, *tokenStart))
	{
		++tokenStart;
	}

	if (*tokenStart == '\0')
	{
		nextToken = nullptr;
		return nullptr;
	}

	char* tokenEnd = tokenStart;
	while (*tokenEnd && !FindCharInString(delimiters, *tokenEnd))
	{
		++tokenEnd;
	}

	if (*tokenEnd != '\0')
	{
		*tokenEnd = '\0';
		nextToken = tokenEnd + 1;
	}
	else
	{
		nextToken = nullptr;
	}

	return tokenStart;
}


void SaveUserToFile(const char* FILENAME, const User& user) {
	ofstream ofStream(FILENAME, 4);

	if (!ofStream.is_open())
	{
		return;
	}

	ofStream << user.username << '|' << user.email << '|' << user.password << '\n';

	ofStream.close();
}

User* ReadUserFromFile(const char* FILENAME) {
	ifstream ifStream(FILENAME);

	if (!ifStream.is_open())
	{
		return nullptr;
	}

	char buffer[BUFFER_SIZE];

	ifStream.getline(buffer, BUFFER_SIZE);

	if (!buffer)
	{
		return nullptr;
	}

	char* usernameToken = StrTok(buffer, "|");
	char* emailToken = StrTok(buffer, "|");
	char* passwordToken = StrTok(buffer, "\n");

	User* user = new User(); //Make sure to delete later
	strncpy_s(user->username, usernameToken, USER_FIELD_SIZE);
	strncpy_s(user->email, emailToken, USER_FIELD_SIZE);
	strncpy_s(user->password, passwordToken, USER_FIELD_SIZE);

	ifStream.close();

	return user;
}

void SaveSystemToFile(const char* FILENAME, const System& system) {
	ofstream ofStream(FILENAME);

	if (!ofStream.is_open())
	{
		return;
	}

	ofStream << system.size << '\n';

	for (int i = 0; i < system.size; i++)
	{
		ofStream << system.users[i].username << '|' << system.users[i].email << '|' << system.users[i].password << '\n';
	}

	ofStream.close();
}

System* ReadSystemFromFile(const char* FILENAME) {
	ifstream ifStream(FILENAME);

	if (!ifStream.is_open())
	{
		return nullptr;
	}

	System* system = new System();

	ifStream >> system->size;
	ifStream.ignore();

	char buffer[BUFFER_SIZE];

	for (int i = 0; i < system->size; i++)
	{
		ifStream.getline(buffer, BUFFER_SIZE);

		char* usernameToken = StrTok(buffer, "|");
		char* emailToken = StrTok(buffer, "|");
		char* passwordToken = StrTok(buffer, "\n");

		strncpy_s(system->users[i].username, usernameToken, USER_FIELD_SIZE);
		strncpy_s(system->users[i].email, emailToken, USER_FIELD_SIZE);
		strncpy_s(system->users[i].password, passwordToken, USER_FIELD_SIZE);
	}

	ifStream.close();

	return system;
}

void Register(const char* FILENAME, System& system) {
	if (system.size >= SYSTEM_USERS_SIZE)
	{
		cout << "Maximum amount of users reached!" << endl;
		return;
	}

	char username[USER_FIELD_SIZE];
	char email[USER_FIELD_SIZE];
	char password[USER_FIELD_SIZE];

	cout << "Enter name:" << endl;
	cin.getline(username, USER_FIELD_SIZE);

	cout << "Enter email:" << endl;
	cin.getline(email, USER_FIELD_SIZE);

	cout << "Enter password:" << endl;
	cin.getline(password, USER_FIELD_SIZE);

	strcpy_s(system.users[system.size].username, username);
	strcpy_s(system.users[system.size].email, email);
	strcpy_s(system.users[system.size].password, password);

	system.size++;

	SaveSystemToFile(FILENAME, system);

	cout << "Registration successful" << endl;
}

void GetEmailsAndPasswords(ifstream& ifStream, char(&emails)[SYSTEM_USERS_SIZE][USER_FIELD_SIZE], char(&passwords)[SYSTEM_USERS_SIZE][USER_FIELD_SIZE], int size) {
	char buffer[BUFFER_SIZE];

	for (int i = 0; i < size; i++)
	{
		ifStream.getline(buffer, BUFFER_SIZE);

		char* usernameToken = StrTok(buffer, "|");
		char* emailToken = StrTok(nullptr, "|");
		char* passwordToken = StrTok(nullptr, "\n");

		strcpy_s(emails[i], emailToken);
		strcpy_s(passwords[i], passwordToken);
	}
}

bool DoesUserExist(const char* FILENAME, const char* email, const char* password) {
	if (!email || !password)
	{
		return false;
	}

	ifstream ifStream(FILENAME);

	if (!ifStream.is_open())
	{
		return false;
	}

	int size;
	ifStream >> size;
	ifStream.ignore();

	char emails[SYSTEM_USERS_SIZE][USER_FIELD_SIZE];
	char passwords[SYSTEM_USERS_SIZE][USER_FIELD_SIZE];

	GetEmailsAndPasswords(ifStream, emails, passwords, size);

	ifStream.close();

	for (int i = 0; i < size; i++)
	{
		if (strcmp(emails[i], email) == 0 && strcmp(passwords[i], password) == 0)
		{
			return true;
		}
	}

	return false;
}

void Login(const char* FILENAME, System& system) {
	char email[USER_FIELD_SIZE];
	char password[USER_FIELD_SIZE];

	cout << "Enter email:" << endl;
	cin.getline(email, USER_FIELD_SIZE);

	cout << "Enter password:" << endl;
	cin.getline(password, USER_FIELD_SIZE);

	bool isUserValid = DoesUserExist(FILENAME, email, password);

	if (isUserValid)
	{
		cout << "Login successful" << endl;
	}
	else
	{
		cout << "User does not exist" << endl;
	}
}

int main() {
	const char SYSTEM_FILE[] = "System.txt";

	System* system = ReadSystemFromFile(SYSTEM_FILE);

	cout << "Enter command (register, login or quit):" << endl;

	char command[BUFFER_SIZE];
	cin.getline(command, BUFFER_SIZE);

	while (true)
	{
		if (strcmp(command, "register") == 0)
		{
			Register(SYSTEM_FILE, *system);
		}
		else if (strcmp(command, "login") == 0)
		{
			Login(SYSTEM_FILE, *system);
		}
		else if (strcmp(command, "quit") == 0)
		{
			break;
		}

		cout << "Enter command (register, login or quit):" << endl;
		cin.getline(command, BUFFER_SIZE);
	}

	delete system;
}