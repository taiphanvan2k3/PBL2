#pragma once
#include"Hashtable.cpp"
class HashtableMeaning :public Hashtable<vocab> {
	//class này sẽ được gọi khi user đăng nhập tài khoản thành công
public:
	~HashtableMeaning() {}

	vocab* search(wstring str);

	/*
	Ban đầu kiểm tra phần vn của từ vựng đó xem đã có trong HashtableMeaning chưa
	Nếu chưa thì return false ( chưa tồn tại), ta chuẩn bị thêm vocab đó vào HashtableMeaning
	Ngược lại, duyệt trên dslk của temp xem có node nào có eng = x->getEng() không, nếu có thì
	đã tồn tại =>return true
	vd ban đầu có node [bàn ăn]->table, bây giờ lại thêm vào vocab (table,bàn ăn) thì không cho thêm
	Tránh trường hợp không check điều kiện thì khi tra cứu từ điển Việt-Anh với từ bàn ăn thì nó hiển
	thị ra 2 từ table
	*/
	bool checkIsExist(vocab* x);
	void insertMultiMeaning(vocab* x);

	void insert(vocab* x);
	void deleteMeaning(vocab* x);
	void deleteMultiMeaning(wstring eng,wstring vn);
	//Tra cứu từ vựng Việt-Anh
	void traCuu(wstring str);
};