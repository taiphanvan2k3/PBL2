#include"Menu.h"
class MouseListener {
    HANDLE hStdin;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;
    //x,y: lưu vị trí hiện tại của chuột
    int x, y, idx;
public:
    //Ghi lỗi và thoát ra
    MouseListener();
    void WriteError(LPSTR lpszMessage);
    void paint(wstring ds[],wstring question);
    void paintButtonExit(int background);
    // hàm này để lấy vị trí chuột trên std
    void GetMousePosWin(MOUSE_EVENT_RECORD mer);
    wstring getAnswer(wstring ds[],wstring question);
};