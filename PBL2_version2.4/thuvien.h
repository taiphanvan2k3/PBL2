#pragma once
#include<iostream>
#include <wchar.h>
#include <stdlib.h>// dùng cho việc random
#include <time.h>// dùng cho việc random
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include<string>
#include<Windows.h>
#include<iomanip>
#include"conio.h" // chứa _kbhit()
using namespace std;
int wstrcmp(wchar_t a[], wchar_t b[]);
int wstrcmp(wchar_t a[], const wchar_t b[]);
int wstrcmp(wchar_t a[], wstring b);
int wstricmp(wchar_t a[], wchar_t b[]);
void wstrcat(wchar_t dest[], const wchar_t src[]);
wchar_t wtolower(wchar_t a);
wchar_t wtolower(const wchar_t a);
void convert(wchar_t str[]);
void convert(wstring& str);
void convertWstringToChar(char dest[], wstring src);
void wstrcpy(wchar_t dest[], wchar_t src[]);
void wstrcpy(wchar_t dest[], wstring src);
void wstrcpy(wchar_t dest[], const wchar_t src[]);
//Xoá khoảng trắng 2 đầu
void trim(wchar_t str[]);
void trim(wstring& str);
//Xoá khoảng trống dư thừa ở giữa các từ
void deleteSpace(wchar_t str[]);
void deleteSpace(wstring& str);
//Định dạng lại input
void formatInput(wchar_t str[]);
void formatInput(wstring& str);
void setPage(int* numOfPage, int n);
//Đồ hoạ
//Vì mục đích làm cho chương trình sinh động nên đã sử dụng 4 hàm setcolor,textcolor,gotoxy,Showcur
void setcolor(int color);
void textcolor(int text_color, int backgound_color);
void gotoxy(int x, int y);
//Bật,tắt hiển thị con trỏ chuột
void ShowCur(int CursorVisibility);
//Lấy mật khẩu input và in ra dưới dạng *
void getMKInput(wchar_t mk[], int x, int y);
//Note:tenplate: chỉ được định nghĩa trong file.h
template<class T>
void deleteLinkList(T* head) {
	if (head == NULL)
		return;
	if (head->getNext())
		deleteLinkList(head->getNext());
	delete head;
}


template<class T>
inline void shuffle(T arr[], int n) {
	srand((unsigned int)time(NULL));
	for (int i = n - 1; i > 0; i--) {
		int pos = rand() % (i + 1);
		swap(arr[pos], arr[i]);
	}
}

template<class T1, class T2>
inline bool operator == (T1 s1, T2 s2) {
	int n1 = s1.length(), n2 = s2.length();
	if (n1 != n2)
		return false;
	for (int i = 0; i < n1; i++)
		if (s1[i] != s2[i])
			return false;
	return true;
}

template<class T>
void quicksort(T arr[], int l, int r) {
	if (l < r) {
		int i = l, j = r;
		T p = arr[(i + j) / 2];
		while (i < j) {
			while (arr[i] < p)
				i++;
			while (arr[j] > p)
				j--;
			if (i <= j) {
				swap(arr[i], arr[j]);
				i++;
				j--;
			}
		}
		quicksort(arr, i, r);
		quicksort(arr, l, j);
	}
}
