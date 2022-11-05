#pragma once 
#include"account.h"
account::account() {
	this->listContribute = NULL;
	this->vocabMeaning = NULL;
	wstrcpy(this->tk, L"");
	wstrcpy(this->mk, L"");
	this->vocabHeThong = new HashtableVocab();
}

account::account(const wchar_t tk[], const wchar_t mk[]) {
	this->setTK(tk);
	this->setMK(mk);
}

void account::setTK(const wchar_t tk[]) {
	wstrcpy(this->tk, tk);
}

void account::setMK(const wchar_t mk[]) {
	wstrcpy(this->mk, mk);
}

/*
listContribute của user,manager sẽ dùng chung vùng địa chỉ này với
listContribute được tạo ra trong class HeThong, để khi user thay thêm
từ vựng hệ thống vào thì manager sẽ thấy được
*/
void account::setListContribute(list<wstring>* listContribute) {
	this->listContribute = listContribute;
}


void account::setVocabMeaning(HashtableMeaning* vocabMeaning) {
	this->vocabMeaning = vocabMeaning;
}

wchar_t* account::getKey() {
	return this->tk;
}

wchar_t* account::getTK() {
	return this->tk;
}

//Vd: taiphanvan2403@gmail.com => trả về taiphanvan2403
wchar_t* account::getSimpleTk() {
	int idx = 0, n = (int)wcslen(this->tk);
	for (int i = 0; i < n; i++) {
		if (this->tk[i] == L'@')
			break;
		idx++;
	}
	wchar_t* res = new wchar_t[idx + 1];
	for (int i = 0; i < idx; i++)
		res[i] = this->tk[i];
	res[idx] = L'\0';
	return res;
}

wchar_t* account::getMK() {
	return this->mk;
}


HashtableVocab* account::getVocabHeThong() {
	return this->vocabHeThong;
}

void account::doiMatKhau() {
	gotoxy(40, 3);
	setcolor(3);
	wcout << L"ĐỔI MẬT KHẨU"<<endl;
	gotoxy(30, 5);
	setcolor(7);
	wcout << L"Tài khoản:";
	setcolor(6);
	wcout << this->tk << endl;
	setcolor(7);
	gotoxy(30, 6);
	wchar_t oldPass[30];
	wcout << L"Mật khẩu cũ:";
	bool checkOk = true;
	setcolor(6);
	int cnt = 0;
	do {
		if (!checkOk) {
			gotoxy(43, 6);
			setcolor(4);
			wcout << L"mật khẩu không khớp với mật khẩu hiện tại!!!";
			Sleep(800);
			for (int i = 0; i < 45; i++) {
				gotoxy(43 + i, 6);
				wcout << L" ";
			}
		}
		checkOk = false;
		cnt++;
		setcolor(6);
		getMKInput(oldPass, 43, 6);
	} while (wstrcmp(oldPass,this->mk) !=0 && cnt<3);
	if (cnt == 3) {
		system("cls");
		setcolor(3);
		wcout << L"\t\t\t\tBạn đã nhập sai mật khẩu cũ 3 lần. \n\t\t\tHãy cố nhớ lại mật khẩu cũ trước khi tiến hành thay đổi.\n";
		setcolor(7);
		return;
	}
	wchar_t newPass[30];
	setcolor(7);
	gotoxy(30, 7);
	wcout << L"Mật khẩu mới:";
	setcolor(6);
	getMKInput(newPass, 30+14, 7);
	setcolor(7);
	gotoxy(30, 8);
	wcout << L"Xác nhận:";
	wchar_t confirm[30];
	bool check = true;
	do {
		if (!check) {
			gotoxy(40, 8);
			setcolor(4);
			wcout << L"mật khẩu xác nhận không khớp!!!";
			Sleep(500);
			for (int i = 0; i < 32; i++) {
				gotoxy(40+i, 8);
				wcout << L" ";
			}
		}
		setcolor(6);
		gotoxy(40, 8);
		getMKInput(confirm,40, 8);
		check = false;
	} while (wstrcmp(confirm, newPass) !=0);
	setcolor(7);
	gotoxy(30, 10);
	setcolor(3);
	wstrcpy(this->mk, confirm);
	wcout << L"Đã thay đổi mật khẩu thành công !"<<endl;
	setcolor(7);
}

void account::InTuVungHeThong() {
	this->vocabHeThong->InTuVungTangDan();
}

void account::xemThongTinTaiKhoan() {
	wcout << "\t\t" << left << setw(30) << this->getTK() << "\t\t" << this->getMK() << endl;
}


