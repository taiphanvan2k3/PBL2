#include"MouseListener.h"

MouseListener::MouseListener() {
    ShowCur(0);
}

void MouseListener::WriteError(LPSTR lpszMessage) {
    printf("%s\n", lpszMessage);
    ExitProcess(0);
}

void MouseListener::paintButtonExit(int background) {
    Menu m;
    m.box(L"  Thoát", 70, 7, 2, 10, 3, background);
}
void MouseListener::paint(wstring option[],wstring question) {
    gotoxy(45, 3);
    wcout << "Question: "<<question;
    setcolor(6);
    gotoxy(42, 4);
    wcout << "A." << left << setw(20) << option[0] << "B." << option[1] << endl;
    gotoxy(42, 5);
    wcout << "C." << left << setw(20) << option[2] << "D." << option[3] << endl;
    paintButtonExit(0);
    setcolor(7);

    if (x >= 42 && x <= 82 && (y == 4 || y == 5)) {
        if (y == 4) {
            if (x == 42)
                idx = 0;
            else idx = 1;
        }
        else {
            if (x == 42)
                idx = 2;
            else idx = 3;
        }
        setcolor(4);
        gotoxy(x, y);
        if (idx == 1 || idx == 3)
            wcout << "  ";
        wcout <<wchar_t(idx+'A')<<"."<< option[idx];
        setcolor(7);
    }
    else if (70 <= x && x <= 80 && 7 <= y && y <= 9)
        paintButtonExit(4);
}
// hàm này để lấy vị trí chuột trên std
void MouseListener::GetMousePosWin(MOUSE_EVENT_RECORD mer) {
    // Khai báo các biến mà hàm cần
    INPUT_RECORD Inrec;
    DWORD eventRead;
    HANDLE hStdIn;
    DWORD dwMode;
    bool Captured = false;
    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    dwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

    //Kiểm tra xem console đã ở chế độ chấp nhận input từ chuột chưa
    if (SetConsoleMode(hStdIn, dwMode | ENABLE_MOUSE_INPUT))
        GetConsoleMode(hStdIn, &dwMode);
    SetConsoleMode(hStdIn, (dwMode & (ENABLE_MOUSE_INPUT)));
    // vòng lặp này sẽ lấy các event của trong bộ nhớ ra để xử lý
    do {
        PeekConsoleInput(hStdIn, &Inrec, 1, &eventRead);
        if (eventRead) {
            ReadConsoleInput(hStdIn, &Inrec, 1, &eventRead);
            x = Inrec.Event.MouseEvent.dwMousePosition.X;
            y = Inrec.Event.MouseEvent.dwMousePosition.Y;
            switch (Inrec.EventType) {
                case MOUSE_EVENT: {
                    Captured = true;
                    if (y == 4 || y == 5) {
                        if (x >= 62)
                            x = 62;
                        else if (x >= 42)
                            x = 42;
                    }
                    else if (7 <= y && y <= 9) {
                        if (70 <= x && x <= 80)
                            idx = -1;
                    }
                    break;
                }
            }
        }

    } while (!Captured);
}

wstring MouseListener::getAnswer(wstring ds[],wstring question) {

    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int counter = 0;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        WriteError("GetStdHandle");

    fdwMode = ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode)) {
        WriteError("SetConsoleMode");
    }

    // Mở cửa sổ ở chế độ chấp nhận input 
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode)) {
        WriteError("SetConsoleMode");
    }
    setcolor(7);
    paint(ds,question);
    // Vòng lặp để quét qua các event 
    while (!counter)
    {
        // đọc event vào
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            WriteError("ReadConsoleInput");
        }
        //xử lý từng event một
        for (i = 0; i < cNumRead; i++)
        {
            switch (irInBuf[i].EventType) {
            case MOUSE_EVENT:
                // khi có event của chuột (rê chuột,...)
                GetMousePosWin(irInBuf[i].Event.MouseEvent);
                paint(ds,question);
                if (GetAsyncKeyState(0x01)) {
                    if (idx == -1)
                        return L"Thoát";
                    return ds[idx];
                }
                break;
            }
        }
    }
}