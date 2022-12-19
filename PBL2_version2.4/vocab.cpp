#include"vocab.h"
vocab::vocab() {
	wstrcpy(this->eng, L"");
	wstrcpy(this->phienam, L"");
	wstrcpy(this->tuloai, L"");
	this->sl = this->point = 0;
	this->next = NULL;
}
//Hàm tạo chỉ có tác dụng khi thực hiện phép gán ngay lúc khởi tạo 1 đối tượng mới
/*
Vd vocab a;
vocab b=a; thi đúng
nhưng vocab a,b;
b=a; thì nó sẽ gọi hàm tạo mặc định
*/
vocab::vocab(const vocab& v) {
	this->next = NULL;
	wstrcpy(this->eng, v.eng);
	this->sl = v.sl;
	for (int i = 0; i < sl; i++)
		wstrcpy(this->vn[i], v.vn[i]);
	wstrcpy(this->phienam, v.phienam);
	wstrcpy(this->tuloai, v.tuloai);
	this->point = v.point;
}

vocab vocab::operator=(const vocab& v) {
	if (this != &v) {
		wstrcpy(this->eng, v.eng);
		this->sl = v.sl;
		for (int i = 0; i < sl; i++)
			wstrcpy(this->vn[i], v.vn[i]);
		wstrcpy(this->phienam, v.phienam);
		wstrcpy(this->tuloai, v.tuloai);
		this->point = v.point;
	}
	return *this;
}

vocab::vocab(wchar_t eng[], wchar_t vn[][30], int sl, wchar_t phienam[], wchar_t tuloai[]) {
	this->setEnglish(eng);
	this->setVN(vn, sl);
	this->setTuLoai(tuloai);
	this->setPhienAm(phienam);
}

wchar_t* vocab::getKey() {
	return this->eng;
}

wchar_t* vocab::getEnglish() {
	return this->eng;
}

wchar_t* vocab::getTuLoai() {
	return this->tuloai;
}

wchar_t* vocab::getPhienAm() {
	return this->phienam;
}

int vocab::getSoLuong() {
	return this->sl;
}

int vocab::getPoint() {
	return this->point;
}

void vocab::setEnglish(wchar_t eng[]) {
	wstrcpy(this->eng, eng);
}

void vocab::setVN(wchar_t vn[][30], int n) {
	this->sl = n;
	for (int i = 0; i < n; i++)
		wstrcpy(this->vn[i], vn[i]);
}

//Thiết lập duy nhất 1 nghĩa cho vocab, mục đích insertMultiMeaning trong HashtableMeaning
void vocab::set1VN(vocab* v, int idx) {
	wstrcpy(this->vn[0], v->vn[idx]);
}

void vocab::setTuLoai(wchar_t tuloai[]) {
	wstrcpy(this->tuloai, tuloai);
}

void vocab::setPhienAm(wchar_t phienam[]) {
	wstrcpy(this->phienam, phienam);
}
void vocab::setPoint(int point) {
	this->point = point;
}
void vocab::setSoLuong(int sl) {
	this->sl = sl;
}

void vocab::setNext(vocab* x) {
	this->next = x;
}

vocab* vocab::getNext() {
	return this->next;
}
//th=1: ứng với việc display khi tra cứu
//th=2: ứng với việc display khi in danh sách từ vựng
void vocab::display(int th) {
	wchar_t c[20];
	if (wstrcmp(tuloai, L"verb") == 0)
		wstrcpy(c, L"v");
	else if (wstrcmp(tuloai, L"noun") == 0)
		wstrcpy(c, L"n");
	else if (wstrcmp(tuloai, L"adjective") == 0)
		wstrcpy(c, L"adj");
	else if (wstrcmp(tuloai, L"adverb") == 0)
		wstrcpy(c, L"adv");
	else if (wstrcmp(tuloai, L"preposition") == 0)
		wstrcpy(c, L"pre");
	if (th == 1) {
		wprintf(L"%s", eng);
		wprintf(L"%s", phienam);
		wprintf(L"(%s):", c);
		for (int i = 0; i < sl - 1; i++)
			wprintf(L"%s,", vn[i]);
		wprintf(L"%s.", vn[sl - 1]);
	}
	else {
		wcout << L"\t│";
		setcolor(6);
		wcout << left << setw(20) << eng;
		setcolor(7);
		wcout << L"│";
		setcolor(2);
		wcout << left << setw(20) << phienam;
		setcolor(7);
		wcout << L"│";
		if (wstrcmp(tuloai, L"noun") == 0)
			setcolor(3);
		if (wstrcmp(tuloai, L"adjective") == 0)
			setcolor(5);
		if (wstrcmp(tuloai, L"verb") == 0)
			setcolor(4);
		if (wstrcmp(tuloai, L"adverb") == 0)
			setcolor(2);
		wcout << left << setw(15) << tuloai;
		setcolor(7);
		wcout << L"│";
		setcolor(6);
		wcout << left << setw(35) << toStringListVN();
		setcolor(7);
		wcout << L"│";
		//wcout << L"\t│" << left << setw(20) << eng << L"│" << left << setw(20) << phienam << L"│" << left << setw(15) << tuloai << L"│" << left << setw(35) << toStringListVN() << L"│";
	}
}

//Bỏ phương thức này
void vocab::doc_file_1_vocab(wchar_t str[], int d, int p) {
	wchar_t ds[3][100];
	int k = 0, n = (int)wcslen(str), idx = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == '-') {
			ds[k][idx] = L'\0';
			k++;
			idx = 0;
		}
		else ds[k][idx++] = str[i];
	}
	ds[2][idx] = '\0';
	this->setEnglish(ds[0]);
	this->setTuLoai(ds[2]);
	this->setPoint(p);
	wchar_t vn[10][30];
	n = (int)wcslen(ds[1]);
	k = 0, idx = 0;
	for (int i = 0; i < n; i++) {
		if (ds[1][i] == ',') {
			vn[k][idx] = '\0';
			k++;
			idx = 0;
		}
		else vn[k][idx++] = ds[1][i];
	}
	vn[k][idx] = L'\0';
	this->setVN(vn, d);
}

void vocab::nhap_tt_1_vocab() {
	setcolor(3);
	wprintf(L"Hệ thống chưa có chức năng tự động thêm phiên âm do đó phiền bạn nhập phiên âm:");
	setcolor(6);
	_getws_s(phienam);
	int lc;
	do {
		system("cls");
		setcolor(2);
		wprintf(L"Nhập nghĩa thứ %d:", this->sl + 1);
		setcolor(6);
		_getws_s(vn[this->sl]);
		formatInput(vn[this->sl]);
		sl++;
		setcolor(2);
		wprintf(L"Bạn có muốn thêm nghĩa nào khác không ?\n");
		wprintf(L"Nhập 1-Yes,0-No: ");
		setcolor(6);
		wscanf_s(L"%d", &lc);
		int c = (int)getwchar();
	} while (lc);
	setcolor(2);
	wprintf(L"Từ loại:");
	setcolor(6);
	_getws_s(tuloai);
	setcolor(2);
	wprintf(L"Nhập giá trị điểm khi trả lời đúng từ vựng này:");
	setcolor(6);
	wscanf_s(L"%d", &point);
	int c = (int)getwchar();
}

//Update về phần dữ liệu của vocab chứ ko update vocab *next
void vocab::updateData(vocab* v) {
	this->sl = v->sl;
	for (int i = 0; i < sl; i++)
		wstrcpy(this->vn[i], v->vn[i]);
	wstrcpy(this->phienam, v->phienam);
	wstrcpy(this->tuloai, v->tuloai);
	this->point = v->point;
}

wstring vocab::toStringListVN() {
	wstring res = L"";
	for (int i = 0; i < sl; i++) {
		res += vn[i];
		if (i < sl - 1) res += ',';
	}
	return res;
}

//Nạp chồng 2 toán tử >,< để so sánh trong hàm quicksort
bool vocab::operator > (vocab a) {
	return (wstrcmp(this->eng, a.eng) > 0);
}

bool vocab::operator < (vocab a) {
	return (wstrcmp(this->eng, a.eng) < 0);
}

bool vocab::operator == (const vocab a) {
	return (wstrcmp(this->eng,a.eng) == 0);
}

//Làm việc với file
void vocab::doc_file_1_vocab(FILE* f) {
	wchar_t phienam[100];
	fgetws(phienam, 100, f);
	if (wstrcmp(phienam, L"") == 0) {
		wcout << L"File đang rỗng.";
		return;
	}
	if (phienam[wcslen(phienam) - 1] == '\n')
		phienam[wcslen(phienam) - 1] = '\0';
	this->setPhienAm(phienam);

	wchar_t str[100];
	fgetws(str, 100, f);
	if (str[wcslen(str) - 1] == '\n')
		str[wcslen(str) - 1] = '\0';
	int n = (int)wcslen(str);
	int p = str[n - 1] - '0';
	int sl = str[n - 3] - '0';
	str[n - 4] = L'\0';
	this->doc_file_1_vocab(str, sl, p); 
}