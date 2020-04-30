#include <iostream>
#include "floatingPoint.h"

using namespace std;
void main()
{
	int n;
	cout << "Enter n: ";
	cin >> n;
	for(int i=-n; i<n; i++)
		cout <<"2^"<<n<<" = "<< pow(i) << endl;
}