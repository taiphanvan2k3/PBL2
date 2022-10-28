#pragma once
#include"thuvien.h"
class Menu {
private:
	/*
	0: đen
	1: xanh dương đậm
	2: xanh lá cây
	3: xanh dương nhạt
	4: đỏ
	5: tím
	6: vàng đậm
	7: xám
	8: xám đen
	14: màu da
	*/
public:
	Menu();
	void box(wstring task, int x, int y, int h, int w, int t_color, int b_color);
	void thanh_sang2(wstring str, int x, int y, int w, int h, int t_color, int b_color);
	void n_box(wstring task[], int x, int y, int w, int b);
	void in_tieu_de(wstring task[], int x, int y, int w, int b);
	void updateTask(wstring task[], int th);
};
