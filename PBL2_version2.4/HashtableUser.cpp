#include"HashtableUser.h"

HashtableUser::HashtableUser() {

}

void HashtableUser::insert(user* x) {
	//overiding lại phương thức insert ở làm cha
	bool canInsert = Hashtable::insert(x);
	if (!canInsert) {
		setcolor(4);
		wcout << L"Tài khoản này đã tồn tại trong hệ thống." << endl;
	}
}

void HashtableUser::deleteUser(wchar_t tk[]) {
	convert(tk);
	int id = hash(tk);
	user* after = heads[id], * before = NULL;
	while (after != NULL && wstrcmp(after->getTK(), tk) != 0) {
		before = after;
		after = after->getNext();
	}
	if (after == NULL) {
		setcolor(4);
		wprintf(L"Tài khoản bạn đang muốn xoá không có trong hệ thống.\n");
	}
	else {
		system("cls");
		deleted++;
		setcolor(2);
		wprintf(L"Đã xoá người dùng có thông tin sau ra khỏi hệ thống:\n");
		setcolor(7);
		after->xemThongTinTaiKhoan();
		if (after == heads[id])
			heads[id] = after->getNext();
		else before->setNext(after->getNext());
		if (after->isExistFileAlbum())
			after->deleteFileAlbum();
		delete after;
	}
	setcolor(7);
}

void HashtableUser::displayListUser() {
	node<int>* l = listId.getHead();
	setcolor(3);
	wcout << "\t\t" << left << setw(30) << L"   Tài khoản" << "\t\t" << L"   Mật khẩu" << endl;
	setcolor(7);
	while (l) {
		user* tam = heads[l->data];
		while (tam) {
			tam->xemThongTinTaiKhoan();
			tam = tam->getNext();
		}
		l = l->next;
	}
	setcolor(7);
}

void HashtableUser::xemTaiKhoanUser() {
	setcolor(3);
	wcout << "\t\t" << left << setw(10) << "STT" << "\t" << L"Tài khoản\n";
	setcolor(7);
	node<int>* l = listId.getHead();
	int stt = 1;
	while (l) {
		user* tam = heads[l->data];
		while (tam) {
			wcout << "\t\t" << left << setw(10) << stt++ << "\t" << tam->getTK() << endl;
			tam = tam->getNext();
		}
		l = l->next;
	}
	setcolor(7);
}


//Đồng bộ từ vựng, khi manager sửa 1 từ vựng nào mà user nào có thì cập nhật lại
//từ vựng đó của user
void HashtableUser::syncVocab(vocab* updatedVocab) {
	node<int>* l = listId.getHead();
	while (l) {
		user* tam = heads[l->data];
		while (tam) {
			vocab* temp = tam->getAlbum()->search(updatedVocab->getEnglish());
			if (temp != NULL)
				temp->updateData(updatedVocab);
			//*temp = *updatedVocab;
		//tam = tam->next;
			tam = tam->getNext();
		}
		l = l->next;
	}
}

//Ghi tk,mk vào lại chính file mà ta đã đọc thông tin tk,mk user lúc chạy chương trình
void HashtableUser::ghiFileTkMk() {
	FILE* f = NULL;
	FILE** pFile = &f;
	_wfopen_s(pFile, L"account\\listAccount.txt", L"w,ccs=UTF-16LE");
	node<int>* l = listId.getHead();
	int idx = 0, n = num - deleted;
	if (f == NULL)
		return;
	while (l != NULL) {
		user* tam = heads[l->data];
		while (tam != NULL) {
			idx++;
			fwprintf(f, L"%s,%s", tam->getTK(), tam->getMK());
			if (idx < n)
				fputwc(L'\n', f);
			tam = tam->getNext();
		}
		l = l->next;
	}
	fclose(f);
}