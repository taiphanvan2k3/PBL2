#include"thuvien.h"
int wstrcmp(wchar_t a[], wchar_t b[]) {
	int n1 = (int)wcslen(a);
	int n2 = (int)wcslen(b);
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
	int n1 = (int)wcslen(a);
	int n2 = (int)wcslen(b);
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
	int n1 = (int)wcslen(a);
	int n2 = (int)b.length();
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
	int n1 = (int)wcslen(a);
	int n2 = (int)wcslen(b);
	int n = min(n1, n2);
	for (int i = 0; i < n; i++) {
		char x = (char)wtolower(a[i]), y = (char)wtolower(b[i]);
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
	int n1 = (int)wcslen(dest);
	int n2 = (int)wcslen(src);
	for (int i = 0; i < n2; i++)
		dest[n1++] = src[i];
	dest[n1] = L'\0';
}

void convert(wchar_t str[]) {
	setlocale(LC_ALL, "");
	int n = (int)wcslen(str);
	for (int i = 0; i < n; i++)
		str[i] = towlower(str[i]);
}

void convert(wstring& str) {
	setlocale(LC_ALL, "");
	int n = (int)str.length();
	for (int i = 0; i < n; i++)
		str[i] = towlower(str[i]);
}

void convertWstringToChar(char dest[], wstring src) {
	int n = (int)src.length();
	for (int i = 0; i < n; i++)
		dest[i] = src[i] - L'a' + 'a';
	dest[n] = '\0';
}

void wstrcpy(wchar_t dest[], wchar_t src[]) {
	int n = (int)wcslen(src);
	for (int i = 0; i < n; i++)
		dest[i] = src[i];
	dest[n] = L'\0';
}

void wstrcpy(wchar_t dest[], const wchar_t src[]) {
	int n = (int)wcslen(src);
	for (int i = 0; i < n; i++)
		dest[i] = src[i];
	dest[n] = L'\0';
}

void wstrcpy(wchar_t dest[], wstring src) {
	int n = (int)src.length();
	for (int i = 0; i < n; i++)
		dest[i] = src[i];
	dest[n] = L'\0';
}

void trim(wchar_t str[]) {
	int idx = 0, l = 0, r = (int)wcslen(str) - 1;
	while (str[l] == L' ' || str[l] == '\t')
		l++;
	while (str[r] == L' ' || str[r] == '\t')
		r--;
	if (l > 0 || r < wcslen(str) - 1) {
		int n = r - l + 1;
		for (int i = l; i <= r; i++)
			str[idx++] = str[i];
		str[n] = L'\0';
	}
}

void trim(wstring& str) {
	int idx = 0, l = 0, r = (int)str.length() - 1;
	while (str[l] == L' ' || str[l] == '\t')
		l++;
	while (str[r] == L' ' || str[r] == '\t')
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
	int n = (int)wcslen(str);
	for (int i = 0; i < n; i++) {
		bool check = true;
		while (i < n && (str[i] == L' ' || str[i] == L'\t')) {
			check = false;
			i++;
		}
		if (i < n) {
			if (!check)
				str[idx++] = L' ';
			str[idx++] = str[i];
		}
	}
	str[idx++] = L'\0';
}
void deleteSpace(wstring& str) {
	wstring res = L"";
	int n = (int)str.size();
	for (int i = 0; i < n; i++) {
		bool check = true;
		while (str[i] == L' ' || str[i] == L'\t') {
			check = false;
			i++;
		}
		if (i < n) {
			if (!check)
				res += L" ";
			res += str[i];
		}
	}
	str = res;
}

void formatInput(wchar_t str[]) {
	trim(str);
	deleteSpace(str);
	convert(str);
}

void formatInput(wstring& str) {
	trim(str);
	deleteSpace(str);
	convert(str);
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

void getMKInput(wchar_t mk[], int x, int y,int th) {
	//th=0: ứng với việc đăng nhập
	//th=1: ứng với việc đăng kí
	int num_mk = 0;
	bool pressed = false;
	while (num_mk + 1 < 30) {
		gotoxy(x + num_mk, y);
		wchar_t c = _getch();
		//Phím enter
		if (c == 13) {
			if (num_mk >= 5 || (th==0 && num_mk>=1)) {
				mk[num_mk] = '\0';
				break;
			}
			else {
				gotoxy(x, y);
				if (th == 0) {
					wcout << L"mật khẩu đăng nhập không được bỏ trống.";
					Sleep(1000);
					gotoxy(x, y);
					for (int i = 0; i < 40; i++)
						wcout << L" ";
					gotoxy(x, y);
				}
				else {
					wcout << L"mật khẩu phải tối thiểu 5 kí tự.";
					Sleep(1000);
					gotoxy(x, y);
					for (int i = 0; i < 33; i++)
						wcout << L" ";
					gotoxy(x, y);
				}
				if (pressed) {
					setcolor(2);
					mk[num_mk] = '\0';
					wcout << mk;
					gotoxy(x, y + 1);
					wcout << L" ";
				}
				else {
					setcolor(6);
					for (int i = 0; i < num_mk; i++)
						wcout << L"•";
				}
			}
		}
		//Phím delete
		else if (c == 8) {
			if (num_mk > 0) {
				num_mk--;
				gotoxy(x + num_mk, y);
				wcout << L" ";
			}
		}
		//Khi nhấn ctrl S =>show mật khẩu
		else if (c == 19) {
			pressed = !pressed;
			gotoxy(x, y);
			if (pressed) {
				setcolor(2);
				mk[num_mk] = '\0';
				wcout << mk;
				gotoxy(x, y + 1);
				wcout << L" ";
			}
			else {
				setcolor(6);
				for (int i = 0; i < num_mk; i++)
					wcout << L"•";
			}
		}
		else {
			mk[num_mk++] = c;
			if (pressed) {
				setcolor(2);
				wcout << c;
			}
			else {
				setcolor(6);
				wcout << L"•";
			}
				
		}
	}
}

void waitForType() {
	ShowCur(0);
	int c = _getch();
}