#pragma once
#include"HashtableVocab.h"
HashtableVocab::HashtableVocab() {

}

void HashtableVocab::insert(vocab* x) {
	//overiding lại phương thức insert ở làm cha
	bool canInsert = Hashtable::insert(x);
	if (!canInsert) {
		setcolor(4);
		wprintf(L"->Từ vựng bạn muốn thêm đã có sẵn trong từ điển.\n");
		setcolor(7);
	}
}

void HashtableVocab::deleteVocab(wstring key) {
	convert(key);
	int id = hash(key);
	vocab* after = heads[id], * before = NULL;
	while (after != NULL && wstrcmp(after->getEnglish(), key) != 0) {
		before = after;
		after = after->next;
	}
	if (after == NULL) {
		setcolor(6);
		wprintf(L"Từ vựng bạn muốn xoá không có trong từ điển.\n");
	}
	else {
		deleted++;
		setcolor(6);
		wprintf(L"Đã xoá từ vựng:");
		after->display();
		wprintf(L" ra khỏi từ điển.\n");
		if (after == heads[id])
			heads[id] = after->next;
		else
			before->next = after->next;
		delete after;
		ShowCur(0);
		int c = _getch();
	}
	setcolor(7);
}

//In theo trang này được dùng cho phương thức inTuVungHeThong
void HashtableVocab::InTheoTrang(vocab* ds, int n, int page, int page_max) {
	//In khung
	if (page == 1) {
		setcolor(3);
		wcout << L"\t\t\t\tTừ vựng trong album của bạn hiện tại đang có: " << this->getSoLuong() << endl;
		setcolor(7);
	}
	wcout << L"Bạn đang ở trang " << page << "/" << page_max << endl;
	wcout << L"\t┌";
	for (int i = 1; i <= 101; i++) {
		if (i == 8 || i == 29 || i == 50 || i == 66)
			wcout << L"┬";
		else wcout << L"─";
	}

	wcout << L"┐";
	wcout << "\n\t" << left << setw(6) << L"│  STT";
	wcout << L"\t│" << left << setw(20) << L"     Tiếng Anh" << L"│" << left << setw(20) << L"       Phiên âm" << L"│" << left << setw(15) << L"   Từ loại" << L"│" << left << setw(35) << L"          Nghĩa Tiếng Việt" << L"│" << endl;
	wcout << L"\t├";
	for (int i = 1; i <= 101; i++) {
		if (i == 8 || i == 29 || i == 50 || i == 66)
			wcout << L"┼";
		else wcout << L"─";
	}
	wcout << L"┤\n";

	//In từ vựng
	for (int i = 20 * (page - 1); i < 20 * page && i < n; i++) {
		wcout << L"\t│" << left << setw(6) << (i + 1);
		/*display(2): ứng với cách in từ vựng theo dạng bảng,
		còn display(1) để in thông tin từ vựng theo kiểu tìm kiếm từ vựng*/
		ds[i].display(2);
		wcout << endl;
	}

	wcout << L"\t└";
	for (int i = 1; i <= 101; i++) {
		if (i == 8 || i == 29 || i == 50 || i == 66)
			wcout << L"┴";
		else wcout << L"─";
	}
	wcout << L"┘\n\n";
}

void HashtableVocab::InTuVungTangDan() {
	vocab* ds = NULL;
	int n;
	this->convertToArray(ds, n);
	quicksort(ds, 0, n - 1);
	int page_curr = 1, page_max = n / 20;
	if (n % 20 != 0)
		page_max++;
	InTheoTrang(ds, n, page_curr, page_max);
	ShowCur(0);
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == 27 || c == 13)
				break;
			if (c == -32) {
				c = _getch();
				/*
				Enter:13
				->: 77
				<-: 75
				Lên: 72
				Xuống:80
				*/
				if (c == 77) {
					//Qua trang tiếp theo và chỉ in khi không có sự thay đổi về số trang
					if (page_curr != page_max) {
						system("cls");
						page_curr++;
						InTheoTrang(ds, n, page_curr, page_max);
					}
				}
				else if (c == 75) {
					//Qua trái và chỉ in khi không có sự thay đổi về số trang
					if (page_curr != 1) {
						system("cls");
						page_curr--;
						InTheoTrang(ds, n, page_curr, page_max);
					}
				}
			}
		}
	}
	ShowCur(1);
}

void HashtableVocab::ghiFileVocab(wchar_t* tenFile) {
	FILE* f = NULL;
	FILE** pFile = &f;
	_wfopen_s(pFile, tenFile, L"w,ccs=UTF-16LE");
	if (f == NULL) {
		wcout << L"Mở file để ghi thất bại.";
		return;
	}
	node<int>* l = listId.getHead();
	int n = num - deleted, idx = 0;
	while (l) {
		vocab* tam = this->heads[l->data];
		while (tam != NULL) {
			idx++;
			wchar_t vn[100];
			wstrcpy(vn, tam->toStringListVN());
			fwprintf_s(f, L"%s\n%s-%s-%s;%d,%d", tam->getPhienAm(), tam->getEnglish(), vn, tam->getTuLoai(), tam->getSoLuong(), tam->getPoint());
			if (idx < n)
				fwprintf_s(f, L"\n");
			tam = tam->next;
		}
		l = l->next;
	}
	fclose(f);
}