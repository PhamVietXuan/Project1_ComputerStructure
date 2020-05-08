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

//I. Hàm nhập Qfloat
void Qfloat::ScanQfloat() {
	int radix;
	string scan = "";

	//1. Lựa chọn nhập hệ cơ số 2 hoặc 10
	cout << "Nhap he co so (2 hoac 10): ";
	cin >> radix;

	//2. TH1: Ngoại lệ
	if ((radix != 2) && (radix != 10)) {
		cout << "*****************************************\n";
		cout << "Thong bao: He co so ban nhap khong thoa!\n";
		cout << "*****************************************\n";
		return;
	}

	//3. Th2: TH cơ số 2
	if (radix == 2) {

		//a. Lựa chọn nhập dạng thường hoặc dạng (+/-) 1.F*2^E
		int z;
		cout << "*****************************************\n";
		cout << "1. Nhap dang cham thuong (Nhan 1)\n";
		cout << "2. Nhap dang (+/-) 1.F*2^E (Nhan 2)\n";
		cout << "*****************************************\n";
		cout << "Nhap lua chon cua ban: ";
		cin >> z;

		//b. TH1: Nhập lựa chọn sai
		if ((z != 1) && (z != 2)) {
			cout << "*****************************************\n";
			cout << "Thong bao: Lua chon ban nhap khong hop le!\n";
			cout << "*****************************************\n";
			return;
		}

		//c. TH2: Nhập bình thường
		if (z == 1) {
			// Nhập chuỗi số
			cout << "Nhap chuoi so: ";
			cin >> scan;

			// Xét trường hợp không thoả điều kiện (chuỗi ngắn hơn 17 kí tự)
			if (scan.length() < 17) {
				cout << "*****************************************\n";
				cout << "Thong bao: Chuoi so ban nhap qua ngan!\n";
				cout << "*****************************************\n";
				return;
			}

			// Nhập chuỗi nhị phân vô Qfloat, dò TH chuỗi bị sai kí tự
			int i;

			for (i = 0; (i < 128) && (i < scan.length()); i++) {

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

			// Làm tròn (nếu chuỗi nhị phân quá dài)
			if (i == 128 && scan.length() > 127) {
				if (scan[i] == '1') {
					i--;
					while ((((data[i / INTLENGT] >> (INTLENGT - 1 - i)) & 1) == 1) && (i > 15)) {
						data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
						i--;
					}
					data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
				}
			}

		}

		// d. TH3: Nhập dạng (+/-) 1.F*2^E
		if (z == 2) {
			int Dau, E;
			string F;

			// Nhap Dấu, Mũ, Phần Định Trị, xét trường hợp chuỗi không thoả
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

			// Nhập giá trị dấu vô Qfloat
			if (Dau == 1) { data[0] = data[0] | (1 << (INTLENGT - 1)); }

			// Nhập giá trị E = Mũ + 16383 vô Qfloat
			E += 16383;
			for (int i = 15; i > 0; i--) {
				if (E % 2 == 1) { data[0] = data[0] | (1 << (INTLENGT - 1 - i)); }
				E /= 2;
			}

			//  Nhập Phần Định Trị vô Qfloat
			int i;

			for (i = 16; (i < 128) && (i - 16 < F.length()); i++) {
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

			// Làm tròn (nếu Phần Định Trị đủ dài)
			if (i == 128 && F.length() >= 112) {
				if (F[i - 16] == '1') {
					i--;
					while ((((data[i / INTLENGT] >> (INTLENGT - 1 - i)) & 1) == 1) && (i > 15)) {
						data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
						i--;
					}
					data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
				}
			}

		}

	}

	//4. Th3: TH cơ số 10
	if (radix == 10) {

		//a. Lua chon nhập chuỗi bình thường hoặc dạng (+/-) A.B*10^X
		int z;
		cout << "*****************************************\n";
		cout << "1. Nhap dang cham thuong (Nhan 1)\n";
		cout << "2. Nhap dang (+/-) A.B*10^X (Nhan 2)\n";
		cout << "*****************************************\n";
		cout << "Nhap lua chon cua ban: ";
		cin >> z;

		//b. TH1: Nhập lựa chọn sai
		if ((z != 1) && (z != 2)) {
			cout << "*****************************************\n";
			cout << "Thong bao: Lua chon ban nhap khong hop le!\n";
			cout << "*****************************************\n";
			return;
		}

		//c. TH2: Nhập bình thường
		if (z == 1) {

			// Nhập chuỗi số
			cout << "Nhap chuoi so: ";
			cin >> scan;

			int count = 0, count2 = 0, countNotZero = 0;

			// Dò trường hợp chuỗi nhập sai kí tự (bao gồm kí tự khác '1', '2', '-', '+', '.'
			for (int i = 0; i < scan.length(); i++) {
				if ((scan[i] < '0') || (scan[i] > '9')) {
					if (scan[i] == '.') { count++; }
					else {
						if ((scan[i] == '-') || (scan[i] == '+')) { 
							count2++; 
							if (i != 0) { count2++; }
						}

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

			// Dò trường hợp chuỗi nhập sai
			if ((count > 1) || (count2 > 1)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Chuoi so ban nhap sai ky tu!\n";
				cout << "*****************************************\n";
				return;
			}
			// TH chuỗi toàn số 0 -> số 0
			if (countNotZero == 0) { return; }

			// TH chuỗi có dấu đằng trước, đồng thời lưu giá trị dấu vào Qfloat
			if ((scan[0] == '-') || (scan[0] == '+')) {

				if (scan[0] == '-') { data[0] = data[0] | (1 << (INTLENGT - 1)); }
				scan.erase(0, 1);
			}

			// Chia chuỗi vừa nhập ra phần nguyên và phần thập phân, bằng cách tìm ra vị trí dấu chấm
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

			// Đổi Phần Nguyên và Phần Nhị Phân ra chuỗi nhị phân lưu vào biến Phần Định Trị
			// Dùng biến xét vị trí dấu chấm thành biến xét mũ, đếm giá trị mũ
			Point = 0;
			if ((PhanNguyen == "0") || (PhanNguyen == "")) {
				for (int i = 0; (i < 122) && (PhanThapPhan != "0"); i++) {

					int length = PhanThapPhan.length();
					PhanThapPhan = nhanChuoiVoi2(PhanThapPhan);

					if (PhanThapPhan.length() > length) {
						PhanDinhTri += "1";
						PhanThapPhan.erase(0, 1);
					}
					else {
						PhanDinhTri += "0";
						i--;
					}
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
					else {
						PhanDinhTri += "0";
						i--;
					}
				}
			}

			// Xét TH mũ quá lớn hoặc quá nhỏ
			if ((Point < -16383) || (Point > 16383)) {
				cout << "*****************************************\n";
				cout << "Thong bao: Tran so!\n";
				cout << "*****************************************\n";
				return;
			}

			// Cộng số mũ với 16383 để ra giá trị E
			Point += 16383;

			// Lưu giá trị mũ vô Qfloat
			for (int i = 15; i > 0; i--) {
				if (Point % 2 == 1) { data[0] = data[0] | (1 << (INTLENGT - 1 - i)); }
				Point /= 2;
			}

			// Lưu Phần Định Trị vô Qfloat
			int i;

			for (i = 16; (i < 128) && (i - 16 < PhanDinhTri.length()); i++) {
				if (PhanDinhTri[i - 16] == '1') {
					data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
				}
			}

			// Làm tròn nếu Phần Định Trị quá dài
			if (i == 128 && PhanDinhTri.length() >= 112) {
				if (PhanDinhTri[i] == '1') {
					i--;
					while ((((data[i / INTLENGT] >> (INTLENGT - 1 - i)) & 1) == 1) && (i > 15)) {
						data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
						i--;
					}
					data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
				}
			}


		}

		//d. TH3: Nhập dạng (+/-) A.B*10^X
		if (z == 2) {
			int Dau, X;
			string PhanNguyen, PhanThapPhan;

			//Nhập Dấu, Nhập Mũ X, Nhập A, B, Xét trường hợp nhập sai
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

			// Xét dấu, lưu giá trị vào Qfloat
			if (Dau == 1) { data[0] = data[0] | (1 << (INTLENGT - 1)); }

			// Xét gia trị mũ, để đặt lại dấu chấm
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
						PhanNguyen.erase(PhanNguyen.length() - 1, 1);
					}
					else {
						PhanThapPhan = "0" + PhanThapPhan;
					}

				}
			}

			// Phần còn lại làm giống TH1
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
					else {
						PhanDinhTri += "0";
						i--;
					}
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
					else {
						PhanDinhTri += "0";
						i--;
					}
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

			int i;

			for (i = 16; (i < 128) && (i - 16 < PhanDinhTri.length()); i++) {
				if (PhanDinhTri[i - 16] == '1') {
					data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
				}
			}

			if (i == 128 && PhanDinhTri.length() >= 112) {
				if (PhanDinhTri[i] == '1') {
					i--;
					while ((((data[i / INTLENGT] >> (INTLENGT - 1 - i)) & 1) == 1) && (i > 15)) {
						data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
						i--;
					}
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

void Qfloat::DecToBin(string scan) {

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
			else {
				PhanDinhTri += "0";
				i--;
			}
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
			else {
				PhanDinhTri += "0";
				i--;
			}
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

	int i;

	for (i = 16; (i < 128) && (i - 16 < PhanDinhTri.length()); i++) {
		if (PhanDinhTri[i - 16] == '1') {
			data[i / INTLENGT] = data[i / INTLENGT] | (1 << (INTLENGT - 1 - i % INTLENGT));
		}
	}

	if (i == 128 && PhanDinhTri.length() >= 112) {
		if (PhanDinhTri[i] == '1') {
			i--;
			while ((((data[i / INTLENGT] >> (INTLENGT - 1 - i)) & 1) == 1) && (i > 15)) {
				data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
				i--;
			}
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
	return;
}

Qfloat::~Qfloat() {

}