#include <iostream>
#include <string.h>
#include <stdio.h>
#include "conio.h"
#include"bigNum.h"
#include "floatingPoint.h"
using namespace std;

int main()
{
	int bin[4] = { 3221414420, 2061584302, 343597383, 920577761};
	
	floatingPoint a(bin);
	a.ScanQfloat();
	a.printQfloat();
	
}