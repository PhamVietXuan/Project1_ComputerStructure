#include <iostream>
#include <string.h>
#include <stdio.h>
#include "conio.h"
using namespace std;

class Qfloat {
private:
	int data[4] = { 0 };
	const int INTLENGT = 32;
	int Exception = 0;
public:
	void ScanQfloat(int, string);
	void ScanQfloat(int, int, int, string);
	void ScanQfloat(int, int, int, string, string);
	string PrintQfloat(int);
	string BinToDec();
	void DecToBin(string);
public:
	Qfloat();
	~Qfloat();
};