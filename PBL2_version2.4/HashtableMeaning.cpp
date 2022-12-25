#pragma once
#include"HashtableMeaning.h"

vocab* HashtableMeaning::search(wstring str) {
	/*overiding lại phương thức này ở lớp cha
	vì ta đã xây dựng class Hashtable mà trong đó vocab có key là eng
	trong khi bây giờ HashtableMeaning đang mong muốn key là vn*/
	convert(str);
	int id = hash(str);
	vocab* tam = heads[id];
	while (tam) {
		if (tam->toStringListVN() == str)
			return tam;
		tam = tam->next;
	}
	return NULL;
}

/*
Ban đầu kiểm tra phần vn của từ vựng đó xem đã có trong HashtableMeaning chưa
Nếu chưa thì return false ( chưa tồn tại), ta chuẩn bị thêm vocab đó vào HashtableMeaning
Ngược lại, duyệt trên dslk của temp xem có node nào có eng = x->getEng() không, nếu có thì
đã tồn tại =>return true
vd ban đầu có node [di chuyển]->cut, bây giờ lại thêm vào vocab (cut,di chuyển) thì không cho thêm
Tránh trường hợp không check điều kiện thì khi tra cứu từ điển Việt-Anh với từ "di chuyển" thì nó hiển
thị ra kết quả là 2 từ "cut" khi ta tra cứu Việt-Anh với từ cut.
->Chỉ cho phép thêm vào khi thêm vào HashtableMeaning (di chuyển,move)
*/
bool HashtableMeaning::checkIsExist(vocab* x) {
	vocab* temp = this->search(x->toStringListVN());
	if (temp == NULL)
		return false;
	else {

		/*Phát hiện đã có key là x->toStringListVN() trong HashtableMeaning rồi
		Bây giờ kiểm tra xem đã có nghĩa tiếng anh đó chưa thì mới cho phép thêm vào*/
		while (temp) {
			if (wstrcmp(temp->getEnglish(), x->getEnglish()) == 0)
				return true;
			temp = temp->next;
		}
		return false;
	}
}
void HashtableMeaning::insertMultiMeaning(vocab* x) {
	int id = hash(x->toStringListVN());
	if (heads[id] == NULL)
		listId.push_back(id);
	num++;
	insertIntoLinkList(heads[id], x);
}

void HashtableMeaning::insert(vocab* x) {
	int n = x->getSoLuong();
	vocab** ds = new vocab * [n];
	for (int i = 0; i < n; i++) {
		ds[i] = new vocab;
		ds[i]->setEnglish(x->getEnglish());
		ds[i]->updateData(x);
		//*ds[i] = *x;
		ds[i]->setSoLuong(1);
		ds[i]->set1VN(x, i);
		if (!checkIsExist(ds[i]))
			insertMultiMeaning(ds[i]);
	}
}

void HashtableMeaning::deleteMeaning(vocab* x) {
	int n = x->getSoLuong();
	for (int i = 0; i < n; i++)
		this->deleteMultiMeaning(x->eng,x->vn[i]);
}

void HashtableMeaning::deleteMultiMeaning(wstring eng,wstring vn) {
	int idx = this->hash(vn);
	vocab* after = heads[idx], * before = NULL;
	while (after && wstrcmp(after->eng, eng) != 0) {
		before = after;
		after = after->next;
	}
	
	if (after != NULL) {
		if (after == heads[idx])
			heads[idx] = after->next;
		else before->next = after->next;
		delete after;
	}
}

//Tra cứu từ vựng Việt-Anh
void HashtableMeaning::traCuu(wstring str) {
	vocab* temp = this->search(str);
	if (temp == NULL) {
		setcolor(4);
		wcout << L"Không tìm thấy kết quả nào." << endl;
	}
	else {
		while (temp) {
			/*Trên danh sách liên kết của các vocab có cùng id sau khi băm trường vn của chúng ra
			thì đôi lúc 2 từ khác nhau về nghĩa tiếng Việt nhưng do băm ra với cùng một id nên 
			chúng vẫn cùng nằm trên một danh sách liên kết. Do đó trước khi in ra một node thì có thêm bước 
			kiểm tra node đó có trường vn giống với từ tiếng Việt mà ta đi tìm kiếm hay không mới in ra.*/
			if(temp->toStringListVN() == str)
				wcout << "\n\t+" << temp->getTuLoai() << ":" << temp->getEnglish();
			temp = temp->next;
		}
		wcout << endl;
	}
	setcolor(7);
}