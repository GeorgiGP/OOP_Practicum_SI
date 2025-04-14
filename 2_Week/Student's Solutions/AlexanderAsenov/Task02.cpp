#include <iostream>
#include <fstream>

const char FILENAME[] = "file.dat";
const int MAX_PAIRS = 25;

struct Pair {
    size_t firstElement;
    size_t secondElement;
};

struct Relation {
    int size = 0;
    Pair pairs[MAX_PAIRS];
};

void writeRelationToFile(Relation& relation, const char* const FILENAME) {
    std::ofstream stream(FILENAME, std::ios::binary);

    if (!stream.is_open()) {
        return;
    }

    stream.write(reinterpret_cast<const char*>(&relation), sizeof(Relation));

    stream.close();
}

Relation* readFromFile(const char* const FILENAME) {
    Relation* relation = new Relation();

    std::ifstream stream(FILENAME, std::ios::binary);

    if (!stream.is_open()) {
        return nullptr;
    }

    stream.read(reinterpret_cast<char*>(relation), sizeof(Relation));

    stream.close();

    return relation;
}

void addPairToRelation(Relation& relation, Pair& pair) {
    if (relation.size + 1 > MAX_PAIRS) {
        return;
    }

    relation.pairs[relation.size].firstElement = pair.firstElement;
    relation.pairs[relation.size].secondElement = pair.secondElement;
    relation.size++;
}

void printRelation(Relation& relation) {
    for (size_t i = 0; i < relation.size; i++)
    {
        std::cout << "(" << relation.pairs[i].firstElement << ", "
            << relation.pairs[i].secondElement << ")" << std::endl;
    }
}

int main()
{
    Relation* relation = new Relation();

    char command = 'd';

    while (command != 'e') {
        std::cin >> command;

        switch (command)
        {
        case 'a':
            Pair pair;
            std::cin >> pair.firstElement;
            std::cin >> pair.secondElement;
            addPairToRelation(*relation, pair);
            break;
        case 'r':
            delete relation;
            relation = readFromFile(FILENAME);
            if (relation == nullptr) {
                std::cout << "Error";
                command = 'e';
            }
            break;
        case 'w':
            writeRelationToFile(*relation, FILENAME);
            break;
        case 'p':
            printRelation(*relation);
            break;
        default:
            break;
        }
    }

    delete relation;
}