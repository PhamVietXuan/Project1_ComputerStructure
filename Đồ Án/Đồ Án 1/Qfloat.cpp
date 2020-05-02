#include "Qfloat.h"


void Qfloat::ScanQfloat() {
	int radix;
	string scan = "";

	cout << "Nhap he co so (2 hoac 10): ";
	cin >> radix;
	if ((radix != 2) && (radix != 10)) {
		cout << "*****************************************\n";
		cout << "Thong bao: He co so ban nhap khong thoa!\n";
		cout << "*****************************************\n";
		return;
	}

	if (radix == 2) {

		cout << "Nhap chuoi so: ";
		cin >> scan;

		if (scan.length() < 17) {
			cout << "*****************************************\n";
			cout << "Chuoi so ban nhap qua ngan!\n";
			cout << "*****************************************\n";
			return;
		}

		for (int i = 0; (i < 128) && (i < scan.length()); i++) {

			if (scan[i] == '1') {
				data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
			}
			else {
				if (scan[i] == '0') {}
				else {
					cout << "*****************************************\n";
					cout << "Chuoi so ban nhap sai ky tu!\n";
					cout << "*****************************************\n";
					return;
				}
			}

		}
	}

	else {

		cout << "Nhap chuoi so: ";
		cin >> scan;

		int count = 0, count2 = 0, countNotZero = 0;

		for (int i = 0; i < scan.length(); i++) {
			if ((scan[i] < '0') || (scan[i] > '9')) {
				if (scan[i] == '.') { count++; }
				else {
					if ((scan[i] == '-') || (scan[i] == '+')) { count2++; }

					else {
						cout << "*****************************************\n";
						cout << "Chuoi so ban nhap sai ky tu!\n";
						cout << "*****************************************\n";
						return;
					}
				}

			}

			else { if (scan[i] != 0) { countNotZero++; } }
		}

		if ((count > 1) || (count2 > 1)) {
			cout << "*****************************************\n";
			cout << "Chuoi so ban nhap sai ky tu!\n";
			cout << "*****************************************\n";
			return;
		}

		if (countNotZero == 0) { return; }

		if ((scan[0] == '-') || (scan[0] == '+')) {

			if (scan[0] == '-') { data[0] = data[0] | (1 << (INTLENGT - 1)); }
			scan.erase(0, 1);
		}

		string PhanNguyen = "", PhanThapPhan = "", PhanDinhTri = "";
		int Point = scan.length();

		for (int i = 0; i < scan.length(); i++) {
			if (scan[i] == '.') {
				Point = i;
				break;
			}
		}

		for (int i = 0; i < Point; i++) {
			PhanNguyen += scan[i];
		}

		for (int i = Point + 1; i < scan.length(); i++) {
			PhanThapPhan += scan[i];
		}

		Point = 0;
		if ((PhanNguyen == "0") || (PhanNguyen == "")) {
			for (int i = 0; (i < 122) && (PhanThapPhan != "0"); i++) {

				int length = PhanThapPhan.length();
				PhanThapPhan = nhanChuoiVoi2(PhanThapPhan);

				if (PhanThapPhan.length() > length) {
					PhanDinhTri += "1";
					PhanThapPhan.erase(0, 1);
				}
				else { PhanDinhTri += "0"; }
			}

			while (PhanDinhTri[0] == '0') {
				Point--;
				PhanDinhTri.erase(0, 1);
			}
			Point--;
			PhanDinhTri.erase(0, 1);
		}

		else {
			while (PhanNguyen != "1") {

				if (mod2(PhanNguyen) == 1) { PhanDinhTri = "1" + PhanDinhTri; }
				else { PhanDinhTri = "0" + PhanDinhTri; }
				PhanNguyen = div2(PhanNguyen);
				Point++;
			}

			for (int i = 0; i < 122; i++) {

				int g = 0;
				for (int j = 0; j < PhanThapPhan.length(); j++) {
					if (PhanThapPhan[j] != '0') {
						g++;
						break;
					}
				}

				if (g == 0) { break; }

				int length = PhanThapPhan.length();
				PhanThapPhan = nhanChuoiVoi2(PhanThapPhan);

				if (PhanThapPhan.length() > length) {
					PhanDinhTri += "1";
					PhanThapPhan.erase(0, 1);
				}
				else { PhanDinhTri += "0"; }
			}
		}

		if ((Point < -127) || (Point > 127)) {
			cout << "*****************************************\n";
			cout << "Thong bao: Tran so!\n";
			cout << "*****************************************\n";
			return;
		}

		Point += 127;

		for (int i = 15; i > 0; i--) {
			if (Point % 2 == 1) { data[0] = data[0] | (1 << (INTLENGT - 1 - i)); }
			Point /= 2;
		}

		for (int i = 16; (i < 128) && (i - 16 < PhanDinhTri.length()); i++) {
			if (PhanDinhTri[i - 16] == '1') {
				data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
			}
		}

		int test = 0;
		for (int i = 0; i < 128; i++) {
			test += (data[i / INTLENGT] >> (INTLENGT - 1 - i)) & 1;
			if (test > 0) { break; }
		}
		if (test == 0) {
			cout << "*****************************************\n";
			cout << "Thong bao: Tran so!\n";
			cout << "*****************************************\n";
			return;
		}

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