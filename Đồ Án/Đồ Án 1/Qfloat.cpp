#include "Qfloat.h"

void Qfloat::ScanQfloat() {
	int radix;
	string scan = "";

	cout << "Nhap he co so (2 hoac 10): ";
	cin >> radix;
	if ((radix != 2) && (radix != 10)) {
		cout << "He co so ban nhap khong thoa!\n";
		return;
	}

	cout << "Nhap chuoi so: ";
	cin >> scan;

	if (radix == 2) {

		if (scan.length() < 17) {
			cout << "Chuoi so ban nhap qua ngan!\n";
			return;
		}

		for (int i = 0; (i < 128) && (i < scan.length()); i++) {
			
			if (scan[i] == '1') {
				data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
			}
			else {
				if (scan[i] == '0') {}
				else {
					cout << "Chuoi so ban nhap sai ky tu!\n";
					return;
				}
			}

		}
	}

	else {
		
	}

	return;
}


bool* Qfloat::DecToBin() {
	bool* result = new bool[128];

	for (int i = 0; i < 128; i++) {
		result[i] = (data[i / INTLENGT] >> (INTLENGT - 1 - i)) & 1;
	}

	return result;
}


Qfloat::~Qfloat() {

}