#include "BigNum.h"
//Hàm chuyển đổi chuỗi nhị phân qua nhị phân lưu trong bit int
//Input: Chuỗi nhị phân
//Output: bit int có lưu giá trị chuỗi nhị phân
int binToDec(string bit)//convert binary to integer number
// bit.length() = 15: exponent
{
    int x = 0;
    for (int i = 0; i < bit.length(); i++)
    {
        x = x | ((bit[i] - '0') << (bit.length() - 1 - i));
    }
    return x;
}

//Hàm chuyển đổi bit int có lưu giá trị nhị phân qua chuỗi nhị phân
//Input: bit int có lưu giá trị chuỗi nhị phân
//Output: Chuỗi nhị phân
string decToBin(string dec)//convert decimal number to binary number(string)
{
    string bin = "";
    if (dec == "0")
        return "0";
    while (dec != "0")
    {
        bin = (char)(mod2(dec) + '0') + bin;
        dec = div2(dec);
    }

    return bin;
}

//Hàm chuyển chuỗi số thập phân qua kiểu int
//Input: Chuỗi số thập phân
//Output: Giá trị thập phân kiểu int
int stringToInt(string numStr)// convert a string to number 
{
    int num = 0;
    int dauAm = 1;
    if (numStr[0] == '-')
    {
        dauAm = -1;

        for (int i = 1; i < numStr.length(); i++)
        {
            num = num * 10 + numStr[i] - '0';
        }
    }
    else if (numStr[0] == '+')
    {
        dauAm = 1;

        for (int i = 1; i < numStr.length(); i++)
        {
            num = num * 10 + numStr[i] - '0';
        }
    }
    else
        for (int i = 0; i < numStr.length(); i++)
        {
            num = num * 10 + numStr[i] - '0';
        }
    return dauAm * num;
}

//Hàm chuyển đổi số thập phân kiểu int ra dạng chuỗi
//Input: Gia trị thạp phân kieur int
//Output: Dạng chuỗi
string intToString(int num)
{
    int n = num;
    string kq = "";
    while (n > 0)
    {
        kq += (char)(n % 2 + '0');
        n = n / 2;
    }
    return kq;
}


//Hàm nhân chuỗi với 2
//Intput: Chuỗi số ban đầu
//Output: Chuỗi số sau khi nhân 2
string nhanChuoiVoi2(string bigNum)//multiple a string by 2
{
    string kq;
    int nho = 0;
    int dau = 1;
    if (bigNum[0] == '-')//la so am
    {
        dau = -1;
        bigNum.erase(0, 1);
    }
    if (bigNum[0] == '+')//la so am
    {
        dau = 1;
        bigNum.erase(0, 1);
    }
    for (int i = bigNum.size() - 1; i >= 0; i--)
        if (bigNum[i] != '.')
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
        else
            kq = '.' + kq;

    if (nho == 1)//
        kq = '1' + kq;
    if (dau == -1)
        kq = "-" + kq;
    return kq;
}

//Hàm chia lấy phần nguyên chuỗi với 2
//Input: Chuỗi só ban đầu
//Output: Chuỗi số sau khi chia nguyên với 2
string div2(string bigNum)
{
    int dau = 1;
    if (bigNum[0] == '-')//la so am
    {
        dau = -1;
        bigNum.erase(0, 1);
    }
    if (bigNum[0] == '+')//la so am
    {
        dau = 1;
        bigNum.erase(0, 1);
    }
    string kq = "";
    string num = "0";
    int i = 0;
    int n = bigNum.size();
    while (i < n)//division 
    {
        if (stringToInt(num) < 2)
        {
            num = num + bigNum[i];
            char res = (char)(stringToInt(num) / 2);
            kq = kq + char(res + '0');
            char du = stringToInt(num) % 2;
            num = du + '0';
            i++;
        }

    }
    while (kq[0] == '0' && kq.size() > 1)//delete '0' character at the head of string.
    {
        kq.erase(0, 1);
    }
    if (dau == -1 && kq != "0")
        kq = "-" + kq;
    return kq;
}

//Hàm chia lấy phần dư chuỗi với 2
//Input: Chuỗi số ban đầu
//Output: Giá trị dư của chuỗi sau khi chia 2
int mod2(string bigNum)
{
    return ((bigNum[bigNum.size() - 1] - '0') % 2);
}

// Hàm chia chuỗi với 2 dạng sô thực
//Input: Chuỗi só ban đầu
//Output: Chuỗi số sau khi chia 2
string chia2(string bigNum)
{
    if (bigNum == "0") return "0";
    string strNum = "";
    strNum += bigNum[0];
    int num = stringToInt(strNum);;
    int i = 1;
    bool ok = 0;
    string kq = "0";

    while ((i < bigNum.length()) || (i >= bigNum.length() && num > 0))
    {

        if ((i >= bigNum.length()) && (ok == 0))
        {
            kq += '.';
            ok = 1;
        }

        if (num < 2)
        {
            if (i < bigNum.length())
            {
                if (bigNum[i] != '.')
                {

                    strNum += bigNum[i];
                    num = stringToInt(strNum);
                    kq += (char)(num / 2 + '0');

                    strNum = intToString(num % 2);
                    num = num % 2;
                    i++;
                }
                else
                {
                    ok = 1;
                    kq += '.';
                    i++;
                }
            }
            else
            {
                strNum += '0';
                num = stringToInt(strNum);
                kq += (char)(num / 2 + '0');
                strNum = intToString(num % 2);
                num = num % 2;

                i++;
            }
        }
        else
        {
            kq += (char)(num / 2 + '0');
            strNum = intToString(num % 2);
            num = num % 2;
        }
    }
    while (kq[0] == '0' && kq[1] != 0 && (kq.length() > 1) && kq[1] != '.') kq.erase(0, 1);
    return kq;
}

//Hàm 2^n
//Input: Mũ n
//Output: Giá trị 2^n
//Nếu n>0 nhân n lần với 2, n<0 chia n lần với 2, n=0 giá trị bằng 1
string pow(int n)
{
    if (n == 0) return "1";
    string res = "1";
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            res = nhanChuoiVoi2(res);
        }
        return res;
    }
    if (n < 0)
    {
        for (int i = 0; i < -n; i++)
        {
            res = chia2(res);
        }
        return res;
    }

}


//Hàm cộng 2 chuỗi số
//Input: Chuỗi số a, b
//Output: Chuỗi số mang kết quả phép cộng trên
string addFloat(string a, string b)
{

    //if integer part of both not equal, '0' will be add to the head of the string which has shorter integer part. 
    while (a.find('.') < b.find('.'))
        a = '0' + a;
    while (a.find('.') > b.find('.'))
        b = '0' + b;

    //if the real part of the two string not equal, '0' will be add to the last of the shorter string
    while (a.length() < b.length())
        a += '0';
    while (a.length() > b.length())
        b += '0';
    int nho = 0;
    string res = "";
    for (int i = a.length() - 1; i >= 0; i--)
    {
        if (a[i] != '.')
        {
            char kq = 0;
            kq = a[i] + b[i] + nho - 2 * '0';
            nho = kq / 10;
            kq = kq % 10;
            res = (char)(kq + '0') + res;
        }
        else res = '.' + res;
    }

    if (nho == 1)
        res = '1' + res;

    return res;
}

//Hàm đổi nhị phân sang thập phân của Qfloat
//Input: Qfloat được lưu trữ dạng nhị phân
//Output: Trả về dạng chuỗi kí tự giá trị thập phân
string binToQfloat(int bin[4])
{
    string kq = "";

    kq += '1';

    string exp = "";

    for (int i = 1; i <= 15; i++)
    {
        exp += (char)(getBit(bin[0], i) + '0');
    }

    int E = binToDec(exp) - 16383;

    string value = "";
    for (int i = 16; i < 128; i++)
    {
        value += (char)(getBit(bin[i / 32], i % 32) + '0');
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

    if (getBit(bin[0], 0) == 1) {
        kq = '-' + kq;

    }
    return kq;
}

//Ham gán 1 vào vị trí bit i của x
//Input:  Giá trị Int và vị trí i cần gán bit 1
//Output: Giá trị x sau khi đc gán bit 1 vào vị trí bit i
int setBit1(int x, int i)
{
    return ((1 << (31 - i)) | x);
}

//Hàm lấy bit i từ x
//Input: Giá trị Int và vị trí i cần lấy bit
//Output: Giá trị bit tại vị trí bit i của x
int getBit(int x, int i)
{
    return ((x >> (31 - i)) & 1);
}