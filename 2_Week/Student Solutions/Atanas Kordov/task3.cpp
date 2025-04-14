#include <iostream>
#include <fstream>

using namespace std;

struct Color
{
    int red_val; // read_num / 65536
    int green_val; // (read_num / 256) % 256
    int blue_val; // read_num % 256
};
// stream needs to be in binary mode + result dynamically allocated
void readColorCode(ifstream& ifs, Color* result)
{
    Color curColor = { -1, -1, -1 };

    if (!ifs.is_open())
    {
        cerr << "Cannot open file.\n";
        return;
    }

    char str[8];
    int currNum = 0;
    int arrIndex = 0;

    while (ifs.read(str, 8))
    {
        // lazy to write myself, pls allow :>
        currNum = atoi(str);

        // read/save to struct
        curColor.red_val = currNum / 65536;
        curColor.green_val = (currNum / 256) % 256;
        curColor.blue_val = currNum % 256;

        // save to arr
        result[arrIndex++] = curColor;

        // reset
        curColor = { -1, -1, -1 };

        // skip the '|'
        ifs.seekg(1, ios::cur);
    }

    ifs.seekg(ios::beg);
}
void saveRedToFile(ofstream& ofs, Color* colors, int colorsSize)
{
    if (!ofs.is_open())
    {
        cerr << "Cannot open file.\n";
        return;
    }

    for (int i = 0; i < colorsSize; i++)
    {
        if (colors[i].red_val >= 250)
        {
            if (ofs.tellp() != 0)
            {
                ofs << '|';
            }
            int num = colors[i].red_val * 65536 + colors[i].green_val * 256 + colors[i].blue_val;
            ofs << num;
        }
    }
}