#pragma once
#pragma once // tránh đụng độ thư viện khi gọi chồng file lên nhau
#include <stdio.h>
#include<iostream>
#include <conio.h>
#include<ctime> /* thư viện hỗ trợ về thời gian thực */
#include "windows.h" // thư viện này bá đạo lắm nhé - chứa nhiều đồ chơi nek - cứ tìm hiểu dần dần s
//======= lấy tọa độ x của con trỏ hiện tại =============
#define KEY_NONE	-1
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= lấy tọa độ y của con trỏ hiện tại =======
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= đặt màu cho chữ (không nền)=========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= trả về mã phím người dùng bấm =========
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}
		return key;
	}
	else
	{
		return KEY_NONE;
	}

	return KEY_NONE;
}


//Hàm thay đổi kích cỡ Console
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

//Hàm tô màu có nền
void textcolor(int x)// x la chi so mau(1-255)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}




//Hàm xóa màn hình
void ClearCreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// Hàm bắt sự kiền bàn phím
//Phím Enter : 13
//Phím ESC : 27
//Phím Tab : 9
//Mũi tên lên : 72
//Mũi tên xuống : 80
//Mũi tên sang trái : 75
//Mũi tên sang phải : 77
//Phím cách : 32

void checkkeypress()
{
	char key_press;
	int ascii_value;
	std::cout << "\n\t\tNhap phim bat ky de kiem tra ma ASCII\n\t\t\An ESC de thoat\n\n\n";
	while (1)
	{
		key_press = _getch();
		ascii_value = key_press;
		if (ascii_value == 27) // For ESC
			break;
		std::cout << "Ban nhap phim-> \" " << key_press << " \" Gia tri ASCII =  " << ascii_value << "\n";
	}
}












