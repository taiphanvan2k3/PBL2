#include"HeThong.h"
int main() {
	int t;
	t = _setmode(_fileno(stdout), _O_U16TEXT); //cần để viết được ký tự utf-16 ra stdout
	t = _setmode(_fileno(stdin), _O_U16TEXT);//cần để viết được ký tự utf-16 ra stdin
	/*HeThong h;
	int phanQuyen;
	account* ac = h.Login(phanQuyen);
	if (ac != NULL) {
		if (phanQuyen == 1) {
			Manager* m = (Manager*)ac;
			m->displayListUser();
		}
		else {
			user* u = (user*)ac;
			u->gameChonDapAnDung();
		}
	}*/

	/*
	 L"r,ccs=UTF-16LE"
	this->setTK(L"Admin001@gmail.com");
	this->setMK(L"@@admin001");
	*/
	//[ˈfʊt.bɑːl]
	HeThong h;
	h.MAIN(); 
}
