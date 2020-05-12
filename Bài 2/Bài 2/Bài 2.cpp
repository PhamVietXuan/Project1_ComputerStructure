#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include "conio.h"
#include "Qfloat.h"

using namespace std;

int main() {
	Qfloat a;
	a.ScanQfloat(2, "0100000000000000001000001100000000");
	cout<<a.PrintQfloat(10);
}