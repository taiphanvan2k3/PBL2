#include"user.h"
user::user() {
	this->firstLogin = false;
	this->next = NULL;
	this->album = new HashtableVocab();
}

void user::setNext(user* x) {
	this->next = x;
}

user* user::getNext() {
	return this->next;
}

bool user::getFirstLogin() {
	return this->firstLogin;
}

void user::setFirstLogin() {
	this->firstLogin = true;
}

HashtableVocab* user::getAlbum() {
	return this->album;
}

//Biến th này chỉ cần thiết bên manager, vì ta đang kế thừa từ lớp account nên phải override lại
//đúng phương thức themTuVung này như trong class cha
void user::themTuVung(vocab* v, int th) {
	setcolor(6);
	wprintf(L"Bạn cần điền các thông tin sau để hoàn tất việc thêm từ vựng vào ALBUM của bạn:\n");
	wprintf(L"Mời bạn nhập từ vựng:");
	wchar_t str[30];
	setcolor(7);
	_getws_s(str);
	formatInput(str);
	convert(str);
	vocab* tam = this->album->search(str);
	if (tam != NULL) {
		wprintf(L"Từ vựng bạn muốn thêm đã có trong album của bạn rồi.\n");
		ShowCur(0);
		int c = _getch();
	}
	else {
		v->setEnglish(str);
		v->nhap_tt_1_vocab();
		album->insert(v);
	}
}
//Thêm từ vựng vào album dựa trên từ vựng có sẵn có admin
void user::themTuVungVersion(vocab* ds, int n, int page, bool* checkStatus) {
	wcout << L"\t┌";
	for (int i = 1; i <= 109; i++) {
		if (i == 16 || i == 37 || i == 58 || i == 74)
			wcout << L"┬";
		else wcout << L"─";
	}
	wcout << L"┐";
	wcout << "\n\t" << left << setw(14) << L"│Tình trạng";
	wcout << L"\t│" << left << setw(20) << L"     Tiếng Anh" << L"│" << left << setw(20) << L"       Phiên âm" << L"│" << left << setw(15) << L"   Từ loại" << L"│" << left << setw(35) << L"          Nghĩa Tiếng Việt" << L"│" << endl;
	wcout << L"\t├";
	for (int i = 1; i <= 109; i++) {
		if (i == 16 || i == 37 || i == 58 || i == 74)
			wcout << L"┼";
		else wcout << L"─";
	}
	wcout << L"┤\n";
	for (int i = 20 * (page - 1); i < 20 * page && i < n; i++) {
		wstring status = (checkStatus[i]) ? (L"Đã thêm") : (L"Chưa thêm");
		if (status == L"Đã thêm") {
			wcout << L"\t│" << left << setw(14);
			setcolor(4);
			wcout << status;
			setcolor(7);
		}
		else wcout << L"\t│" << left << setw(14) << status;
		ds[i].display(2);
		wcout << endl;
	}
	wcout << L"\t└";
	for (int i = 1; i <= 109; i++) {
		if (i == 16 || i == 37 || i == 58 || i == 74)
			wcout << L"┴";
		else wcout << L"─";
	}
	wcout << L"┘\n\n";
}

//Phương thức này sẽ tự động gọi khi user đăng nhập thành công
void user::docFileAlbum() {
	FILE* f = NULL;
	FILE** pFile = &f;
	wchar_t tenFile[100] = L"account\\";
	wstrcat(tenFile, this->getSimpleTk());
	wstrcat(tenFile, L".txt");
	_wfopen_s(pFile, tenFile, L"r,ccs=UTF-16LE");
	if (f == NULL)
		return;
	while (!feof(f)) {
		vocab* a = new vocab;
		a->doc_file_1_vocab(f);
		vocab* temp = this->getVocabHeThong()->search(a->getEnglish());
		if (temp != NULL) {
			a->updateData(temp);
			//*a = *temp;
			//a->setNext(NULL);
		}
		this->album->insert(a);
	}
	fclose(f);
}

void user::traCuuTuVungAnhViet() {
	gotoxy(35, 2);
	setcolor(2);
	wcout << L"===========TRA CỨU TỪ VỰNG ANH-VIỆT===========" << endl;
	wchar_t str[30];
	setcolor(3);
	wcout << L"Nhập từ vựng bạn cần TRA CỨU :";
	setcolor(6);
	_getws_s(str);
	formatInput(str);
	convert(str);
	vocab* tam = this->vocabHeThong->search(str);
	if (tam == NULL) {
		setcolor(4);
		wcout << L"Từ vựng bạn cần tra cứu hiện tại vẫn chưa có trong từ điển." << endl;
		setcolor(3);
		wcout << L"Hệ thống xin ghi nhận đóng góp của bạn và sẽ xem xét việc thêm từ vựng bạn vừa tra cứu vào từ điển hệ thống." << endl;
		setcolor(7);
		this->listContribute->push_back(str);
	}
	else {
		setcolor(2);
		tam->display();
		setcolor(7);
		wcout << endl;
	}
	ShowCur(0);
}

void user::traCuuTuVungVietAnh() {
	gotoxy(35, 2);
	setcolor(2);
	wcout << L"===========TRA CỨU TỪ VỰNG VIỆT-ANH===========" << endl;
	setcolor(3);
	wcout << L"->Nhập nghĩa để tìm kiếm:";
	wstring str;
	setcolor(6);
	bool check = true;
	int cnt = 0;
	do {
		if (!check) {
			gotoxy(25, 3);
			wcout << L"bạn vui lòng nhập từ bạn cần tra cứu trước khi nhấn Enter.";
			Sleep(1000);
			gotoxy(25, 3);
			for (int i = 0; i < 59; i++)
				wcout << L" ";
			gotoxy(25, 3);
		}
		check = false;
		cnt++;
		getline(wcin, str);
	} while (str.size() == 0 && cnt<5);
	if (cnt == 5) {
		system("cls");
		setcolor(6);
		wcout << L"\t->Thao tác bị huỷ vì dường như bạn không muốn tra cứu từ vựng.";
		return;
	}
	formatInput(str);
	setcolor(3);
	wcout << L"->Kết quả tìm kiếm:";
	setcolor(7);
	this->vocabMeaning->traCuu(str);
}

//User chỉ có quyền xoá từ vựng trong album của họ thôi chứ không có quyền xoá vào từ vựng hệ thống
void user::xoaTuVung() {
	if (this->album->getSoLuong() == 0) {
		wcout << L"Thao tác này không hợp lệ do album của bạn hiện tại đang rỗng." << endl;
		return;
	}

	wchar_t str[50];
	wcout << L"Nhập từ vựng bạn cần XOÁ:";
	_getws_s(str);
	formatInput(str);
	this->album->deleteVocab(str);
}

void user::InTuVungAlbum() {
	if (this->album->getSoLuong() == 0)
		wcout << L"\t\tAlbum từ vựng của bạn hiện tại đang trống." << endl;
	else album->InTuVungTangDan();
}

//Gọi phương thức này khi đăng kí tk user hoặc đăng nhập thành công

void user::loadTuVungHeThong(HashtableVocab* vocabHeThong2) {
	this->vocabHeThong = vocabHeThong2;
}

void user::reviewVocab(list<vocab>wrongAnswer) {
	system("cls");
	if (wrongAnswer.getSize() > 0) {
		setcolor(3);
		wcout << L"\t\tHãy dành chút thời gian của mình để xem lại những từ bạn đã trả lời sai:\n\n";
		setcolor(7);
		node<vocab>* temp = wrongAnswer.getHead();
		int cnt = 0;
		while (temp) {
			cnt++;
			vocab k = temp->getData();
			wcout << "\t\t\t" << left << setw(25) << k.getEnglish() << L"───────>\t\t"<< k.toStringListVN() << endl;
			if (cnt == 10) {
				cnt = 0;
				ShowCur(0);
				int c = _getch();
				system("cls");
				setcolor(3);
				wcout << L"\t\tHãy dành chút thời gian của mình để xem lại những từ bạn đã trả lời sai:\n\n";
				setcolor(7);
			}
			temp = temp->getNext();
		}
	}
	else {
		setcolor(3);
		gotoxy(32, 0);
		wcout << L"Hẹn gặp lại bạn vào lần ôn tập tiếp theo.";
	}
	setcolor(7);
}

void user::gameDienTu() {
	//Lưu lại các câu mà người dùng đã trả lời sai
	list<vocab>wrongAnswer;

	//Duyệt tất cả các từ vựng có trong album rồi dùng rand() để chọn 1 vị trí để chừa trống
	vocab* list = NULL;
	int n = 0;
	this->vocabHeThong->convertToArray(list, n);
	shuffle(list, n);
	srand((unsigned int)time(NULL));
	
	int score = 0, right = 0;
	for (int i = 0; i < n; i++) {
		system("cls");
		wchar_t str[30];
		wstrcpy(str, list[i].getEnglish());
		int len = (int)wcslen(str);
		int pos_random;
		wchar_t c;
		do {
			pos_random = rand() % len;
			c = str[pos_random];
		} while (c == ' ');
		str[pos_random] = '_';
		setcolor(2);
		wcout << L"\t\t\t\t\t\t\t\t Điểm số của bạn hiện tại:" << score << endl;
		if (i != 0)
			wcout << L"\t\t\t\t\t\t\t\t Đúng:" << right << "\tSai:" << i - right << endl;
		setcolor(3);
		setcolor(6);
		wcout << L"Điền kí tự thích hợp vào từ còn thiếu sau:";
		setcolor(7);
		wcout << str << endl;
		setcolor(6);
		wcout << L"Nhấn enter hoặc 0 nếu bạn không muốn chơi nữa!!!\n";
		wcout << L"─>Mời bạn nhập vào 1 kí tự để hoàn chỉnh từ vựng trên:";
		setcolor(4);
		wchar_t input[10];
		_getws_s(input);
		setcolor(6);
		if (wstrcmp(input, L"") == 0 || wstrcmp(input, L"0") == 0)
			break;
		else if (wcslen(input) > 1) {
			system("cls");
			setcolor(2);
			wcout << L"Câu trả lời của bạn không đúng định dạng và vẫn tính là một câu sai" << endl;
			setcolor(7);
		}
		convert(input);
		if (input[0] == c) {
			right++;
			setcolor(2);
			wcout << L"─>Bạn đã trả lời chính xác." << endl;
			score += list[i].getPoint();
			wcout << L"->Điểm số của bạn vừa được cộng thêm " << list[i].getPoint() << endl;
		}
		else {
			setcolor(4);
			wcout << L"->Câu trả lời của bạn chưa chính xác." << endl;
			wrongAnswer.push_back(list[i]);
		}
		setcolor(6);
		wcout << L"Từ vựng hoàn chỉnh là:";
		list[i].display();
		wcout << endl;
		setcolor(7);
		ShowCur(0);
		int temp = _getch();
	}
	reviewVocab(wrongAnswer);
}

void user::gameChonDapAnDung2() {
	//Lưu lại các câu mà người dùng đã trả lời sai
	list<vocab>wrongAnswer;

	/*Tạo 1 mảng các vocab với số lượng lấy ra từ getSize album shuffle mảng đó
	Duyệt mảng ,chọn 3 nghĩa khác từ listString các nghĩa vn có được lúc loadDuLieu
	shuffle 4 option đó*/
	vocab* list = NULL;
	int n = 0;
	this->vocabHeThong->convertToArray(list, n);
	shuffle(list, n);
	srand((unsigned int)time(NULL));
	int score = 0, right = 0;
	for (int i = 0; i < n; i++) {
		system("cls");
		gotoxy(80, 1);
		setcolor(2);
		wcout << L"Điểm số của bạn hiện tại:" << score << endl;
		if (i != 0) {
			gotoxy(80, 2);
			wcout << L"Đúng:" << right << "\tSai:" << i - right << endl;
		}
		//Đáp án đúng:
		wstring right_answer = list[i].getEnglish();
		wstring option[4];
		option[0] = list[i].getEnglish();
		int pos1 = i, pos2 = i, pos3 = i;
		do {
			pos1 = rand() % n;
		} while (pos1 == i);

		do {
			pos2 = rand() % n;
		} while (pos2 == i || pos2 == pos1);

		do {
			pos3 = rand() % n;
		} while (pos3 == i || pos3 == pos1 || pos3 == pos2);

		//Sau khi random ra 4 index khác nhau ta tiến hành cho vào mảng rồi shuffle mảng
		//này lên
		option[1] = list[pos1].getEnglish();
		option[2] = list[pos2].getEnglish();
		option[3] = list[pos3].getEnglish();
		shuffle(option, 4);
		wstring question = list[i].toStringListVN();
		MouseListener m;
		wstring answer = m.getAnswer(option, question);
		gotoxy(0, 10);
		if (answer == L"Thoát")
			break;
		if (answer == right_answer) {
			right++;
			setcolor(2);
			wcout << L"->Bạn đã trả lời chính xác." << endl;
			score += list[i].getPoint();
			wcout << L"->Điểm số của bạn vừa được cộng thêm " << list[i].getPoint() << endl;
		}
		else {
			wrongAnswer.push_back(list[i]);
			setcolor(4);
			wcout << L"->Câu trả lời của bạn chưa chính xác." << endl;
			for (int i = 0; i < 4; i++)
				if (option[i] == right_answer) {
					setcolor(2);
					wcout << L"Câu trả lời chính xác là:" << (wchar_t)(i + L'A') << "." << option[i] << endl;
					break;
				}
		}
		ShowCur(0);
		int temp = _getch();
	}
	reviewVocab(wrongAnswer);
}
//Kiểm tra file có tồn tại không trước khi tiến hành xoá
bool user::isExistFileAlbum() {
	wchar_t path[100];
	wstrcpy(path, this->getPath());
	FILE* f = NULL;
	FILE** pFile = &f;
	_wfopen_s(pFile, path, L"r,ccs=UTF-16LE");
	if (f != NULL) {
		fclose(f);
		return true;
	}
	return false;
}

//Khi 1 file album từ vựng của user đang rỗng thì xoá nó đi
//để tránh rắc rối khi đăng nhập user thì lại đọc vào file rỗng
wstring user::getPath() {
	wstring res = L"account\\";
	res += this->getSimpleTk();
	res += L".txt";
	return res;
}

void user::deleteFileAlbum() {
	wstring pathFileAlbum = this->getPath();
	wstring del = L"del " + pathFileAlbum;
	char str[100];
	convertWstringToChar(str, del);
	system(str);
}

//Ghi toàn bộ album từ vựng của user xuống file
void user::ghiFileAlbum() {
	wchar_t* tenFile = this->getSimpleTk();
	wchar_t temp[100] = L"account\\";
	wstrcat(temp, tenFile);
	wstrcat(temp, L".txt");
	//Nếu album đang rỗng thì delete đi
	if (this->getAlbum()->getSoLuong() == 0) {
		FILE* f = NULL;
		FILE** pFile = &f;
		_wfopen_s(pFile, temp, L"r,ccs=UTF-16LE");
		if (f != NULL) {
			fclose(f);
			this->deleteFileAlbum();
		}
	}
	else this->getAlbum()->ghiFileVocab(temp);
}