#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include "conio.h"
#include "Qfloat.h"

using namespace std;

int main() {
	Qfloat a;
	a.ScanQfloat(10, 1, 5, "89", "125673");
	cout<<a.PrintQfloat(10);
}