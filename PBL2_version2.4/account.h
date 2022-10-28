#pragma once 
#include"thuvien.h"
#include"HashtableVocab.h"
#include"HashtableMeaning.h"
class account {
private:
	wchar_t tk[50];
	wchar_t mk[50];
protected:
	HashtableVocab* vocabHeThong;
	//vocabMeaning này dùng để tra cứu từ điển Việt-Anh
	HashtableMeaning* vocabMeaning;
	list<wstring>* listContribute;
public:
	account();

	account(const wchar_t tk[], const wchar_t mk[]);

	void setTK(const wchar_t tk[]);

	void setMK(const wchar_t mk[]);

	//listContribute của user,manager sẽ dùng chung vùng địa chỉ này với listContribute được 
	// tạo ra trong class HeThong, để khi user thay thêm từ vựng hệ thống vào thì manager sẽ thấy được

	void setListContribute(list<wstring>* listContribute);

	//void setVocabMeaning(HashtableMeaning* vocabMeaning);
	void setVocabMeaning(HashtableMeaning* vocabMeaning);

	wchar_t* getKey();
	wchar_t* getTK();

	//Vd: taiphanvan2403@gmail.com => trả về taiphanvan2403
	wchar_t* getSimpleTk();

	wchar_t* getMK();


	//HashtableVocab* getVocabHeThong();
	HashtableVocab* getVocabHeThong();
	void InTuVungHeThong();

	void xemThongTinTaiKhoan();
	//Các phương thức ảo sau tuỳ thuộc vào đối tượng mà có cách định nghĩa khác nhau
	virtual void themTuVung(vocab* v, int th = 1) = 0;
	virtual void xoaTuVung() = 0;
};