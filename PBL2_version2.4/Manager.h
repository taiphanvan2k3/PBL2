#pragma once
#include"HashtableUser.h"
#include"HashtableVocab.h"
class Manager :public account {
private:
	HashtableUser* listUser;
public:
	Manager();

	void setDefaultAccount();

	void setListUser(HashtableUser* listUser);

	/*Th=1 ứng với trường hợp admin đọc thêm từ vựng từ 1 file khác
	Th=2 ứng với trường hợp lúc chạy chương trình thì sẽ tự động
	đọc từ vựng lưu ở file phienam.txt lưu vào vocabHeThong*/
	void docFileDanhSachTuVung(int phanQuyen);

	/*themTuVung này là phương thức thêm từ vựng vào vocabHeThong chỉ có ở Manager
	th=1: ứng với lúc manager chọn chức năng nhập thủ công 
	th=0: ứng với lúc manager chọn chức năng thêm từ vựng đóng góp*/
	void themTuVung(vocab* v, int th = 1);

	void xoaTuVung();

	//Chức năng này chỉ có ở manager vì chỉnh sửa vào vocabHeThong
	void chinhSuaTuVung();

	void InTuVungDongGop();

	void themTuVungDongGop();

	void searchUser();
	void deleteUser();

	//In ra thông tin tk,mk của các user
	void displayListUser();

	//In ra danh sách các tài khoản của user
	void displayTKUser();
};