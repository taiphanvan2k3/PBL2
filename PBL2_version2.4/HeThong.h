#pragma once
#include"Manager.h"
class HeThong :public Menu {
private:
	Manager* manager;
	HashtableUser* listUser;
	HashtableVocab* vocabHeThong;
	HashtableMeaning* vocabMeaning;
	list<wstring>* listContribute;
	void docFileListContribute();
	void ghiFileListContribute();
public:
	bool splitTk_Mk(user* u, wchar_t* str);
	HeThong();
	~HeThong();
	HashtableUser* getListUser();
	void docFileListAccount();
	account* Login(int& phanQuyen);

	//Chức năng đăng kí
	void SignUp();
	void LuuDuLieu();
	void MenuManager();
	void MenuUser(user* u);
	void MAIN();
};