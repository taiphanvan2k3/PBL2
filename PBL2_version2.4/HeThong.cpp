﻿#pragma once
#include"HeThong.h"
bool HeThong::splitTk_Mk(user* u, wchar_t* str) {
	wchar_t Ds[2][100];
	int len = (int)wcslen(str);
	int idx = 0, len_sub = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == ',') {
			Ds[idx][len_sub] = L'\0';
			idx++;
			len_sub = 0;
			continue;
		}
		Ds[idx][len_sub++] = str[i];
		if (i == len - 1)
			Ds[idx][len_sub] = L'\0';
	}
	if (wstricmp(Ds[0], L"admin001@gmail.com") ==0 ) {
		/*khi gặp tài khoản là như vậy thì đó là của admin do đó ta return false
		để ở ngoài kia ta không thêm user *u vào hashtableuser*/
		manager->setMK(Ds[1]);
		return false;
	}
	u->setTK(Ds[0]);
	u->setMK(Ds[1]);
	return true;
}

HeThong::HeThong() {
	this->listUser = new HashtableUser;
	this->vocabMeaning = new HashtableMeaning;

	/*Manager đã tự động setDefaultAccount rồi, bây giờ cập cho Manager quản lí danh sách account và từ vựng
	hệ thống*/
	this->manager = new Manager;

	/*Tạo đối tượng con trỏ listContribute để khi user thêm từ vựng vào list này thì mananager vẫn có quyền
	vào list đó xem*/
	this->listContribute = new list<wstring>;

	//Đọc danh sách tài khoản (tk,mk) của các user từ file
	this->docFileListAccount();

	//Khi đọc file xong thì phải cho Manager quản lí danh sách user đó
	this->manager->setListUser(this->listUser);

	//Cho manager dùng vocabMeaning
	this->manager->setVocabMeaning(this->vocabMeaning);

	/*
	Ban đầu chạy chương trình là tự động nạp từ vựng hệ thống từ file
	vào cho manager,th=2 ứng với trường hợp tự động load từ vựng lên
	Lấy ra được vocabHeThong
	*/
	this->manager->docFileDanhSachTuVung(2);

	//Cho listContribute của manager dùng chung vùng địa chỉ với listContribute ở đây
	this->manager->setListContribute(this->listContribute);

	/*Gán vùng nhớ vocabHeThong trong class manager cho vocabHeThong trong class HeThong
	để khi vocabHeThong trong class Manager thay đổi thì vocabHeThong trong class HeThong cũng thay đổi theo*/
	this->vocabHeThong = this->manager->getVocabHeThong();

	//Đọc file các từ vựng mà user đã đóng góp từ file đã lưu trước đó
	this->docFileListContribute();
}



HeThong::~HeThong() {
	delete manager;
	/*
	Đổi với việc delete bảng băm thì phải xoá đệ quy trên từng danh sách
	của bảng băm đó
	*/
	delete listUser;
	delete vocabHeThong;
	delete vocabMeaning;
	deleteLinkList(listContribute->getHead());
}


HashtableUser* HeThong::getListUser() {
	return this->listUser;
}

void HeThong::docFileListAccount() {
	FILE* f;
	FILE** pFile = &f;
	_wfopen_s(pFile, L"account\\listAccount.txt", L"r,ccs=UTF-16LE");
	wchar_t str[100];
	if (f == NULL)
		return;
	while (!feof(f)) {
		fgetws(str, 100, *pFile);
		if (str[wcslen(str) - 1] == L'\n')
			str[wcslen(str) - 1] = L'\0';
		user* u = new user;
		bool check = this->splitTk_Mk(u, str);
		if(check)
			this->listUser->insert(u);
	}
	fclose(f);
}

account* HeThong::Login(int& phanQuyen) {
	gotoxy(40, 3);
	setcolor(3);
	wcout << L"TỪ VỰNG ANH-VIỆT TFLAT";
	wchar_t tk[100];
	wchar_t mk[30];
	int x = 30, y = 5;
	gotoxy(x, y);
	setcolor(7);
	wcout << L"Tài khoản:";
	bool check = true;
	int cnt = 0;
	do {
		if (!check) {
			setcolor(6);
			gotoxy(40, 5);
			wcout << L"tài khoản đăng nhập không được bỏ trống.";
			Sleep(1000);
			gotoxy(40, 5);
			for (int i = 0; i < 41; i++)
				wcout << L" ";
			gotoxy(40, 5);
		}
		setcolor(6);
		_getws_s(tk);
		formatInput(tk);
		check = false;
		cnt++;
	} while (wcslen(tk) == 0 && cnt < 5);
	if (cnt == 5) {
		system("cls");
		setcolor(6);
		wcout << L"\t\t\t->Thao tác đăng nhập của bạn bị huỷ.";
		Sleep(600);
		return NULL;
	}
	gotoxy(x, y + 1);
	setcolor(7);
	wcout << L"Mật khẩu:";
	setcolor(6);
	getMKInput(mk, 40, 6);
	//Đi kiểm tra đăng nhập
	gotoxy(30, 7);
	if (wstricmp(manager->getTK(), tk) == 0 && wstrcmp(manager->getMK(), mk) == 0) {
		setcolor(2);
		wcout << L"->Bạn đang đăng nhập với tư cách ADMIN." << endl;
		phanQuyen = 1;
		return manager;
	}
	else {
		user* temp = this->listUser->search(tk);
		if (temp == NULL || wstrcmp(temp->getMK(), mk) != 0) {
			setcolor(4);
			wcout << L"->Thông tin tài khoản hoặc mật khẩu không chính xác." << endl;
			return NULL;
		}
		else {
			setcolor(2);
			wcout << L"->Chào mừng bạn đã trở lại hệ thống." << endl;
			temp->loadTuVungHeThong(this->vocabHeThong);
			temp->setListContribute(this->listContribute);
			//setVocabMeaning để mỗi lần user tra cứu từ vựng Việt-Anh thì lấy ra dùng thôi
			temp->setVocabMeaning(this->vocabMeaning);
			phanQuyen = 2;
			return temp;
		}
	}
	setcolor(7);
}

//Chức năng đăng kí
void HeThong::SignUp() {
	int x = 30, y = 5;
	wchar_t tk[50];
	user* temp = NULL;
	do {
		system("cls");
		gotoxy(40, 3);
		setcolor(3);
		wcout << L"ĐĂNG KÝ TÀI KHOẢN" << endl;
		gotoxy(x, y);
		setcolor(7);
		wcout << L"Tài khoản:";
		setcolor(6);
		bool check = true;
		int cnt = 0;
		do {
			if (!check) {
				gotoxy(40, 5);
				wcout << L"tài khoản không được bỏ trống.";
				Sleep(1000);
				gotoxy(40, 5);
				for (int i = 0; i < 31; i++)
					wcout << L" ";
				gotoxy(40, 5);
			}
			check = false;
			_getws_s(tk);
			cnt++;
		} while (wcslen(tk) == 0 && cnt < 3);
		if (cnt == 3) {
			system("cls");
			setcolor(6);
			wcout << L"\t\t\t->Thao tác đăng kí của bạn bị huỷ vì bạn đã \n\t\t\tkhông tiến hành nhập tài khoản 3 lần liên tiếp.";
			Sleep(1000);
			return;
		}
		temp = this->listUser->search(tk);
		if (temp != NULL) {
			gotoxy(x + 10, y);
			setcolor(4);
			wcout << L"tài khoản này đã tồn tại trong hệ thống." << endl;
			ShowCur(0);
			Sleep(1500);
			ShowCur(1);
			for (int i = 0; i < 41; i++) {
				gotoxy(x + i, y);
				wcout << L" ";
			}
		}
	} while (temp != NULL);
	gotoxy(x, y + 1);
	setcolor(7);
	wchar_t mk[30];
	wcout << L"Mật khẩu:";
	setcolor(6);
	getMKInput(mk, 40, 6,1);
	//Xác nhận lại mật khẩu
	wchar_t confirmMk[30];
	gotoxy(x, y + 2);
	setcolor(7);
	wcout << L"Xác nhận MK:";
	bool check = true;
	int cnt = 0;
	do {
		if (!check) {
			gotoxy(43, 7);
			setcolor(4);
			wcout << L"mật khẩu xác nhận không khớp.";
			Sleep(1000);
			for (int i = 0; i < 30; i++) {
				gotoxy(43 + i, 7);
				wcout << L" ";
			}
		}
		setcolor(6);
		getMKInput(confirmMk, 43, 7,1);
		check = false;
		cnt++;
	} while (wstrcmp(mk, confirmMk) != 0 && cnt<3);
	
	gotoxy(30, 8);
	if (cnt == 3) {
		setcolor(2);
		wcout << L"->Thao tác bị huỷ do bạn nhập sai mật khẩu xác nhận 3 lần.";
		return;
	}
	setcolor(2);
	wcout << L"->Bạn vừa đăng kí thành công.";
	temp = new user;
	temp->setTK(tk);
	temp->setMK(mk);
	//Load từ vựng hệ thống cho user mới
	temp->loadTuVungHeThong(this->vocabHeThong);
	temp->setListContribute(this->listContribute);
	//setVocabMeaning để mỗi lần user tra cứu từ vựng Việt-Anh thì lấy ra dùng thôi
	temp->setVocabMeaning(this->vocabMeaning);
	this->listUser->insert(temp);
}


void HeThong::docFileListContribute() {
	FILE* f = NULL;
	FILE** pFile = &f;
	_wfopen_s(pFile, L"contributedVocab.txt", L"r,ccs=UTF-16LE");
	if (f == NULL)
		return;
	while (!feof(f)) {
		wchar_t str[30];
		fgetws(str, 30, f);
		if (str[wcslen(str) - 1] == L'\n')
			str[wcslen(str) - 1] = L'\0';
		if (this->vocabHeThong->search(str) == NULL)
			this->listContribute->push_back(str);
	}
	fclose(f);
}

void HeThong::ghiFileListContribute() {
	FILE* f = NULL;
	FILE** pFile = &f;
	_wfopen_s(pFile, L"contributedVocab.txt", L"w,ccs=UTF-16LE");
	if (f == NULL)
		return;
	if (this->listContribute->getSize() == 0) {
		fclose(f);
		system("del contributedVocab.txt");
		return;
	}	
	node<wstring>* temp = this->listContribute->getHead();
	while (temp) {
		wchar_t str[30];
		wstrcpy(str, temp->getData());
		fwprintf(f, L"%s", str);
		if (temp->getNext() != NULL)
			fwprintf(f, L"\n");
		temp = temp->getNext();
	}
	fclose(f);
}


void HeThong::LuuDuLieu() {
	/*
	Chức năng này sẽ được gọi khi tại menu chung thực hiện tuỳ chọn thoát
	Tiến hành lưu toàn bộ từ vựng hệ thống, tk-mk user, album từ vựng của từng user xuống file
	Từ vựng hệ thống và album từ vựng (user) đều là class HashtableVocab
	=> Xây dựng phương thức ghi file trên HashtableVocab
	*/

	wchar_t filePhienAm[] = L"test.txt";
	this->manager->getVocabHeThong()->ghiFileVocab(filePhienAm);

	//Lưu toàn bộ tk-mk user xuống file
	this->listUser->ghiFileTkMk(manager->getTK(),manager->getMK());
	//Lưu các từ vựng đóng góp mà admin chưa thực hiện việc thêm xuống file
	this->ghiFileListContribute();

	/*
	Lưu toàn bộ album từ vựng của từng user xuống file
	this->listUser->ghiFileAlbumUser();
	Lưu ý phương thức vừa rồi là sai vì khi 1 tài khoản chưa đăng nhập lần nào
	vào hệ thống khi hệ thống mở thì số từ vựng album của nó là 0 nên khi gọi phương thức
	trên thì vô tình xoá đi file của user đó
	*/
}


void HeThong::MenuManager() {
	wstring task[11];
	//Menu manager thuộc th=2 và có 10 tuỳ chọn (b=10)
	updateTask(task, 2);
	int b = 11;
	int x = 30, y = 5, w = 60, h = 2;
	int t_color = 3, b_color = 0;
	int b_color_curr = 4;
	int KT = 1;
	int yp = y, ycu = y;
	in_tieu_de(task, x, y, w, b);
	while (1) {
		//Tắt con trỏ chuột để khỏi nhấp nháy
		ShowCur(0);
		if (KT) {
			//Tắt màu hộp đã thao tác trước đây
			this->thanh_sang2(task[(ycu - y) / 2], x, ycu, w, h, t_color, b_color);
			ycu = yp;
			//Bật màu hộp đang cần thao tác ở thời điểm hiện tại
			this->thanh_sang2(task[(yp - y) / 2], x, yp, w, h, t_color, b_color_curr);
			KT = 0;
			/*Sau khi thay đổi màu thanh sáng phải gán lại KT=0,lí do là vòng while(1)
			chạy liên tục nên nếu chúng ta không gán KT=1 thì nó cứ vào và đổi màu thanh
			sáng trong khi mình chưa thao tác gì*/
		}
		//Nếu người dùng bấm một kí tự từ bàn phím
		if (_kbhit())
		{
			//Lấy ra kí tự vừa bấm đó
			char c = _getch();
			//Nếu bấm back_space hoặc esc thì kết thúc chương trình
			if (c == 32 || c == 27) break;
			KT = 1;
			//c==72: điều hướng đi lên
			if (c == 72) {
				//Nếu ở hộp đầu tiên mà bấm nữa thì sẽ nhảy xuống hộp cuối cùng
				if (yp == y)
					yp = y + (b - 1) * h;
				else yp -= h;
			}
			//c==80: điều hướng đi xuống
			else if (c == 80) {
				if (yp == y + (b - 1) * h)
					yp = y;
				else yp += h;
			}
			//Nhấn enter
			else if (c == 13) {
				ShowCur(1);
				int lc = (yp - y) / h;
				system("cls");

				//Triển khai các tuỳ chọn
				if (lc == 0) {
					//Load thêm từ vựng từ file lên hệ thống
					this->manager->docFileDanhSachTuVung(1);
				}
				else if (lc == 1) {
					//Xem từ vựng hệ thống.
					this->manager->InTuVungHeThong();
				}
				else if (lc == 2) {
					//Thêm thủ công từ vựng vào từ điển hệ thống.
					vocab* v = new vocab;
					this->manager->themTuVung(v);
				}
				else if (lc == 3) {
					//Chỉnh sửa thông tin từ vựng.
					this->manager->chinhSuaTuVung();
				}
				else if (lc == 4) {
					//Xoá từ vựng khỏi từ điển hệ thống
					this->manager->xoaTuVung();
				}
				else if (lc == 5) {
					//Xem và thêm từ vựng đóng góp vào từ điển
					this->manager->InTuVungDongGop();
					if (listContribute->getSize() > 0) {
						vocab* v = new vocab;
						this->manager->themTuVung(v, 0);
					}
				}
				else if (lc == 6) {
					//In thông tin danh sách người dùng.
					this->manager->displayListUser();
				}
				else if (lc == 7) {
					this->manager->searchUser();
				}
				else if (lc == 8) {
					wcout << L"Danh sách tài khoản user:" << endl;
					this->manager->displayTKUser();
					this->manager->deleteUser();
				}
				else if (lc == 9) {
					this->manager->doiMatKhau();
				}
				else if (lc == 10) {
					/*Với manager, việc đăng xuất chỉ đơn giản là tắt máy
					Còn với user thì mới có thông báo .....*/
					break;
				}
				if (lc !=0 && lc != 1 && lc != 2 && lc != 3 && lc!=4 && lc!=5) {
					ShowCur(0);
					int temp = _getch();
				}
				in_tieu_de(task, x, y, w, b);
			}
		}
	}
}

void HeThong::MenuUser(user* u) {
	//Menu user thuộc th=3 và có 9 tuỳ chọn (b=7)
	int b = 9;
	wstring task[10];
	updateTask(task, 3);
	int x = 30, y = 5, w = 60, h = 2;
	int t_color = 3, b_color = 0;
	int b_color_curr = 4;
	int KT = 1;
	int yp = y, ycu = y;
	in_tieu_de(task, x, y, w, b);
	while (1) {
		//Tắt con trỏ chuột để khỏi nhấp nháy
		ShowCur(0);
		if (KT) {
			//Tắt màu hộp đã thao tác trước đây
			this->thanh_sang2(task[(ycu - y) / 2], x, ycu, w, h, t_color, b_color);
			ycu = yp;
			//Bật màu hộp đang cần thao tác ở thời điểm hiện tại
			this->thanh_sang2(task[(yp - y) / 2], x, yp, w, h, t_color, b_color_curr);
			KT = 0;
		}
		//Nếu người dùng bấm một kí tự từ bàn phím
		if (_kbhit())
		{
			//Lấy ra kí tự vừa bấm đó
			char c = _getch();
			//Nếu bấm back_space hoặc esc thì kết thúc chương trình
			if (c == 32 || c == 27) break;
			KT = 1;
			//c==72: điều hướng đi lên
			if (c == 72) {
				//Nếu ở hộp đầu tiên mà bấm nữa thì sẽ nhảy xuống hộp cuối cùng
				if (yp == y)
					yp = y + (b - 1) * h;
				else yp -= h;
			}
			//c==80: điều hướng đi xuống
			else if (c == 80) {
				if (yp == y + (b - 1) * h)
					yp = y;
				else yp += h;
			}
			//Nhấn enter
			else if (c == 13) {
				ShowCur(1);
				int lc = (yp - y) / h;
				system("cls");
				//Tra cứu từ điển Anh-Việt.
				if (lc == 0)
					u->traCuuTuVungAnhViet();
				//Tra cứu từ điển Việt-Anh.
				else if (lc == 1)
					u->traCuuTuVungVietAnh();
				//Thêm từ vựng vào album cá nhân.
				else if (lc == 2) {
					int lc;
					setcolor(3);
					wcout << L"\t\t\tChọn hình thức để thêm từ vựng vào album của bạn:" << endl;
					setcolor(2);
					wcout << L"\t\t\t1.Thêm từ vựng thủ công." << endl;
					wcout << L"\t\t\t2.Thêm từ vựng từ nguồn từ vựng của hệ thống." << endl;
					setcolor(6);
					wcout << L"->Lựa chọn của bạn là:";
					setcolor(7);
					wcin >> lc;
					int c = getwchar();
					system("cls");
					if (lc == 1) {
						vocab* v = new vocab;
						u->themTuVung(v);
					}
					else {
						vocab* ds = NULL;
						int n;
						u->getVocabHeThong()->convertToArray(ds, n);
						quicksort(ds, 0, n - 1);
						bool* checkStatus = new bool[n];
						for (int i = 0; i < n; i++) {
							vocab* temp = u->getAlbum()->search(ds[i].getEnglish());
							if (temp != NULL)
								checkStatus[i] = 1;
							else checkStatus[i] = 0;
						}
						int x = 1;
						int ycu = 4, yp = 4;
						gotoxy(1, 4);
						wcout << L"└──>";
						gotoxy(1, 1);
						//u->themTuVungNewVersion(ds, n, checkStatus);
						int KT = 1;
						int page_curr = 1, page_max = n / 20;
						if (page_max % 20 != 0)
							page_max++;
						int* numOfPage = new int[page_max + 1];
						setPage(numOfPage, n);
						u->themTuVungVersion(ds, n, page_curr, checkStatus);
						while (1) {
							ShowCur(0);
							if (KT) {
								gotoxy(x, ycu);
								wcout << L"    ";
								ycu = yp;
								KT = 0;
								gotoxy(x, yp);
								wcout << L"└──>";
							}
							if (_kbhit()) {
								char c = _getch();
								if (c == 32 || c == 27)
									break;
								KT = 1;
								//Điều hướng đi lên
								if (c == 72) {
									if (yp == 4)
										yp = 3 + numOfPage[page_curr];
									else yp--;
								}
								else if (c == 80) {
									if (yp == numOfPage[page_curr] + 3)
										yp = 4;
									else yp++;
								}
								else if (c == 75) {
									if (page_curr != 1) {
										system("cls");
										gotoxy(1, 1);
										u->themTuVungVersion(ds, n, --page_curr, checkStatus);
										yp = 4;
									}
								}
								else if (c == 77) {
									if (page_curr < page_max) {
										system("cls");
										gotoxy(1, 1);
										u->themTuVungVersion(ds, n, ++page_curr, checkStatus);
										yp = 4;
									}
								}
								else if (c == 13) {
									system("cls");
									/*Vì mỗi trang sẽ bắt đầu với số thứ tự khác nhau
									để tìm chính xác ra đang ở từ vựng nào trong mảng
									ta cần cộng 1 lượng (offset = yp-4) vào 20*(page_curr-1)*/
									int idx = 20 * (page_curr - 1) + (yp - 4);
									checkStatus[idx] = 1 - checkStatus[idx];
									if (checkStatus[idx]) {
										setcolor(2);
										wcout << L"Vừa thêm từ vựng [" << ds[idx].getEnglish() << L"] vào album của bạn." << endl;
										setcolor(7);
										vocab* v = new vocab;
										*v = ds[idx];
										u->getAlbum()->insert(v);
										ShowCur(0);
										int c = _getch();
									}
									else u->getAlbum()->deleteVocab(ds[idx].getEnglish());
									system("cls");
									gotoxy(1, 1);
									u->themTuVungVersion(ds, n, page_curr, checkStatus);
								}
							}
						}
					}
				}
				//Xem từ vựng hệ thống
				else if (lc == 3)
					u->InTuVungHeThong();
				//Xem từ vựng album cá nhân.
				else if (lc == 4)
					u->InTuVungAlbum();
				//Xoá từ vựng ra khỏi album.
				else if (lc == 5)
					u->xoaTuVung();
				//Ôn tập kiến thức.
				else if (lc == 6) {
					setcolor(3);
					wcout << L"Hệ thống hiện tại đang có 2 loại trò chơi:" << endl;
					setcolor(2);
					wcout << L"\t1.Trò chơi điền kí tự còn thiếu vào chỗ trống để tạo ra từ vựng chính xác." << endl;
					wcout << L"\t2.Trò chơi kiểm tra từ vựng thông qua bộ câu hỏi trắc nghiệm." << endl;
					int lc;
					setcolor(6);
					wcout << L"Mời bạn nhập lựa chọn của mình:";
					setcolor(4);
					wcin >> lc;
					setcolor(7);
					int c = (int)getwchar();
					if (lc == 1)
						u->gameDienTu();
					else u->gameChonDapAnDung2();
				}
				else if (lc == 7) {
					u->doiMatKhau();
				}
				/*Đăng xuất, chỉ ghi album từ vựng user xuống file khi tắt chương trình thôi
				giảm thiểu thời gian cập nhật dữ liệu file liên tục và không cần thiết*/
				else {
					wchar_t path[100];
					wstrcpy(path, u->getPath());
					//Nếu album đang rỗng thì delete đi
					if (u->getAlbum()->getSoLuong() == 0) {
						if (u->isExistFileAlbum())
							u->deleteFileAlbum();
					}

					else u->getAlbum()->ghiFileVocab(path);
					setcolor(3);
					wcout << L"\t\t\t\tĐã sao toàn bộ lưu dữ liệu của bạn." << endl;
					wcout << L"\t\t\tTạm biệt bạn.Hẹn gặp lại bạn ở phiên đăng nhập tiếp theo.";
					waitForType();
					setcolor(0);
					break;
				}
				ShowCur(0);
				if (lc != 2 && lc!=3) {
					if (lc == 4 && u->getAlbum()->getSoLuong() == 0)
						waitForType();
					else if (lc != 4) {
						if (lc != 7 && lc != 0 && lc != 6 && lc != 1)
							system("pause");
						else waitForType();
					}
				}
				in_tieu_de(task, x, y, w, b);
			}
		}
	}
}

void HeThong::MAIN() {
	//Menu general có 3 tuỳ chọn => b=3
	int b = 3;
	wstring task[10];
	updateTask(task, 1);
	int x = 45, y = 5, w = 30, h = 2;
	int t_color = 3, b_color = 0;
	int b_color_curr = 4;
	int KT = 1;
	int yp = y, ycu = y;
	in_tieu_de(task, x, y, w, b);
	while (1) {
		//Tắt con trỏ chuột để khỏi nhấp nháy
		ShowCur(0);
		if (KT) {
			//Tắt màu hộp đã thao tác trước đây
			this->thanh_sang2(task[(ycu - y) / 2], x, ycu, w, h, t_color, b_color);
			ycu = yp;
			//Bật màu hộp đang cần thao tác ở thời điểm hiện tại
			this->thanh_sang2(task[(yp - y) / 2], x, yp, w, h, t_color, b_color_curr);
			KT = 0;
		}
		if (_kbhit())
		{
			char c = _getch();
			if (c == 32 || c == 27) break;
			KT = 1;
			if (c == 72) {

				if (yp == y)
					yp = y + (b - 1) * h;
				else yp -= h;
			}
			else if (c == 80) {
				if (yp == y + (b - 1) * h)
					yp = y;
				else yp += h;
			}
			else if (c == 13) {
				ShowCur(1);
				int lc = (yp - y) / h;
				system("cls");
				if (lc == 0) {
					/*Chức năng đăng nhập tài khoản
					phanQuyen=1 =>Manager
					phanQuyen=2 =>User
					Ngược lại là đăng nhập thất bại*/
					int phanQuyen;
					account* temp = this->Login(phanQuyen);
					ShowCur(0);
					Sleep(650);
					if (temp != NULL) {
						if (phanQuyen == 1)
							this->MenuManager();
						else {
							user* u = (user*)temp;
							/*Khi đăng nhập thành công sẽ tự động đọc file từ vựng album của user từ file
							Chỉ đọc file khi user chưa đăng nhập lần nào kể từ lúc chạy chương trình
							Còn nếu đã đăng nhập rồi thì từ vựng user đó đã có sẵn trong vocabAlbum của user đó rồi*/
							if (u->getFirstLogin() == false) {
								u->docFileAlbum();
								u->setFirstLogin();
							}

							//Gọi menu user
							this->MenuUser(u);
						}
					}
				}
				else if (lc == 1) {
					//Chức năng đăng kí tài khoản
					this->SignUp();
					ShowCur(0);
					Sleep(650);
				}
				else if (lc == 2) {
					this->LuuDuLieu();
					setcolor(3);
					wcout << L"\t\tĐã sao lưu toàn bộ dữ liệu xuống tập tin." << endl;
					wcout << L"\t\t\tCHÀO TẠM BIỆT!!!" << endl;
					setcolor(7);
					break;
				}
				in_tieu_de(task, x, y, w, b);
			}
		}
	}
}