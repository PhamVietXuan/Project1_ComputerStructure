#include <iostream>
using namespace std;
char binToDec(char a[8])//convert binary to integer number
{
    char x = 0;
    for (int i = 0; i < 8; i++)
    {
        x = x | (a[i] << (7 - i));
    }
    return x;
}
void decToBin(char n)
{
    char a[8] = { 0 };
    for (int i = 0; i < sizeof(n) * 8; i++)
    {
        a[sizeof(n) * 8 - 1 - i] = ((n >> i) & 1);
    }

    for (int i = 0; i < 8; i++)
        cout << (int)a[i];
    cout << endl;
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
    for (int i = bigNum.size()-1; i >= 0; i--)
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
    while (i<n)//divison 
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