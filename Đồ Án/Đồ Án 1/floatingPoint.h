#pragma once
#include <iostream>
#include <string>

using namespace std;

class floatingPoint
{
private:
	int data[4] = { 0, 0, 0, 0 };

};

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
void binToQfloat(int bin[4]);
