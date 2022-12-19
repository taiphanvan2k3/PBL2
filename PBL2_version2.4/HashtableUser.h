#pragma once
#include"Hashtable.cpp"
#include"user.h"
class HashtableUser:public Hashtable<user> {
public:
	HashtableUser();
	~HashtableUser(){}
	void insert(user* x);

	void deleteUser(wchar_t tk[]);

	void displayListUser();

	void xemTaiKhoanUser();

	/*Đồng bộ từ vựng, khi manager sửa 1 từ vựng nào mà user nào có thì cập nhật lại
	từ vựng đó của user*/
	void syncVocab(vocab* updatedVocab);

	//Ghi tk,mk vào lại chính file mà ta đã đọc thông tin tk,mk user lúc chạy chương trình
	void ghiFileTkMk(wchar_t* tkAdmin,wchar_t* mkAdmin);
	//Sai
	/*
		void ghiFileAlbumUser() {
		node<int>* l = listId.getHead();
		while (l != NULL) {
			user* tam = heads[l->data];
			while (tam != NULL) {
				tam->ghiFileAlbum();
				tam = tam->next;
			}
			l = l->next;
		}
	}
	*/
};