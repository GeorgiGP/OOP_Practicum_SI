#include <iostream>
#include <fstream>
using namespace std;

const char PLACEHOLDER_FILE[] = "Placeholders.txt";
const char VALUES_FILE[] = "Values.txt";
const char RESULT_FILE[] = "Result.txt";

const int MAX_LINES = 10;
const int MAX_KEY_LENGTH = 40;
const int MAX_VALUE_LENGTH = 60;
const int MAX_BUFFER_LENGTH = 256;

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

char* GetValuesFromFile(char keys[][MAX_KEY_LENGTH], char values[][MAX_VALUE_LENGTH], int& keyCnt) {
	ifstream ifStream(VALUES_FILE);

	if (!ifStream.is_open())
	{
		return nullptr;
	}

	char buffer[MAX_BUFFER_LENGTH];

	while (ifStream.getline(buffer, MAX_BUFFER_LENGTH) && keyCnt < MAX_LINES)
	{
		char* token = StrTok(buffer, " ");

		if (!token)
		{
			continue;
		}

		strncpy_s(keys[keyCnt], token, MAX_KEY_LENGTH);
		keys[keyCnt][MAX_KEY_LENGTH - 1] = '\0';

		token = StrTok(nullptr, "\n");
		strncpy_s(values[keyCnt], token, MAX_VALUE_LENGTH);
		values[keyCnt++][MAX_VALUE_LENGTH - 1] = '\0';
	}

	ifStream.close();
}

void WriteResultFile() {
	ifstream ifStream(PLACEHOLDER_FILE);
	ofstream ofStream(RESULT_FILE);

	if (!ifStream.is_open() || !ofStream.is_open())
	{
		return;
	}

	char line[MAX_BUFFER_LENGTH];
	char keys[MAX_LINES][MAX_KEY_LENGTH];
	char values[MAX_LINES][MAX_VALUE_LENGTH];

	int keyCnt = 0;

	GetValuesFromFile(keys, values, keyCnt);

	while (ifStream.getline(line, MAX_BUFFER_LENGTH))
	{
		char result[MAX_BUFFER_LENGTH] = "";
		char temp[MAX_BUFFER_LENGTH];

		int resultIndex = 0;
		int i = 0;

		while (line[i] != '\0')
		{
			if (line[i] == '{')
			{
				int startIndex = ++i;

				while (line[i] != '}' && line[i] != '\0')
				{
					i++;
				}

				if (line[i] == '}')
				{
					int length = i - startIndex;

					strncpy_s(temp, line + startIndex, length);
					temp[length] = '\0';

					bool isKeyFound = false;

					for (int j = 0; j < keyCnt; j++)
					{
						if (strcmp(temp, keys[j]) == 0)
						{
							strncpy_s(temp, values[j], MAX_VALUE_LENGTH);

							for (int k = 0; temp[k] != '\0'; k++)
							{
								result[resultIndex++] = temp[k];
							}

							isKeyFound = true;
							break;
						}
					}

					if (!isKeyFound)
					{
						result[resultIndex++] = '{';

						for (int k = startIndex; k < i; k++)
						{
							result[resultIndex++] = line[k];
						}
						result[resultIndex++] = '}';
					}
				}
			}
			else
			{
				result[resultIndex++] = line[i];
			}

			i++;
		}

		result[resultIndex] = '\0';

		ofStream << result << endl;
	}

	ifStream.close();
	ofStream.close();
}

int main() {
	WriteResultFile();
}