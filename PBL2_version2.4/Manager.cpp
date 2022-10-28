//#pragma once
#include"Manager.h"
Manager::Manager() {
	this->listUser = new HashtableUser;
	this->setDefaultAccount();
}

void Manager::setDefaultAccount() {
	this->setTK(L"Admin001@gmail.com");
	this->setMK(L"@@admin001");
}


void Manager::setListUser(HashtableUser* listUser) {
	this->listUser = listUser;
}

/*
th=1 ứng với trường hợp admin đọc thêm từ vựng từ 1 file khác
th=2 ứng với trường hợp lúc chạy chương trình thì sẽ tự động
đọc từ vựng lưu ở file phienam.txt lưu vào vocabhethong
*/
void Manager::docFileDanhSachTuVung(int phanQuyen) {
	FILE* f = NULL;
	FILE** pFile = &f;
	//Manager có thể tuỳ chọn
	if (phanQuyen == 1) {
		setcolor(3);
		wprintf(L"Dữ liệu về từ vựng đang được lưu trong project với tên:");
		setcolor(4);
		wprintf(L"advancedvocab.txt\n");
		setcolor(3);
		wprintf(L"Nhập tên file mà bạn muốn đọc:");
		wchar_t str[100];
		setcolor(6);
		_getws_s(str);
		wcscat_s(str, L".txt");
		_wfopen_s(pFile, str, L"r,ccs=UTF-16LE");
		while (*pFile == NULL) {
			system("cls");
			setcolor(3);
			wprintf(L"Dữ liệu về từ vựng đang được lưu trong project với tên:");
			setcolor(4);
			wprintf(L"advancedvocab.txt\n");
			setcolor(3);
			wprintf(L"Mời bạn nhập lại tên file cho đúng:");
			setcolor(6);
			_getws_s(str);
			wcscat_s(str, L".txt");
			_wfopen_s(pFile, str, L"r,ccs=UTF-16LE");
		}
	}
	else _wfopen_s(pFile, L"phienam.txt", L"r,ccs=UTF-16LE");
	if (f == NULL)
		return;
	int cnt = 0;
	while (!feof(f)) {
		cnt++;
		vocab* a = new vocab();
		a->doc_file_1_vocab(f);
		this->vocabHeThong->insert(a);
		this->vocabMeaning->insert(a);
	}

	if (phanQuyen == 1) {
		setcolor(2);
		system("cls");
		wcout << L"Đang nạp " << cnt << L" từ vựng từ điển." << endl;
		for (int i = 1; i <= cnt; i++) {
			wcout << L"Loading " << i * 100 / cnt << " %" << endl;
			Sleep(100);
		}
		wcout << L"Hoàn tất." << endl;
		setcolor(7);
		fclose(f);
	}
}


//themTuVung này là phương thức thêm từ vựng vào vocabHeThong chỉ có ở Manager
//th=1: ứng với lúc manager chọn chức năng nhập thủ công 
//th=0: ứng với lúc manager chọn chức năng thêm từ vựng đóng góp
void Manager::themTuVung(vocab* v, int th) {
	wchar_t str[30];
	if (th == 1) {
		wprintf(L"Bạn cần điền các thông tin sau để hoàn tất việc thêm từ vựng vào TỪ ĐIỂN:\n");
		wprintf(L"Mời bạn nhập từ vựng:");
		_getws_s(str);
		formatInput(str);
		convert(str);
	}
	if (str == NULL)
		return;
	vocab* tam = this->vocabHeThong->search(str);
	if (tam != NULL)
		wprintf(L"Từ vựng bạn muốn thêm đã có trong từ điển rồi.\n");
	else {
		if (th)
			v->setEnglish(str);
		v->nhap_tt_1_vocab();
		this->vocabHeThong->insert(v);
		this->vocabMeaning->insert(v);
	}
}

void Manager::xoaTuVung() {
	wchar_t str[50];
	wcout << L"Nhập từ vựng bạn cần XOÁ:";
	_getws_s(str);
	formatInput(str);
	this->vocabHeThong->deleteVocab(str);
}

//Chức năng này chỉ có ở manager vì chỉnh sửa vào vocabHeThong
void Manager::chinhSuaTuVung() {
	wchar_t str[50];
	setcolor(3);
	wcout << L"Nhập từ vựng bạn cần CHỈNH SỬA:";
	setcolor(6);
	_getws_s(str);
	trim(str);
	vocab* tam = this->vocabHeThong->search(str);
	if (tam == NULL) {
		setcolor(4);
		wcout << L"Từ vựng mà bạn đang muốn chỉnh sửa hiện tại chưa có trong TỪ ĐIỂN hệ thống." << endl;
	}
	else {
		setcolor(3);
		wcout << L"Từ vựng trước khi thay đổi:";
		setcolor(6);
		tam->display(1);
		wcout << endl;
		vocab* newVocab = new vocab;
		setcolor(3);
		wcout << L"*Bạn có cảm thấy từ vựng này của bạn có vấn đề về phần ENGLISH không?" << endl;
		wcout << L"->Nhập đổi mới từ vựng nếu bạn muốn chỉnh sửa!" << endl;
		wcout << L"->Nhập từ vựng mới:";
		wchar_t str[30];
		setcolor(6);
		_getws_s(str);
		setcolor(7);
		formatInput(str);
		convert(str);
		//Nếu người dùng nhập vào từ vựng có eng khác với eng của tam tức là str khác rỗng
		//Do đó ta cập nhật lại phần eng của newVocab
		if (wstrcmp(str, L"") != 0)
			newVocab->setEnglish(str);
		//Nếu người dùng nhấn enter=>str là rỗng => str cũng chính là eng cũ nên ta wstrcpy để gán cho str
		else wstrcpy(str, tam->getEnglish());
		newVocab->nhap_tt_1_vocab();
		if (wstrcmp(tam->getEnglish(), str) != 0) {
			//Khi chỉnh sửa luôn về trường eng của tam thì ta phải xoá tam ra khỏi bảng băm
			//rồi insert vào newVocab tương ứng với từ vựng mới
			this->vocabHeThong->deleteVocab(tam->getEnglish());
			this->vocabHeThong->insert(newVocab);
			this->vocabMeaning->insert(newVocab);
			//Xem xét việc this->vocabMeaning->insert(newVocab);
		}
		else {
			/*Chú ý ở đây dùng phương thức updateDate chứ ko dùng *tam=*newVocab
			vì có thể newVocab có phần eng là rỗng mà bây giờ ta đi gán như vậy sẽ dẫn đến sai*/
			tam->updateData(newVocab);
			this->vocabMeaning->insert(tam);
			//Đồng bộ 
			if (this->listUser != NULL)
				this->listUser->syncVocab(tam);
		}
	}
}

void Manager::InTuVungDongGop() {
	wcout << L"Danh sách từ vựng người dùng đã đóng góp:" << endl;
	if (this->listContribute->getSize() == 0)
		wcout << L"->Danh sách đang rỗng" << endl;
	else this->listContribute->display();
}

void Manager::themTuVungDongGop() {
	wchar_t eng[30];
	do {
		vocab* v = new vocab();
		system("cls");
		InTuVungDongGop();
		wcout << L"Mời bạn chọn từ vựng muốn thêm từ danh sách đóng góp:";
		_getws_s(eng);
		convert(eng);
		v->setEnglish(eng);
		//Thêm xong thì xoá từ đó khỏi danh sách đóng góp
		this->listContribute->erase(eng);
		themTuVung(v, 0);
	} while (wstrcmp(eng, L"") != 0 && this->listContribute->getSize() != 0);
}

void Manager::searchUser() {
	setcolor(3);
	wcout << L"Nhập email user bạn muốn tìm kiếm:";
	setcolor(7);
	wchar_t email[50];
	wcin >> email;
	int c = (int)getwchar();
	user* res = this->listUser->search(email);
	if (res) {
		system("cls");
		setcolor(3);
		wcout << L"\t\t\tThông tin tài khoản user:\n\n";
		setcolor(7);
		wcout << L"\t->Tài khoản:" << res->getTK() << endl;
		wcout << L"\t->Mật khẩu:" << res->getMK() << endl;
	}
	else {
		setcolor(6);
		wcout << L"->Không tìm thấy thông tin người dùng bạn muốn tìm kiếm." << endl;
		setcolor(7);
	}
}

void Manager::deleteUser() {
	setcolor(3);
	wcout << L"Nhập tài khoản user bạn cần muốn xoá:";
	wchar_t tk[50];
	setcolor(7);
	_getws_s(tk);
	this->listUser->deleteUser(tk);
}

//In ra thông tin tk,mk của các user
void Manager::displayListUser() {
	this->listUser->displayListUser();
}

//In ra danh sách các tài khoản của user
void Manager::displayTKUser() {
	this->listUser->xemTaiKhoanUser();
}