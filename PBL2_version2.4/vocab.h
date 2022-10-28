#pragma once
#include"thuvien.h"
class vocab {
private:
	wchar_t eng[30];
	wchar_t vn[10][30];
	wchar_t tuloai[10];
	wchar_t phienam[100];
	int sl, point;
	vocab* next;
	//sL: số lượng nghĩa tiếng việt
	//point: điểm dùng để đánh giá độ khó của từ
public:
	vocab();

	//Hàm tạo chỉ có tác dụng khi thực hiện phép gán ngay lúc khởi tạo 1 đối tượng mới
	/*
	Vd vocab a;
	vocab b=a; thi đúng
	nhưng vocab a,b;
	b=a; thì nó sẽ gọi hàm tạo mặc định
	*/
	vocab(const vocab& v);
	vocab(wchar_t eng[], wchar_t vn[][30], int sl, wchar_t phienam[], wchar_t tuloai[]);
	wchar_t* getKey();
	wchar_t* getEnglish();
	wchar_t* getTuLoai();

	wchar_t* getPhienAm();

	int getSoLuong();

	int getPoint();

	void setEnglish(wchar_t eng[]);

	void setVN(wchar_t vn[][30], int n);

	//Thiết lập duy nhất 1 nghĩa cho vocab, mục đích insertMultiMeaning trong HashtableMeaning
	void set1VN(vocab* v, int idx);

	void setTuLoai(wchar_t tuloai[]);

	void setPhienAm(wchar_t phienam[]);
	void setPoint(int point);
	void setSoLuong(int sl);

	void setNext(vocab* x);

	vocab* getNext();
	//th=1: ứng với việc display khi tra cứu
	//th=2: ứng với việc display khi in danh sách từ vựng
	void display(int th = 1);

	//Bỏ phương thức này
	void doc_file_1_vocab(wchar_t str[], int d, int p);

	void nhap_tt_1_vocab();

	//Update về phần dữ liệu của vocab chứ ko update vocab *next
	void updateData(vocab* v);

	wstring toStringListVN();

	//Nạp chồng 2 toán tử >,< để so sánh trong hàm quicksort
	bool operator > (vocab a);

	bool operator < (vocab a);

	vocab operator = (const vocab& v);
	//Làm việc với file
	void doc_file_1_vocab(FILE* f);
};