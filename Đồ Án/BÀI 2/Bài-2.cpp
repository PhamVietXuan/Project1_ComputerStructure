#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include "conio.h"
#include "Qfloat.h"
#include <fstream>
using namespace std;

int main() 
{
	ifstream fin;
	fin.open("input.txt");

	ofstream fout;
	fout.open("output.txt");

	int radix1, radix2;
	string bigNum;

	while (!fin.eof())
	{
		fin >> radix1 >> radix2 >> bigNum;
		
		if (radix1 == 10 && radix2 == 2)
		{
			Qfloat a;
			a.ScanQfloat(10, bigNum);
			fout<<a.PrintQfloat(2)<<endl;
		
		}
		else
			if (radix1 == 2 && radix2 == 10)
			{
				Qfloat a;
				a.ScanQfloat(2, bigNum);
				fout << a.PrintQfloat(10) << endl;
			}
	}
}