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

void account::InTuVungHeThong() {
	this->vocabHeThong->InTuVungTangDan();
}

void account::xemThongTinTaiKhoan() {
	wcout << "\t\t" << left << setw(30) << this->getTK() << "\t\t" << this->getMK() << endl;
}


