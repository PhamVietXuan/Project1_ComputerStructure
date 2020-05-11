#include <iostream>
#include <sstream>
#include "Qfloat.h"
#include "BigNum.h"

using namespace std;

// Hàm khởi tạo
Qfloat::Qfloat() {

}

// a. Hàm nhập Qfloat

//Hàm nhập Qfloat dạng chuỗi thường nhị phân và thập phân
//Input: Hệ cơ số ban đầu, chuỗi số muốn nhâp
//Output: Chuỗi đã được lưu vào Qfloat hoặc gán giá trị cho ngoại lệ
//Nếu là hệ thập phân ban đầu, xác định giá trị mũ E, chuyển chuỗi qua nhị phân lưu vào phần định trị để lưu vào Qfloat
void Qfloat::ScanQfloat(int radix, string scan) {

	//2. TH1: Ngoại lệ
	if ((radix != 2) && (radix != 10)) {
		Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
		return;
	}

	//3. Th2: TH cơ số 2
	if (radix == 2) {

		// Xét trường hợp không thoả điều kiện (chuỗi ngắn hơn 17 kí tự)
		if (scan.length() < 17) {
			Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
			return;
		}

		if (scan.length() > 128) {
			Exception = 1;//"Thong bao: He co so ban nhap khong thoa!
			return;
		}

		// Nhập chuỗi nhị phân vô Qfloat, dò TH chuỗi bị sai kí tự
		int i;

		for (i = 0; (i < 128) && (i < scan.length()); i++) {

			if (scan[i] == '1') {
				data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
			}
			else {
				if (scan[i] == '0') {}
				else {
					Exception = 1;//"Thong bao: He co so ban nhap khong thoa!
					return;
				}
			}

		}
	}

	//4. Th3: TH cơ số 10
	if (radix == 10) {

		int count = 0, count2 = 0, countNotZero = 0;

		// Dò trường hợp chuỗi nhập sai kí tự (bao gồm kí tự khác số, '-', '+', '.'
		for (int i = 0; i < scan.length(); i++) {
			if ((scan[i] < '0') || (scan[i] > '9')) {
				if (scan[i] == '.') { count++; }
				else {
					if ((scan[i] == '-') || (scan[i] == '+')) {
						count2++;
						if (i != 0) { count2++; }
					}

					else {
						Exception = 1;//"Thong bao: He co so ban nhap khong thoa!
						return;
					}
				}

			}

			else { if (scan[i] != '0') { countNotZero++; } }
		}

		// Dò trường hợp chuỗi nhập sai
		if ((count > 1) || (count2 > 1)) {
			Exception = 1;//"Thong bao: He co so ban nhap khong thoa!
			return;
		}
		// TH chuỗi toàn số 0 -> số 0
		if (countNotZero == 0) { return; }

		// TH chuỗi có dấu đằng trước, đồng thời lưu giá trị dấu vào Qfloat
		if ((scan[0] == '-') || (scan[0] == '+')) {

			if (scan[0] == '-') { data[0] = setBit1(data[0 / INTLENGT], 0 % INTLENGT); }
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

		// Đổi Phần Nguyên và Phần Thập Phân ra chuỗi nhị phân lưu vào biến Phần Định Trị
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
		if ((Point < (-16383 - 112)) || (Point > 16383)) {
			Exception = 2; //"Thong bao: Tran So!
			return;
		}

		// Cộng số mũ với 16383 để ra giá trị E
		int E = 16383 + Point;

		//TH đặc biệt: normalized number
		if (E < 0) {

			// Nhập phần định trị cho normalized number
			int i = 0;

			for (i = 16 - E; (i < 128) && (i - 16 + E < PhanDinhTri.length()); i++) {
				if (PhanDinhTri[i - 16 + E] == '1') {
					data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
				}
				else {
					if (PhanDinhTri[i - 16 + E] == '0') {}
					else {
						Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
						return;
					}
				}
			}

			// Làm tròn (nếu Phần Định Trị đủ dài)
			if (i == 128 && PhanDinhTri.length() >= 112 + E) {
				if (PhanDinhTri[i - 16 + E] == '1') {
					i--;
					while ((getBit(data[i / INTLENGT], i % INTLENGT) == 1) && (i > 15)) {
						data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
						i--;
					}
					data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
				}
			}
			return;
		}



		// Lưu giá trị mũ vô Qfloat với TH bình thường
		for (int i = 15; i > 0; i--) {
			if (E % 2 == 1) { data[0] = setBit1(data[i / INTLENGT], i % INTLENGT); }
			E /= 2;
		}

		// Lưu Phần Định Trị vô Qfloat
		int i;

		for (i = 16; (i < 128) && (i - 16 < PhanDinhTri.length()); i++) {
			if (PhanDinhTri[i - 16] == '1') {
				data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
			}
		}

		// Làm tròn nếu Phần Định Trị quá dài
		if (i == 128 && PhanDinhTri.length() >= 112) {
			if (PhanDinhTri[i] == '1') {
				i--;
				while ((getBit(data[i / INTLENGT], i % INTLENGT) == 1) && (i > 15)) {
					data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
					i--;
				}
				data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
			}
		}

	}

	return;
}

//Hàm nhập Qfloat dạng chuỗi nhị phân dạng (+/-)1.F*2^E
//Input: Hệ cơ số ban đầu, dấu, mũ và phần định trị của giá trị nhị phân bạn muốn nhập
//Output: Chuỗi đã được lưu vào Qfloat hoặc gán giá trị cho ngoại lệ
//Lưu lần lượt các giá trị vào Qfloat, riêng với giá trị mũ cần cộng 16383 sau đó chuyển qua nhị phân để lưu vào Qfloat
void Qfloat::ScanQfloat(int radix, int Dau, int E, string F) {

	//2. TH1: Ngoại lệ
	if ((radix != 2)) {
		Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
		return;
	}

	//3. Th2: TH cơ số 2 dạng (+/-) 1.F*2^E
	if ((Dau != 0) && (Dau != 1)) {
		Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
		return;
	}

	if ((E < (-16383 - 112)) || (E > 16383)) {
		Exception = 2; //"Thong bao: Tran So!
		return;
	}

	// Nhập giá trị dấu vô Qfloat
	if (Dau == 1) { data[0] = setBit1(data[0 / INTLENGT], 0 % INTLENGT); }

	// Nhập giá trị E = Mũ + 16383 vô Qfloat
	E += 16383;

	//TH đặc biệt: normalized number
	if (E < 0) {

		// Nhập phần định trị cho normalized number
		int i = 0;

		for (i = 16 - E; (i < (128)) && ((i - 16 + E) < F.length()); i++) {
			if (F[i - 16 + E] == '1') {
				data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
			}
			else {
				if (F[i - 16 + E] == '0') {}
				else {
					Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
					return;
				}
			}
		}

		// Làm tròn (nếu Phần Định Trị đủ dài)
		if (i == 128 + E && F.length() >= 112 + E) {
			if (F[i - 16 + E] == '1') {
				i--;
				while ((getBit(data[i / INTLENGT], i % INTLENGT) == 1) && (i > 15)) {
					data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
					i--;
				}
				data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
			}
		}
		return;
	}

	// Nhập mũ với TH bình thường
	for (int i = 15; i > 0; i--) {
		if (E % 2 == 1) { data[0] = setBit1(data[i / INTLENGT], i % INTLENGT); }
		E /= 2;
	}

	// Nhập Phần Định Trị vô Qfloat
	int i;

	for (i = 16; (i < 128) && (i - 16 < F.length()); i++) {
		if (F[i - 16] == '1') {
			data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
		}
		else {
			if (F[i - 16] == '0') {}
			else {
				Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
				return;
			}
		}
	}

	// Làm tròn (nếu Phần Định Trị đủ dài)
	if (i == 128 && F.length() >= 112 + E) {
		if (F[i - 16 + E] == '1') {
			i--;
			while ((getBit(data[i / INTLENGT], i % INTLENGT) == 1) && (i > 15)) {
				data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
				i--;
			}
			data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
		}
	}

}

//Hàm nhập Qfloat dạng chuỗi nhị phân dạng (+/-)PhanNguyen.PhanThapPhan*10^X
//Input: Hệ cơ số ban đầu, dấu, mũ và phần nguyên, phần thập phân của số thập phan bạn muốn nhập
//Output: Chuỗi đã được lưu vào Qfloat hoặc gán giá trị cho ngoại lệ
//Lưu lần lượt các giá trị vào Qfloat, riêng với giá trị mũ cần cộng 16383 sau đó chuyển qua nhị phân để lưu vào Qfloat
// Chuyển qua dạng chuỗi thương để xác định phần nguyên và phần thập phân chính xác
// Sau đó chuyển qua nhị phân lưu vào phần định trị nhị phân và lưu vào Qfloat
void Qfloat::ScanQfloat(int radix, int Dau, int X, string PhanNguyen, string PhanThapPhan) {

	//2. TH1: Ngoại lệ
	if ((radix != 10)) {
		Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
		return;
	}

	//3. Th2: TH cơ số 10 dạng (+/-) A.B*10^X

	if ((Dau != 0) && (Dau != 1)) {
		Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
		return;
	}

	int CountNotZero = 0;

	for (int i = 0; i < PhanNguyen.length(); i++) {
		if ((PhanNguyen[i] < '0') || (PhanNguyen[i] > '9')) {
			Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
			return;
		}

		if (PhanNguyen[i] != '0') { CountNotZero++; }
	}

	for (int i = 0; i < PhanThapPhan.length(); i++) {
		if ((PhanThapPhan[i] < '0') || (PhanThapPhan[i] > '9')) {
			Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
			return;
		}

		if (PhanThapPhan[i] != '0') { CountNotZero++; }
	}

	//TH đặc biệt: Giá trị bằng 0
	if (CountNotZero == 0) { return; }

	// Xét dấu, lưu giá trị vào Qfloat
	if (Dau == 1) { data[0] = setBit1(data[0 / INTLENGT], 0 % INTLENGT); }

	// Xét giá trị mũ, để đặt lại dấu chấm
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

	// Đổi Phần Nguyên và Phần Thập Phân ra chuỗi nhị phân lưu vào biến Phần Định Trị
	// Dùng biến xét vị trí dấu chấm thành biến xét mũ, đếm giá trị mũ
	if ((PhanNguyen == "0") || (PhanNguyen == "")) {

		if (PhanThapPhan == "0") { return; }

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

	//Xét TH mũ quá lớn hoặc quá nhỏ
	if ((Point < (-16383 - 112)) || (Point > 16383)) {
		Exception = 2; //"Thong bao: Tran So!
		return;
	}

	// Cộng số mũ với 16383 để ra giá trị E
	int E = 16383 + Point;

	//TH đặc biệt: normalized number
	if (E < 0) {

		// Nhập phần định trị cho normalized number
		int i = 0;

		for (i = 16 - E; (i < 128) && (i - 16 + E < PhanDinhTri.length()); i++) {
			if (PhanDinhTri[i - 16 + E] == '1') {
				data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
			}
			else {
				if (PhanDinhTri[i - 16 + E] == '0') {}
				else {
					Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
					return;
				}
			}
		}

		// Làm tròn (nếu Phần Định Trị đủ dài)
		if (i == 128 && PhanDinhTri.length() >= 112 + E) {
			if (PhanDinhTri[i - 16 + E] == '1') {
				i--;
				while ((getBit(data[i / INTLENGT], i % INTLENGT) == 1) && (i > 15)) {
					data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
					i--;
				}
				data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
			}
		}
		return;
	}



	// Lưu giá trị mũ vô Qfloat với TH bình thường
	for (int i = 15; i > 0; i--) {
		if (E % 2 == 1) { data[0] = setBit1(data[i / INTLENGT], i % INTLENGT); }
		E /= 2;
	}

	// Lưu Phần Định Trị vô Qfloat
	int i;

	for (i = 16; (i < 128) && (i - 16 < PhanDinhTri.length()); i++) {
		if (PhanDinhTri[i - 16] == '1') {
			data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
		}
	}

	// Làm tròn nếu phần định trị quá dài
	if (i == 128 && PhanDinhTri.length() >= 112) {
		if (PhanDinhTri[i] == '1') {
			i--;
			while ((getBit(data[i / INTLENGT], i % INTLENGT) == 1) && (i > 15)) {
				data[i / INTLENGT] = data[i / INTLENGT] ^ (1 << (INTLENGT - 1 - i % INTLENGT));
				i--;
			}
			data[i / INTLENGT] = setBit1(data[i / INTLENGT], i % INTLENGT);
		}
	}

	//TH làm tròn bị tràn số ra số vô cùng ( 1/0  1111111111111111  0000000000........)
	int test = 0;
	for (int i = 16; i < 128; i++) {
		test += getBit(data[i / INTLENGT], i % INTLENGT);
		if (test > 0) { break; }
	}
	if (test == 0) {

		int test2 = 0;

		for (int i = 1; i < 16; i++) {
			test2 += getBit(data[i / INTLENGT], i % INTLENGT);
		}

		if (test2 == 15) {
			Exception = 2;//"Thong bao: Tran So!
			return;
		}
	}

	return;
}

// b. Hàm xuất Qfloat
//Input: Hệ số bạn muốn xuất, Qfloat, Exception
//Output: Trả về dạng chuỗi kí tự giá trị hoặc trả về rỗng nếu vô TH ngoại lệ
string Qfloat::PrintQfloat(int radix)
{
	stringstream Value;

	//TH chuỗi bị nhập sai
	if (Exception == 1) {
		Value << " ";
		return Value.str();
	}

	//TH chuỗi bị ràn số
	if (Exception == 2) {
		Value << " ";
		return Value.str();
	}

	// TH hệ số yêu cầu xuất nhập sai
	if (radix != 2 && radix != 10)
	{
		Value <<" ";
	}

	//TH xuất hệ số 2
	if (radix == 2)
	{
		Value << getBit(this->data[0], 0);
		Value << "  ";
		for (int i = 1; i < 128; i++)
		{
			if ((i + 4) % 4 == 0)
				Value << " ";
			if (i == 16) Value << "  ";
			Value << getBit(this->data[i / INTLENGT], i % INTLENGT);
		}
	}

	//TH xuất hệ số 10
	if (radix == 10)
	{
		Value << binToQfloat(this->data);
	}

	return Value.str();

}

// c. Hàm đổi nhị phân sang thập phân của Qfloat
//Input: Qfloat được lưu trữ dạng nhị phân
//Output: Trả về dạng chuỗi kí tự giá trị thập phân
string Qfloat::BinToDec()
{
	string kq = "";

	kq += '1';

	string exp = "";

	for (int i = 1; i <= 15; i++)
	{
		exp += (char)(getBit(data[0], i) + '0');
	}

	int E = binToDec(exp) - 16383;

	string value = "";
	for (int i = 16; i < 128; i++)
	{
		value += (char)(getBit(data[i / 32], i % 32) + '0');
	}

	string M = "0.0";
	for (int i = 0; i < value.length(); i++)
	{
		if (value[i] == '1')
			M = addFloat(M, pow(-(i + 1)));

	}

	M[0] = '1';
	kq = M;
	if (E >= 0)
	{
		for (int i = 1; i <= E; i++)
			kq = nhanChuoiVoi2(kq);
	}
	if (E < 0)
	{
		for (int i = 0; i < -E; i++)
		{
			kq = chia2(kq);
		}
	}

	if (getBit(data[0], 0) == 1) {
		kq = '-' + kq;

	}
	return kq;
}

// d. Hàm đổi thập phân sang nhị phân của Qfloat
//Input: Chuỗi số thập phân muốn nhâp
//Output: Chuỗi đã được lưu vào Qfloat hoặc gán giá trị cho ngoại lệ
//Hệ thập phân ban đầu, xác định giá trị mũ E, chuyển chuỗi qua nhị phân lưu vào phần định trị để lưu vào Qfloat
void Qfloat::DecToBin(string scan) {

	int count = 0, count2 = 0, countNotZero = 0;

	for (int i = 0; i < scan.length(); i++) {
		if ((scan[i] < '0') || (scan[i] > '9')) {
			if (scan[i] == '.') { count++; }
			else {
				if ((scan[i] == '-') || (scan[i] == '+')) { count2++; }

				else {
					Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
					return;
				}
			}

		}

		else { if (scan[i] != 0) { countNotZero++; } }
	}

	if ((count > 1) || (count2 > 1)) {
		Exception = 1; //"Thong bao: He co so ban nhap khong thoa!
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
		Exception = 2; //"Thong bao: Tran So!
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
		Exception = 2;//"Thong bao: Tran So!
		return;
	}
	return;
}

// Hàm huỷ
Qfloat::~Qfloat() {

}