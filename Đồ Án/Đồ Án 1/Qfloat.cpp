#include "Qfloat.h"

string nhanChuoiVoi2(string bigNum){

	string kq;
	int nho = 0;

	for (int i = bigNum.size() - 1; i >= 0; i--)
	{
		char res = (bigNum[i] - '0') * 2 + nho;
		if (res < 10)
		{
			res += '0';
			kq = res + kq;
			nho = 0;
		}
		else
		{
			nho = 1;
			res = res % 10;
			res += '0';
			kq = res + kq;
		}
	}

	if (nho == 1) { kq = '1' + kq; }

	return kq;
}

int stringToInt(string numStr) {
	int num = 0;

	for (int i = 0; i < numStr.length(); i++) {
		num = num * 10 + numStr[i] - '0';
	}

	return num;
}

string div2(string bigNum)
{

	string kq = "";
	string num = "0";
	int i = 0;
	int n = bigNum.size();

	while (i < n) {
		if (stringToInt(num) < 2) {
			num = num + bigNum[i];
			char res = (char)(stringToInt(num) / 2);
			kq = kq + char(res + '0');
			char du = stringToInt(num) % 2;
			num = du + '0';
			i++;
		}
	}

	while (kq[0] == '0' && kq.size() > 1) { kq.erase(0, 1); }

	return kq;
}

int mod2(string bigNum)
{
	return ((bigNum[bigNum.size() - 1] - '0') % 2);
}



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

		int z;
		cout << "*****************************************\n";
		cout << "1. Nhap dang cham thuong (Nhan 1)\n";
		cout << "2. Nhap dang (+/-) 1.F*2^E (Nhan 2)\n";
		cout << "*****************************************\n";
		cout << "Nhap lua chon cua ban: ";
		cin >> z;

		if ((z != 1) && (z != 2)) {
			cout << "*****************************************\n";
			cout << "Thong bao: Lua chon ban nhap khong hop le!\n";
			cout << "*****************************************\n";
			return;
		}
		
		if (z == 1) {
			cout << "Nhap chuoi so: ";
			cin >> scan;

			if (scan.length() < 17) {
				cout << "*****************************************\n";
				cout << "Thong bao: Chuoi so ban nhap qua ngan!\n";
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
						cout << "Thong bao: Chuoi so ban nhap sai ky tu!\n";
						cout << "*****************************************\n";
						return;
					}
				}

			}

		}

		if (z == 2) {
			int Dau, E;
			string F;

			cout << "Nhap dau(So duong nhap 0, So am nhap 1): ";
			cin >> Dau;

			if ((Dau != 0) && (Dau != 1)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Lua chon cua ban khong hop le!\n";
				cout << "*****************************************\n";
				return;
			}

			cout << "Nhap so mu (E) (Nhap dang thap phan): ";
			cin >> E;

			if ((E < -16383) || (E > 16383)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Tran so!\n";
				cout << "*****************************************\n";
				return;
			}

			cout << "Nhap phan dinh tri sau dau cham (F) (Nhap dang nhi phan): ";
			cin >> F;

			if (Dau == 1) { data[0] = data[0] | (1 << (INTLENGT - 1)); }

			E += 16383;
			for (int i = 15; i > 0; i--) {
				if (E % 2 == 1) { data[0] = data[0] | (1 << (INTLENGT - 1 - i)); }
				E /= 2;
			}

			for (int i = 16; (i < 128) && (i - 16 < F.length()); i++) {
				if (F[i - 16] == '1') {
					data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
				}
				else {
					if (F[i - 16] == '0') {}
					else {
						cout << "*****************************************\n";
						cout << "Thong bao: Chuoi so ban nhap sai ky tu!\n";
						cout << "*****************************************\n";
						return;
					}
				}
			}

		}

	}

	if (radix == 10) {

		int z;
		cout << "*****************************************\n";
		cout << "1. Nhap dang cham thuong (Nhan 1)\n";
		cout << "2. Nhap dang (+/-) A.B*10^X (Nhan 2)\n";
		cout << "*****************************************\n";
		cout << "Nhap lua chon cua ban: ";
		cin >> z;

		if ((z != 1) && (z != 2)) {
			cout << "*****************************************\n";
			cout << "Thong bao: Lua chon ban nhap khong hop le!\n";
			cout << "*****************************************\n";
			return;
		}

		if (z == 1) {

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
							cout << "Thong bao: Chuoi so ban nhap sai ky tu!\n";
							cout << "*****************************************\n";
							return;
						}
					}

				}

				else { if (scan[i] != 0) { countNotZero++; } }
			}

			if ((count > 1) || (count2 > 1)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Chuoi so ban nhap sai ky tu!\n";
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

			if ((Point < -16383) || (Point > 16383)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Tran so!\n";
				cout << "*****************************************\n";
				return;
			}

			Point += 16383;

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

		if (z == 2) {
			int Dau, X;
			string PhanNguyen, PhanThapPhan;

			cout << "Nhap dau(So duong nhap 0, So am nhap 1): ";
			cin >> Dau;

			if ((Dau != 0) && (Dau != 1)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Lua chon cua ban khong hop le!\n";
				cout << "*****************************************\n";
				return;
			}

			cout << "Nhap so mu (X) (Nhap dang thap phan): ";
			cin >> X;

			cout << "Nhap phan nguyen (A): ";
			cin >> PhanNguyen;

			for (int i = 0; i < PhanNguyen.length(); i++) {
				if ((PhanNguyen[i] < '0') || (PhanNguyen[i] > '9')) {
					cout << "*****************************************\n";
					cout << "Thong bao: Chuoi so ban nhap sai ky tu!\n";
					cout << "*****************************************\n";
					return;
				}

			}

			cout << "Nhap phan thap phan (B): ";
			cin >> PhanThapPhan;

			for (int i = 0; i < PhanThapPhan.length(); i++) {
				if ((PhanThapPhan[i] < '0') || (PhanThapPhan[i] > '9')) {
					cout << "*****************************************\n";
					cout << "Thong bao: Chuoi so ban nhap sai ky tu!\n";
					cout << "*****************************************\n";
					return;
				}

			}

			if (Dau == 1) { data[0] = data[0] | (1 << (INTLENGT - 1)); }

			if (X > 0) {
				for (int i = 0; i < X; i++) {

					if (PhanThapPhan != "") {
						PhanNguyen += PhanThapPhan[0];
						PhanThapPhan.erase(0, 1);
					}
					else {
						PhanNguyen += "0";
					}

				}
			}

			else {
				for (int i = 0; i > X; i--) {

					if (PhanNguyen != "") {
						PhanThapPhan = PhanNguyen[PhanNguyen.length() - 1] + PhanThapPhan;
						PhanNguyen.erase(PhanNguyen.length(), 1);
					}
					else {
						PhanThapPhan = "0" + PhanThapPhan;
					}

				}
			}

			string PhanDinhTri = "";
			int Point = 0;

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

			if ((Point < -16383) || (Point > 16383)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Tran so!\n";
				cout << "*****************************************\n";
				return;
			}

			Point += 16383;

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