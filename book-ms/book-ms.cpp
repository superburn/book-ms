﻿#define _CRT_SECURE_NO_WARNINGS
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

int GetSelect() {
    char buf[256];
    gets_s(buf);
    return atoi(buf);
}

void GuideInput() {
    char inName[NUM1];
    char inIsbn[NUM1];
    char inPrice[NUM2];
    char inAuthor[NUM2];
    
    cout << "输入书名：" << endl;
    cin >> inName;
    cout << "输入ISBN:" << endl;
    cin >> inIsbn;
    cout << "输入价格：" << endl;
    cin >> inPrice;
    cout << "输入作者：" << endl;
    cin >> inAuthor;

    CBook book(inName, inIsbn, inPrice, inAuthor);
    book.WriteData();
    cout << "Write Finish" << endl;
    WaitUser();
 }

long GetFileLength(ifstream& ifs) {
    long tmppos;
    long respos;
    tmppos = ifs.tellg();
    ifs.seekg(0, ios::end);
    respos = ifs.tellg();
    ifs.seekg(tmppos, ios::beg);
    return respos;
}

void ViewData(int iSelPage = 1) {
    int iPage = 0;
    int iCurPage = 0;
    int iDataCount = 0;
    char inName[NUM1];
    char inIsbn[NUM1];
    char inPrice[NUM2];
    char inAuthor[NUM2];
    bool bIndex = false;
    int iFileLength;
    iCurPage = iSelPage;

    ifstream ifs;
    ifs.open("E:\\book.txt", ios::binary);
    iFileLength = GetFileLength(ifs);
    iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
    if (iDataCount >= 1) {
        bIndex = true;
    }
    iPage = iDataCount / 20 + 1;
    ClearScreen();
    cout << "共有记录" << iDataCount << " ";
    cout << "共有页数" << iPage << " ";
    cout << "当前页数" << iCurPage << " ";
    cout << "n显示下一页 m返回" << endl;
    cout << setw(5) << "Index";
    cout << setw(22) << "Name" << setw(22) << "Isbn";
    cout << setw(5) << "Price" << setw(15) << "Author";
    cout << endl;
    try {
        ifs.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        if (!ifs.fail()) {
            for (int i = 1; i < 21; i++) {
                memset(inName, 0, NUM1);
                memset(inIsbn, 0, NUM1);
                memset(inPrice, 0, NUM2);
                memset(inAuthor, 0, NUM2);
                if (bIndex) {
                    cout << setw(3) << (iCurPage - 1) * 20 + i << endl;
                }
                ifs.read(inName, NUM1);
                cout << setw(24) << inName;
                ifs.read(inIsbn, NUM1);
                cout << setw(24) << inIsbn;
                ifs.read(inPrice, NUM2);
                cout << setw(12) << inPrice;
                ifs.read(inAuthor, NUM2);
                cout << setw(12) << inAuthor;
                if (ifs.tellg() < 0) {
                    bIndex = false;
                }
                else
                {
                    bIndex = true;
                }
            }
        }
    }
    catch (...) {
        cout << "throw file exception" << endl;
        throw "file error occured";
        ifs.close();
    }
    if (iCurPage < iPage) {
        iCurPage++;
    }
    else {
        WaitUser();
    }
    ifs.close();
}

void DeleteBookFromFile() {
    int iDelCount;
    cout << "Input delete index" << endl;
    cin >> iDelCount;
    CBook tmpbook;
    tmpbook.DeleteData(iDelCount);
    cout << "Delete Finish" << endl;
    WaitUser();
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
            GuideInput();
            break;
        case 2:
            ClearScreen();
            ViewData();
            break;
        case 3:
            ClearScreen();
            DeleteBookFromFile();
            break;
        }
    }
}

void WaitView(int iCurPage) {
    char buf[256];
    gets_s(buf);
    if (buf[0] == 'q') {
        system("exit");
    }
    if (buf[0] == 'm') {
        mainloop();
    }
    if (buf[0] == 'n') {
        ViewData(iCurPage);
    }
}

int main()
{
    SetScreenGrid();
    SetSysCaption("图书管理系统");
    mainloop();
}