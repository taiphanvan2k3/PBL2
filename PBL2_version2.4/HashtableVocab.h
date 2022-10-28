#pragma once
#include"Hashtable.cpp"
class HashtableVocab :public Hashtable<vocab> {
public:
	HashtableVocab();

	void insert(vocab* x);

	void deleteVocab(wstring key);

	//In theo trang này được dùng cho phương thức inTuVungHeThong
	void InTheoTrang(vocab* ds, int n, int page, int page_max);

	void InTuVungTangDan();

	void ghiFileVocab(wchar_t* tenFile);
};