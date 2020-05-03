#include <iostream>
#include <string.h>
#include <stdio.h>
#include "conio.h"
//#include "Qfloat.h"
#include "floatingPoint.h"
using namespace std;

int main()
{
	int bin[4] = { 1073930772, 2061584302, 343597383, 920577761};
	
	floatingPoint a(bin);
	a.printQfloat();
	
}