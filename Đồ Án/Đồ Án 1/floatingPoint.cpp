#include <iostream>
#include "floatingPoint.h";

using namespace std;


void floatingPoint::printQfloat()
{
    cout << "Nhap hinh thuc xuat(He 2 hoac He 10): ";
    _int64 radix;
    cin >> radix;
    if (radix != 2 && radix != 10)
        cout << "Sai he co so, moi nhap lai." << endl;
    if (radix == 2)
    {
        cout << getBit(this->data[0], 0) << "  ";
        for (int i = 1; i < 128; i++)
        {
            if ((i + 4) % 4 == 0)
                cout << " ";
            if (i == 16) cout << "  ";
            cout << getBit(this->data[i / 4], i % 4);
        }
    }
    if (radix == 10)
    {
        cout << binToQfloat(this->data);
    }
 
}
int binToDec(string bit)//convert binary to integer number
// bit.length() = 15: exponent
{
    int x = 0;
    for (int i = 0; i < bit.length(); i++)
    {
        x = x | ((bit[i] - '0') << (bit.length()-1 - i));
    }
    return x;
}

string decToBin(string dec)
{
    string bin = "";
    if (dec == "0")
        return "0";
    while (dec != "0")
    {
        bin = (char)(mod2(dec)+'0')+bin;
        dec = div2(dec);
    }

    return bin;
}
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
    return dauAm*num;
}   
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
    while (i<n)//division 
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
    while (kq[0] == '0' && kq.size()>1)//delete '0' character at the head of string.
    {
        kq.erase(0, 1);
    }
    if (dau == -1 && kq!= "0")
        kq = "-" + kq;
    return kq;
}
int mod2(string bigNum)
{
    return ((bigNum[bigNum.size() - 1] - '0') % 2);
}
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
                    if (bigNum[i] != '.' )
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

string pow( int n)
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
int setBit1(int x, int i)
{
    return ((1 << (31 - i)) | x);
}
int getBit(int x, int i)
{
    return ((x >> (31 - i)) & 1);
}
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
        value += (char)(getBit(bin[i / 32], i % 32)+'0');
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
   
    if (getBit(bin[0], 0) == '1')
        kq = '-' + kq;
    return kq;
}