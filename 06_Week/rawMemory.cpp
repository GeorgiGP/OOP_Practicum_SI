
class B {
public:
    int x;

public:
    B(int x) : x(x) {}
};

int main()
{
    void* rawMem = operator new[](10 * sizeof(B));
    B* p = reinterpret_cast<B*>(rawMem);

    for (size_t i = 0; i < 10; i++)
    {
        new(&p[i])B(i * 3);
    }

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << p[i].x;
    }
    delete[] p;
}
