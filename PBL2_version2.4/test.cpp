#include"HeThong.h"
#include<locale>
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

	/*Hashtable<vocab>h;
	vocab* ds;
	int n;
	h.convertToArray(ds, n);*/
	/*list<int>l;
	l.push_back(1);
	l.push_back(2);
	l.erase(1);
	l.display(); */
	HeThong h;
	h.MAIN(); 
}
