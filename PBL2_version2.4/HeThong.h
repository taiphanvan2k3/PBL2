#pragma once
#include"Manager.h"
#include"Menu.h"
class HeThong :public Menu {
private:
	Manager* manager;
	HashtableUser* listUser;
	HashtableVocab* vocabHeThong;
	HashtableMeaning* vocabMeaning;
	list<wstring>* listContribute;
public:
	void splitTk_Mk(user* u, wchar_t* str);
	HeThong();
	~HeThong();
	HashtableUser* getListUser();
	void docFileListAccount();

	//Chức năng đăng nhập
	void getMkInput(wchar_t mk[], int x, int y);
	account* Login(int& phanQuyen);

	//Chức năng đăng kí
	void SignUp();

	/*Chức năng này sẽ được gọi khi tại menu chung thực hiện tuỳ chọn thoát
	Tiến hành lưu toàn bộ từ vựng hệ thống, tk-mk user, album từ vựng của từng user xuống file
	Từ vựng hệ thống và album từ vựng (user) đều là class HashtableVocab 
	=> Xây dựng phương thức ghi file trên HashtableVocab*/
	void LuuDuLieu();
	void MenuManager();
	void MenuUser(user* u);
	void MAIN();
};