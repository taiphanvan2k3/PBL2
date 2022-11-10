#pragma once
#include"Manager.h"
//#include"Menu.h"
class HeThong :public Menu {
private:
	bool checkReadContributedVocab = false;
	Manager* manager;
	HashtableUser* listUser;
	HashtableVocab* vocabHeThong;
	HashtableMeaning* vocabMeaning;
	list<wstring>* listContribute;
	void docFileListContribute();
	void ghiFileListContribute();
public:
	void splitTk_Mk(user* u, wchar_t* str);
	HeThong();
	~HeThong();
	HashtableUser* getListUser();
	void docFileListAccount();
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