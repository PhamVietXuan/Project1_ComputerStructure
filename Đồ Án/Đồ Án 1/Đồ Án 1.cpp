#include <iostream>
#include <string.h>
#include <stdio.h>
#include "conio.h"
#include "Qfloat.h"
using namespace std;

int main()
{
    Qfloat a;
    bool* n;
    a.ScanQfloat();
    n = a.DecToBin();

    for (int i = 0; i < 128; i++) {

        if (n[i] == true) { cout << 1; }
        else { cout << 0; }

        if (i == 0) { cout << "  "; }
        if (i == 15) { cout << " "; }
        if (i % 4 == 3) { cout << " "; }
    }
        cout << endl;

        return 0;

}
