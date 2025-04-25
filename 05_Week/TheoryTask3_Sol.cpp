#include <iostream>
using namespace std;

const unsigned int MAX_MODEL = 21;

enum class State {
	OK,
	INVALID_ARGUMENT,
	NULLPTR,
	INVALID_NAME_FORMAT
};
class Phone {
private:
	unsigned int price;
	char model[MAX_MODEL];


	bool isLetter(char ch) {
		return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
	}

	bool isNumber(char ch) {
		return ('0' <= ch && ch <= '9');
	}

	bool validate(const char* str) {
		while (*str)
		{
			if (!(isLetter(*str) || isNumber(*str)))
			{
				return false;
			}
		}
		return true;
	}
public:
	State setPrice(int price) {
		if (!(100 <= price && price <= 2000))
		{
			return State::INVALID_ARGUMENT;
		}
		this->price = price;
		return State::OK;
	}

	unsigned getPrice() const {
		return price;
	}

	State setModel(const char* model) {
		if (!model)
		{
			return State::NULLPTR;
		}
		int len = strlen(model);
		if (!(15 <= len && len <= 20)) // (15 > len || len > 20)
		{
			return State::INVALID_ARGUMENT;
		}
		if (!validate(model))
		{
			return State::INVALID_NAME_FORMAT;
		}
		strcpy_s(this->model, MAX_MODEL, model); 
	}

	const char* getModel() const {
		return model;
	}
};

int main() {

}
