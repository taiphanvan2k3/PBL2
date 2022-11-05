#include"Menu.h"

Menu::Menu() {

}

void Menu::box(wstring task, int x, int y, int h, int w, int t_color, int b_color) {
	textcolor(t_color, 0);
	for (int ix = x; ix <= x + w; ix++) {
		gotoxy(ix, y);
		wprintf(L"─");
		gotoxy(ix, y + h);
		wprintf(L"─");
	}
	for (int iy = y; iy <= y + h; iy++) {
		gotoxy(x, iy);
		wprintf(L"│");
		gotoxy(x + w, iy);
		wprintf(L"│");
	}
	gotoxy(x, y);
	wprintf(L"┌");
	gotoxy(x, y + h);
	wprintf(L"└");
	gotoxy(x + w, y);
	wprintf(L"┐");
	gotoxy(x + w, y + h);
	wprintf(L"┘");
	thanh_sang2(task, x, y, w, h, t_color, b_color);
}

void Menu::thanh_sang2(wstring str, int x, int y, int w, int h, int t_color, int b_color) {
	int y_middle = y + h / 2;
	for (int yy = y + 1; yy < y + h; yy++) {
		textcolor(t_color, b_color);
		if (yy == y_middle) {
			int n = (int)str.length();
			int id = 0;
			for (int xx = x + 1; xx < x + w; xx++) {
				gotoxy(xx, yy);
				if (id < n) {
					textcolor(10, b_color);
					wcout << str[id++];
				}
				else wprintf(L" ");
			}
		}
		else {
			for (int xx = x + 1; xx < x + w; xx++) {
				gotoxy(xx, yy);
				wprintf(L" ");
			}
		}
	}
	//set lại để tránh màn hình console bị in ra full màu
	textcolor(7, 0);
}

void Menu::n_box(wstring task[], int x, int y, int w, int b) {
	int h = 2;
	int t_color = 3, b_color = 0;
	//t_color: màu chữ
	//b_color: màu nền
	//b_color_curr: màu nền cho hộp đang thao tác
	int b_color_curr = 3;
	for (int i = 0; i < b; i++)
		box(task[i], x, y + i * 2, h, w, t_color, b_color);
	textcolor(3, 0);
	for (int i = 1; i < b; i++) {
		gotoxy(x, y + i * 2);
		wprintf(L"├");
		gotoxy(x + w, y + i * 2);
		wprintf(L"┤");
	}
}
void Menu::in_tieu_de(wstring task[], int x, int y, int w, int b) {
	system("cls");
	setcolor(14);
	gotoxy(48, 2);
	wprintf(L" =========MENU=========\t\n");
	n_box(task, x, y, w, b);
	setcolor(14);
}

void Menu::updateTask(wstring task[], int th) {
	if (th == 1) {
		wstring temp;
		temp.resize(10, L' ');
		task[0] = temp + L"Đăng nhập.";
		temp.resize(6, L' ');
		task[1] = temp + L"Đăng kí tài khoản.";
		task[2] = L"  Thoát khỏi chương trình.";
	}
	else if (th == 2) {
		//task manager
		task[0] = L"Load từ vựng từ file lên hệ thống.";
		task[1] = L"Xem từ vựng hệ thống.";
		task[2] = L"Thêm thủ công từ vựng vào từ điển hệ thống.";
		task[3] = L"Chỉnh sửa thông tin từ vựng.";
		task[4] = L"Xoá từ vựng khỏi từ điển hệ thống";
		task[5] = L"Xem và thêm từ vựng đóng góp vào từ điển";
		task[6] = L"In thông tin danh sách người dùng.";
		task[7] = L"Xem thông tin của một user.";
		task[8] = L"Xoá tài khoản user.";
		task[9] = L"Đổi mật khẩu.";
		task[10] = L"Đăng xuất.";
	}
	else {
		//task user
		task[0] = L"Tra cứu từ điển Anh-Việt.";
		task[1] = L"Tra cứu từ điển Việt-Anh.";
		task[2] = L"Thêm từ vựng vào album cá nhân.";
		task[3] = L"Xem từ điển hệ thống.";
		task[4] = L"Xem từ vựng album cá nhân.";
		task[5] = L"Xoá từ vựng ra khỏi album.";
		task[6] = L"Ôn tập kiến thức.";
		task[7] = L"Đổi mật khẩu.";
		task[8] = L"Đăng xuất.";
	}
}