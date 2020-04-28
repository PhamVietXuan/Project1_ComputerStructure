#include <iostream>
#include "floatingPoint.h"

using namespace std;
void main()

{
	string str;
	cout << "Enter the big number: ";
	cin >> str;
	
	cout << str + " / 2 =" << div2(str);
}