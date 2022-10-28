#pragma once
#include"account.h"
class user :public account {
private:
	HashtableVocab* album;

	//Tạo ra biến này nhằm mục đích, chỉ những tài khoản nào chưa đăng nhập vào hệ thống
	//kể từ lúc mở chương trình thì mới đọc từ file lên
	bool firstLogin;
	user* next;
public:
	user();

	user(const wchar_t tk[], const wchar_t mk[]) :account(tk, mk) {
		this->album = NULL;
		this->next = NULL;
		this->firstLogin = true;
	};

	void setNext(user* x);

	user* getNext();

	bool getFirstLogin();

	void setFirstLogin();

	HashtableVocab* getAlbum();

	/*Biến th này chỉ cần thiết bên manager, vì ta đang kế thừa từ lớp account nên phải override lại
	đúng phương thức temTuVung này như trong class cha*/
	void themTuVung(vocab* v, int th = 1);

	//Thêm từ vựng vào album dựa trên từ vựng có sẵn có admin
	void themTuVungVersion(vocab* ds, int n, int page, bool* checkStatus);

	//Phương thức này sẽ tự động gọi khi user đăng nhập thành công
	void docFileAlbum();

	void traCuuTuVungAnhViet();

	void traCuuTuVungVietAnh();

	//User chỉ có quyền xoá từ vựng trong album của họ thôi chứ không có quyền xoá vào từ vựng hệ thống
	void xoaTuVung();

	void InTuVungAlbum();

	//Gọi phương thức này khi đăng kí tk user hoặc đăng nhập thành công
	void loadTuVungHeThong(HashtableVocab* vocabHeThong);

	void gameDienTu();

	void gameChonDapAnDung();

	//Kiểm tra file có tồn tại không trước khi tiến hành xoá
	bool isExistFileAlbum();

	/*Khi 1 file album từ vựng của user đang rỗng thì xoá nó đi
	để tránh rắc rối khi đăng nhập user thì lại đọc vào file rỗng*/
	wstring getPath();

	void deleteFileAlbum();

	//Ghi toàn bộ album từ vựng của user xuống file
	void ghiFileAlbum();
};