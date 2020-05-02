#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "conio.h"
#include "floatingPoint.h"
using namespace std;

class Qfloat {
private:
	int data[4] = { 0 };
	const int INTLENGT = 32;
public:
	void ScanQfloat();
	bool* DecToBin();
public:
	~Qfloat();
};
