#include <iostream>
#include "floatingPoint.h"

using namespace std;
void main()
{
	int a = 2147418112;
	int bin[4] = {0,0,5663,0};
	a = setBit1(a, 16);
	a = setBit1(a, 18);
	bin[0] = a;
	binToQfloat(bin);
}