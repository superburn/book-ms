#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include "Book.h"

#define CMD_COLS 90
#define CMD_LINES 25

using namespace std;

int main()
{
    
}

void SetScreenGrid(){
    char sysSetBuf[80];
    sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
    system(sysSetBuf);
}

void SetSysCaption() {
    system("title Sample");
}

void ClearScreen() {
    system("cls");
}

void SetSysCaption(const char* pText) {
    char sysSetBuf[80];
    sprintf(sysSetBuf, "title %s", pText);
    system(sysSetBuf);
}

void ShowWelcome() {
    for (int i = 0; i < 7; i++) {
        cout << endl;
    }
    cout << setw(40);
    cout << "**************" << endl;
    cout << setw(40);
    cout << "图书管理系统" << endl;
    cout << setw(40);
    cout << "**************" << endl;
}

void ShowRootMenu() {
    cout << setw(40);
    cout << "请选择功能" << endl;
    cout << endl;
    cout << setw(38);
    cout << "1 添加新书" << endl;
    cout << endl;
    cout << setw(38);
    cout << "2 浏览全部" << endl;
    cout << endl;
    cout << setw(38);
    cout << "3 删除图书" << endl;
}

void WaitUser() {
    int iInputPage = 0;
    cout << "enter：返回主菜单 q:退出" << endl;
    char buf[256];
    gets_s(buf);
    if (buf[0] == 'q') {
        system("exit");
    }
}

void mainloop() {
    ShowWelcome();
    while (1) {
        ClearScreen();
        ShowWelcome();
        ShowRootMenu();
        switch (GetSelect())
        {
        case 1:
            ClearScreen();
            //GuideInput();
            break;
        case 2:
            ClearScreen();
            //ViewData();
            break;
        case 3:
            ClearScreen();
            //DeleteBookFromFile();
            break;
        }
    }
}

int GetSelect() {
    char buf[256];
    gets_s(buf);
    return atoi(buf);
}