#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int min = 0;
    int max = 5;

    cout << "Generating a number from ";
    cout << min;
    cout << " to ";
    cout << max;
    cout << " (inclusive)...";
    cout << endl;

    srand(time(0));
    int rng = rand();

    cout << "RNG: ";
    cout << rng;
    cout << endl;

    int res = rng % (max - min + 1) + min;

    cout << res;
    cout << endl;

    return 0;
}