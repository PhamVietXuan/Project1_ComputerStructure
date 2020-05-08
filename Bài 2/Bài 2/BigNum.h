#pragma once
#include <iostream>
using namespace std;

string decToBin(string dec);
int binToDec(string bit);

string nhanChuoiVoi2(string bigNum);
string chia2(string bigNum);
string pow(int n); //return 2^n
string div2(string bigNum);
int mod2(string bigNum);

int stringToInt(string numStr);
string intToString(int num);

string addFloat(string a, string b);
string binToQfloat(int bin[4]);

int setBit1(int x, int i);
int getBit(int x, int i);