#include<iostream>
#include<string>
#include "Header.h"

#pragma comment (lib, "winmm.lib")
using namespace std;

void Revstr(string& a)
{
	for (int i = 0; i <= (a.size() - 1) / 2; i++)
		swap(a[i], a[a.size() - 1 - i]);
}

int Atoi(char c)
{
	return int(c - '0');
}
void xoaso0dungdau(string& s)// neu 0000=>0
{
	while (Atoi(s[0]) == 0 && s.size() > 1)
		s.erase(s.begin());
}

void chuanhoachuoi(string& s)
{
	if (s[0] != '-') xoaso0dungdau(s);
	else
	{
		while (s[1] == '0')
		{
			s.erase(1, 1);
		}
		if (s == "-")
			s = "0";
	}
}

string tong(string a, string b)// ham tinh tong 2 so nguyen duong
{
	string c;
	int i = 0;
	int TONG = 0;
	Revstr(b);
	Revstr(a);
	int n = a.length();
	int m = b.length();
	while (n > m)
	{
		b.push_back('0');
		m++;
	}
	while (m > n)
	{
		a.push_back('0');
		n++;
	}
	while (i < a.length())
	{
		TONG = TONG + (a[i] + b[i] - 96);
		c.push_back(TONG % 10 + 48);
		TONG /= 10;
		i++;
	}
	if (TONG > 0)
	{
		c.push_back(TONG + 48);
	}
	Revstr(c);
	return c;
}

bool sosanh2soduoidangstring(string a, string b)// neu a nho hon hoac bang b thi return true
{
	if (a.size() < b.size() || (a.size() == b.size() && a < b) || a == b)
		return true;
	return false;
}

string hieu(string a, string b)// ham tính hiệu 2 số nguyên dương (có trả về giá trị âm)
{
	string c;
	int i = 0;
	int HIEU = 0;
	bool KT = true;
	if (a.length() < b.length())
	{
		swap(a, b);
		KT = false;
	}
	else if (a.length() == b.length())// 2 if để swap chuỗi nếu số trừ lớn hơn số bị trừ
	{
		if (b > a)
		{
			swap(a, b);
			KT = false;
		}
	}
	Revstr(b);
	Revstr(a);
	int n = a.length();
	int m = b.length();
	while (n > m)
	{
		b.push_back('0');
		m++;
	}
	while (m > n)
	{
		a.push_back('0');
		n++;
	}
	while (i < n)// xét các trường hợp và thực hiên tính toán
	{
		if (a[i] > b[i])
		{
			HIEU = (a[i] - b[i]) + HIEU;
			c.push_back(HIEU + 48);
			HIEU = 0;
		}
		else if (a[i] < b[i])
		{
			HIEU = (a[i] + 10 - b[i]) + HIEU;
			c.push_back(abs(HIEU) + 48);
			HIEU = -1;
		}
		else
		{
			if (HIEU < 0)
			{
				HIEU = (a[i] + 10 - b[i]) + HIEU;
				c.push_back(abs(HIEU) + 48);
				HIEU = -1;
			}
			else
			{
				HIEU = (a[i] - b[i]) + HIEU;
				c.push_back(HIEU + 48);
				HIEU = 0;
			}
		}
		i++;
	}
	Revstr(c);
	if (KT == false)
	{
		c = '-' + c;
	}
	chuanhoachuoi(c);
	return c;
}

string tichvoi1so(string a, int b)// tich cua 1 chuoi so duong với 1 số nguyên dương bất kì
{
	if (b == 0) return "0";
	string c;
	int du = 0;;
	for (int i = a.size() - 1; i > -1; i--)
	{
		c.push_back(char((Atoi(a[i]) * b + du) % 10 + 48));
		du = (Atoi(a[i]) * b + du) / 10;
	}
	if (du > 0) c.push_back(char(du + 48));
	Revstr(c);
	return c;
}

void themso0cuoicung(string& s, int n)// them n số 0 vào cuối chuỗi
{
	for (int i = 0; i < n; i++)
		s.push_back('0');
}

string nhan(string a, string b)
{
	string d = "0";
	Revstr(b);
	Revstr(a);
	int n = a.length();
	int m = b.length();
	while (n > m)
	{
		b.push_back('0');
		m++;
	}
	while (m > n)
	{
		a.push_back('0');
		n++;
	}
	for (int i = 0; i < m; i++)
	{
		int TICH = 0;
		string c = "";
		for (int j = 0; j < n; j++)// hàm nhân từng số vào số nhân
		{
			TICH = TICH + ((b[i] - 48) * (a[j] - 48));
			c.push_back(TICH % 10 + 48);
			TICH /= 10;
		}
		if (TICH > 0)// nếu số dư lớ hơn 0 thì thêm vào đầu kq nhân
		{
			c.push_back(TICH + 48);
		}
		Revstr(c);
		for (int k = 0; k < i; k++)// chuẩn hóa thành những chuỗi bằng nhau
		{
			c = c + '0';
		}
		d = tong(d, c);// tong tất cả những chuỗi nhân được để thành kết quả
	}
	chuanhoachuoi(d);
	return d;
}

void xuliphepchialandau(string& a, string b, string& c, int& sochusodu)// chọn và chia số chia lần đầu
{
	int n = b.size();
	string a1 = a.substr(0, n);
	if (sosanh2soduoidangstring(b, a1)) // b nho hon hoặc bằng chuoi cắt a1
	{
		for (int i = 9; i > 0; i--)
		{
			if (sosanh2soduoidangstring(tichvoi1so(b, i), a1)) // tich của chuỗi b với i < = a1
			{
				c.push_back(char(i + 48));
				string sodu = hieu(a1, tichvoi1so(b, i));
				sochusodu = sodu.size();
				a.erase(0, n);
				a.insert(0, sodu);
				break;
			}
		}
	}
	else
	{
		a1 = a.substr(0, n + 1);
		for (int i = 9; ; i--)
		{
			if (sosanh2soduoidangstring(tichvoi1so(b, i), a1))
			{
				c.push_back(char(i + 48));
				string sodu = hieu(a1, tichvoi1so(b, i));
				sochusodu = sodu.size();
				a.erase(0, n + 1);
				a.insert(0, sodu);
				break;
			}
		}
	}
}

void xuliphepchia(string& temp, string b, string& c, int& sochusodu)// chia những lần tiếp theo
{
	for (int i = 9; ; i--)
	{
		if (sosanh2soduoidangstring(tichvoi1so(b, i), temp))// tich <= temp
		{
			c.push_back(char(i + 48));
			string sodu = hieu(temp, tichvoi1so(b, i));
			sochusodu = sodu.size();
			temp = sodu;
			break;
		}
	}
}

string chia(string a, string b)// chia 2 so nguyen duong
{
	xoaso0dungdau(b);
	if (b == "0") return "MATH ERROR!";
	string c;
	int sochusodu = 0;
	xuliphepchialandau(a, b, c, sochusodu);
	while (sochusodu < a.size())//XU LI PHEP CHIA NHUNG LAN TIEP THEO
	{
		string temp = a.substr(0, sochusodu + 1);
		xoaso0dungdau(temp);
		a.erase(0, sochusodu + 1);
		xuliphepchia(temp, b, c, sochusodu);
		a.insert(0, temp);
	}
	//sau khi chuỗi a gốc hết kí tự nếu <=> du.size()=a.size() (sau mỗi lần chia chuỗi a được gán bằng chuỗi du) thì nếu chuỗi a != '0' thì thêm dấu . ở chuỗi c
	xoaso0dungdau(a);
	if (a != "0")
		c.push_back('.');
	//CHỉ Lấy ra 5 chữ số sau dấu phẩy (nếu 5 chữ số đều bằng 0 thì lấy tới số khác 0 gần nhất) và làm tròn.
	int i = 0;
	while (i < 5)
	{
		themso0cuoicung(a, 1);
		xoaso0dungdau(a);
		if (a == "0") break;
		xuliphepchia(a, b, c, sochusodu);
		//nếu 5 chữ số đều bằng 0 thì lấy tới số khác 0 gần nhất
		if (i == 4)
		{
			bool KT = true;
			for (int j = c.size() - 1; c[j] != '.'; j--)
			{
				if (c[j] != '0')
				{
					KT = false;
				}
			}
			if (KT == true)
			{
				i--;
			}
		}
		//làm tròn
		if (i == 4)
		{
			themso0cuoicung(a, 1);
			xoaso0dungdau(a);
			if (a == "0") break;
			xuliphepchia(a, b, c, sochusodu);
			if (c[c.size() - 1] - 48 >= 5&&c[c.size()-1]!='9')
			{
				c[c.size() - 2] += 1;
			}
			c.erase(c.size() - 1, 1);
		}
		i++;
	}
	return c;
}

void box(int x, int y, int w, int h, int text_color)// vẽ hôp xung quanh râu ria
{
	textcolor(text_color);
	for (int i = x; i <= x + w; i++)
	{
		gotoXY(i, y);
		cout << char(205);
		gotoXY(i, y + h);
		cout << char(205);
	}
	for (int j = y; j <= y + h; j++)
	{
		gotoXY(x, j);
		cout << char(186);
		gotoXY(x + w, j);
		cout << char(186);
	}
	gotoXY(x, y); cout << char(201);
	gotoXY(x + w, y); cout << char(187);
	gotoXY(x, y + h); cout << char(200);
	gotoXY(x + w, y + h); cout << char(188);
	for (int i = x; i <= x + w; i++)
	{
		gotoXY(i, y + 7);
		cout << char(205);
	}
	gotoXY(x, y + 7); cout << char(204);
	gotoXY(x + w, y + 7); cout << char(185);
	textcolor(12);
	gotoXY(x + 30, y + 1); cout << "=====SIEU MAY TINH CONG TRU NHAN CHIA====";
	gotoXY(x + 6, y + 2) ; cout << "HUONG DAN SU DUNG: ";
	gotoXY(x + 10, y + 3); cout << "1. Nhap so hang thu nhat, ket thuc bang enter.";
	gotoXY(x + 10, y + 4); cout << "2. Nhap phep toan(+,-,*,/), ket thuc bang enter.";
	gotoXY(x + 10, y + 5); cout << "3. Nhap so hang thu hai, ket thuc bang enter va doi ket qua...";
	gotoXY(x + 10, y + 6); cout << "4. Nhan ESC de thoat.";
	gotoXY(0, y + h + 1);
}

bool kiemtraamduong(string s)// nêu so duong tra ve true , am tra ve false
{
	if (s[0] != '-') return true;
	return false;
}

bool check(string s)
{
	if (s[0] != '-' && (s[0] < 48 || s[0]>57))// ki tu dau khong phai la dau'-' cung khong phai so
		return false;
	for (int i = 1; i < s.size(); i++)
		if (s[i] < 48 || s[i]>57)
			return false;
	return true;
}

string Xuli(string a, string b, string& c, string pheptoan)// sau khi nhap 2 so thi xu li tinh toan cac truong hop
{
	chuanhoachuoi(a);
	chuanhoachuoi(b);
	if (!check(a) || !check(b))
		return "MATH ERROR!";
	if (pheptoan == "+")
	{
		if (kiemtraamduong(a) && kiemtraamduong(b))//2 so deu duong
			c = tong(a, b);
		else if (kiemtraamduong(a) && !kiemtraamduong(b))//a duong b am
		{
			c = hieu(a, b);
			b.erase(0, 1);
		}
		else if (!kiemtraamduong(a) && kiemtraamduong(b))//a am b duong
		{
			a.erase(0, 1);
			c = hieu(b, a);
		}
		else// ca 2 am
		{
			a.erase(0, 1);
			b.erase(0, 1);
			c = tong(a, b);
			c.insert(0, "-");
		}
	}
	else if (pheptoan == "-")
	{
		if (kiemtraamduong(a) && kiemtraamduong(b))//2 so deu duong
			c = hieu(a, b);
		else if (kiemtraamduong(a) && !kiemtraamduong(b))//a duong b am
		{
			b.erase(0, 1);
			c = tong(a, b);
		}
		else if (!kiemtraamduong(a) && kiemtraamduong(b))//a am b duong
		{
			a.erase(0, 1);
			c = tong(a, b);
			c.insert(0, "-");
		}
		else// ca 2 am
		{
			a.erase(0, 1);
			b.erase(0, 1);
			c = hieu(b, a);
		}
	}
	else if (pheptoan == "*")
	{
		if (kiemtraamduong(a) && kiemtraamduong(b))//cung duong
		{
			c = nhan(a, b);
		}
		else if (!kiemtraamduong(a) && !kiemtraamduong(b)) //cung am
		{
			a.erase(0, 1);
			b.erase(0, 1);
			c = nhan(a, b);
		}
		else
		{
			if (!kiemtraamduong(a))
				a.erase(0, 1);
			else b.erase(0, 1);
			c = nhan(a, b);
			if (c != "0")
				c.insert(0, "-");
		}
	}
	else if (pheptoan == "/")
	{
		if (kiemtraamduong(a) && kiemtraamduong(b))//cung duong
		{
			c = chia(a, b);
		}
		else if (!kiemtraamduong(a) && !kiemtraamduong(b)) //cung am
		{
			a.erase(0, 1);
			b.erase(0, 1);
			c = chia(a, b);
		}
		else
		{
			if (!kiemtraamduong(a))
				a.erase(0, 1);
			else b.erase(0, 1);
			c = chia(a, b);
			if (c != "0")
				c.insert(0, "-");
		}
	}
	else c = "MATH ERROR!";
	return c;
}

int main()
{
	PlaySound(L"NewAlan_Walker_Faded.wav", NULL, SND_ASYNC);
	ShowCur(false);
	while (true)
	{
		box(2, 1, 100, 20, 10);
		char key_press;
		string pheptoan;
		string a;
		string b;
		string c;
		gotoXY(5, 10);
		cout << "So thu nhat:  ";
		while (true)//Nhap so hang thu nhat
		{
			key_press = _getch();
			int ascii_value = key_press;
			if (ascii_value == 27)// phím ESC
			{
				gotoXY(0, 21);
				return 0;
			}
			else if (ascii_value == 13)// phím enter
				break;
			else if (ascii_value == 8)// phím backspace
			{
				if (a.size() > 0)
				{
					a.erase(a.size() - 1, 1);
					gotoXY(20, 10);
					cout << a << " ";
				}
			}
			else a.push_back(key_press);
			gotoXY(20, 10);
			cout << a;
		}
		gotoXY(5, 11); cout << "Phep toan  :   ";
		getline(cin, pheptoan);
		gotoXY(5, 12);
		cout << "So thu hai :  ";
		while (true)//Nhap so hang thu 2
		{
			key_press = _getch();
			int ascii_value = key_press;
			if (ascii_value == 27)// phím ESC
			{
				gotoXY(0, 21);
				return 0;
			}
			else if (ascii_value == 13)// phím enter
				break;
			else if (ascii_value == 8)// phím backspace
			{
				if (b.size() > 0)
				{
					b.erase(b.size() - 1, 1);
					gotoXY(20, 12);
					cout << b << " ";
				}
			}
			else b.push_back(key_press);
			gotoXY(20, 12);
			cout << b;
		}
		gotoXY(18, 13);
		for (int i = 0; i < 4 + (a.size() > b.size() ? a.size() : b.size()); i++) cout << char(196);
		double start, end;
		start = clock();
		c = Xuli(a, b, c, pheptoan);
		if (c == "MATH ERROR!") 
		{ 
			PlaySound(L"NewES_MM_Error23.wav", NULL, SND_ASYNC); 
			Sleep(1000); 
			PlaySound(L"NewAlan_Walker_Faded.wav", NULL, SND_ASYNC); 
		}
		gotoXY(5, 14); cout << "KQ=            " << c;
		end = clock();
		gotoXY(27, 18);
		cout << "Thoi gian tinh: " << (end - start) / CLOCKS_PER_SEC << "(s)";
		gotoXY(27, 19);
		system("pause");
		system("cls");
	}
	return 1;
}