const int MAX_PAIR_COUNT = 25;
struct Pair
{
    int num1;
    int num2;
};
struct Relation
{
    Pair pairs[MAX_PAIR_COUNT];
    int size;
};
void writePairToFile(Pair pair, ofstream& ofs)
{
    if (!ofs.is_open())
    {
        cerr << "Error opening file."; 
        return;
    }

    ofs << pair.num1 << " " << pair.num2;
}
void writeRelationToFile(Relation rel, ofstream& ofs)
{
    if (!ofs.is_open())
    {
        cerr << "Error opening file.";
        return;
    }

    for (int i = 0; i < rel.size; i++)
    {
        writePairToFile(rel.pairs[i], ofs);
        ofs << "\n";
    }
}
Pair readPairFromFile(int line, ifstream& ifs)
{
    int num1 = 0, num2 = 0;

    if (!ifs.is_open())
    {
        cerr << "Error opening file.";
        return { num1, num2 };
    }

    for (int i = 0; i < line; i++)
    {
        // 'skip' the lines, until we get to the one we need
        ifs >> num1 >> num2;
    }

    cout << "Read pair at line " << line << ": " << num1 << ", " << num2 << "\n";
    return { num1, num2 };
}
Relation readRelationFromFile(ifstream& ifs)
{
    Relation rel = { };
    if (!ifs.is_open())
    {
        cerr << "Error opening file.";
        return rel;
    }

    for (int i = 0; i < rel.size; i++)
    {
        rel.pairs[i] = readPairFromFile(i, ifs);
        rel.size++;
    }

    return rel;
}
void addPairToRelation(Pair pair, Relation rel)
{
    if (rel.size == 25)
    {
        cout << "Max pair size reached. Can not add pair.";
        return;
    }

    rel.pairs[rel.size++] = pair;
}