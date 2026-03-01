#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "USAGE: lmap_compile [CSVFILE.csv] [TILEMAP.png]\n";
        return -1;
    }
    return 0;
}