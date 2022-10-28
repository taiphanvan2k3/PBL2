#include"thuvien.h"
int wstrcmp(wchar_t a[], wchar_t b[]) {
	int n1 = wcslen(a);
	int n2 = wcslen(b);
	int n = min(n1, n2);
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}
	if (n1 == n2)
		return 0;
	else if (n1 > n2)
		return 1;
	return -1;
}

int wstrcmp(wchar_t a[], const wchar_t b[]) {
	int n1 = wcslen(a);
	int n2 = wcslen(b);
	int n = min(n1, n2);
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}
	if (n1 == n2)
		return 0;
	else if (n1 > n2)
		return 1;
	return -1;
}

int wstrcmp(wchar_t a[], wstring b) {
	int n1 = wcslen(a);
	int n2 = b.length();
	int n = min(n1, n2);
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}
	if (n1 == n2)
		return 0;
	else if (n1 > n2)
		return 1;
	return -1;
}

int wstricmp(wchar_t a[], wchar_t b[]) {
	int n1 = wcslen(a);
	int n2 = wcslen(b);
	int n = min(n1, n2);
	for (int i = 0; i < n; i++) {
		char x = wtolower(a[i]), y = wtolower(b[i]);
		if (x > y)
			return 1;
		else if (x < y)
			return -1;
	}
	if (n1 == n2)
		return 0;
	else if (n1 > n2)
		return 1;
	return -1;
}
wchar_t wtolower(wchar_t c) {
	if (c >= L'A' && c <= L'Z')
		c += 32;
	return c;
}

void wstrcat(wchar_t dest[], const wchar_t src[]) {
	int n1 = wcslen(dest);
	int n2 = wcslen(src);
	for (int i = 0; i < n2; i++)
		dest[n1++] = src[i];
	dest[n1] = L'\0';
}

void convert(wchar_t str[]) {
	int n = wcslen(str);
	for (int i = 0; i < n; i++)
		str[i] = wtolower(str[i]);
}

void convert(wstring& str) {
	int n = str.length();
	for (int i = 0; i < n; i++)
		str[i] = wtolower(str[i]);
}

void convertWstringToChar(char dest[], wstring src) {
	int n = src.length();
	for (int i = 0; i < n; i++)
		dest[i] = src[i] - L'a' + 'a';
	dest[n] = '\0';
}

void wstrcpy(wchar_t dest[], wchar_t src[]) {
	int n = wcslen(src);
	for (int i = 0; i < n; i++)
		dest[i] = src[i];
	dest[n] = L'\0';
}

void wstrcpy(wchar_t dest[], const wchar_t src[]) {
	int n = wcslen(src);
	for (int i = 0; i < n; i++)
		dest[i] = src[i];
	dest[n] = L'\0';
}

void wstrcpy(wchar_t dest[], wstring src) {
	int n = src.length();
	for (int i = 0; i < n; i++)
		dest[i] = src[i];
	dest[n] = L'\0';
}

void trim(wchar_t str[]) {
	int idx = 0, l = 0, r = wcslen(str) - 1;
	while (str[l] == L' ')
		l++;
	while (str[r] == L' ')
		r--;
	if (l > 0 || r < wcslen(str) - 1) {
		int n = r - l + 1;
		for (int i = l; i <= r; i++)
			str[idx++] = str[i];
		str[n] = L'\0';
	}
}

void trim(wstring& str) {
	int idx = 0, l = 0, r = str.length() - 1;
	while (str[l] == L' ')
		l++;
	while (str[r] == L' ')
		r--;
	if (l > 0 || r < str.length() - 1) {
		int n = r - l + 1;
		for (int i = l; i <= r; i++)
			str[idx++] = str[i];
		str.resize(n);
	}
}

void deleteSpace(wchar_t str[]) {
	int idx = 0;
	int n = wcslen(str);
	for (int i = 0; i < n; i++) {
		if (str[i] == L' ') {
			while (i + 1 < n && str[i + 1] == L' ')
				i++;
		}
		str[idx++] = str[i];
	}
	str[idx] = L'\0';
}
void deleteSpace(wstring& str) {
	int idx = 0;
	int n = str.length();
	for (int i = 0; i < n; i++) {
		if (str[i] == L' ') {
			while (i + 1 < n && str[i + 1] == L' ')
				i++;
		}
		str[idx++] = str[i];
	}
	str.resize(idx);
}

void formatInput(wchar_t str[]) {
	trim(str);
	deleteSpace(str);
}

void formatInput(wstring& str) {
	trim(str);
	deleteSpace(str);
}

void setPage(int* numOfPage, int n) {
	int i = 1;
	while (n != 0) {
		if (n >= 20) {
			numOfPage[i++] = 20;
			n -= 20;
		}
		else numOfPage[i] = n, n = 0;
	}
}
//Đồ hoạ:
void setcolor(int color)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

void textcolor(int text_color, int backgound_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

//Bật,tắt hiển thị con trỏ chuột
void ShowCur(int CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;
	SetConsoleCursorInfo(handle, &ConCurInf);
}