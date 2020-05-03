#pragma once
#include <iostream>
#include <string>

using namespace std;

class floatingPoint
{
private:
	int data[4] = {0};
	const int INTLENGT = 32;
public:
	floatingPoint(int bin[4])
	{
		data[0] = bin[0];
		data[1] = bin[1];
		data[2] = bin[2];
		data[3] = bin[3];
	}
	~floatingPoint()
	{
		delete[] this;
	}
	void printQfloat();
};
string decToBin(string dec);
string nhanChuoiVoi2(string bigNum);
int stringToInt(string numStr);
string intToString(int num);
string div2(string bigNum);
int mod2(string bigNum);
int binToDec(string bit);
string chia2(string bigNum);
string pow( int n);//return 2^n
string addFloat(string a, string b);
int setBit1(int x, int i);
int getBit(int x, int i);
string binToQfloat(int bin[4]);

