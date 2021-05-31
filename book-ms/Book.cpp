#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

CBook::CBook(char* cName, char* cIsbn, char* cPrice, char* cAuthor) {
    strncpy_s(m_cname, cName, NUM1);
    strncpy_s(m_cIsbn, cIsbn, NUM1);
    strncpy_s(m_cPrice, cPrice, NUM2);
    strncpy_s(m_cAuthor, cAuthor, NUM2);
}

char* CBook::GetName() {
    return m_cname;
}

void CBook::SetName(char* cName) {
    strncpy(m_cname, cName, NUM1);
}

char* CBook::GetIsbn() {
    return m_cIsbn;
}

void CBook::SetIsbn(char* cIsbn) {
    strncpy_s(m_cIsbn, cIsbn, NUM1);
}

char* CBook::GetPrice() {
    return m_cPrice;
}

void CBook::SetPrice(char* cPrice) {
    strncpy_s(m_cPrice, cPrice, NUM2);
}

char* CBook::GetAuthor() {
    return m_cAuthor;
}

void CBook::SetAuthor(char* cAuthor) {
    strncpy_s(m_cAuthor, cAuthor, NUM2);
}

//将图书对象写入到文件中
void CBook::WriteData() {
    ofstream ofs;
    ofs.open("E:\\book.txt", ios::binary | ios::app);
    try {
        ofs.write(m_cname, NUM1);
        ofs.write(m_cIsbn, NUM1);
        ofs.write(m_cPrice, NUM2);
        ofs.write(m_cAuthor, NUM2);
    }
    catch (...) {
        throw "file error occurred";
        ofs.close();
    }
    ofs.close();
}

//从文件中读取数据来构建对象
void CBook::GetBookFromFile(int iCount) {
    ifstream ifs;
    ifs.open("E:\\book.txt", ios::binary);
    char cName[NUM1];
    char cIsbn[NUM1];
    char cPrice[NUM2];
    char cAuthor[NUM2];
    try {
        ifs.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        ifs.read(cName, NUM1);
        if (ifs.tellg() > 0) {
            strncpy(m_cname, cName, NUM1);
        }
        ifs.read(cIsbn, NUM1);
        if (ifs.tellg() > 0) {
            strncpy_s(m_cIsbn, cIsbn, NUM1);
        }
        ifs.read(cPrice, NUM2);
        if (ifs.tellg() > 0) {
            strncpy_s(m_cPrice, cPrice, NUM2);
        }
        ifs.read(cAuthor, NUM2);
        if (ifs.tellg() > 0) {
            strncpy_s(m_cAuthor, cAuthor, NUM2);
        }
    }
    catch (...) {
        throw "file error occurred";
        ifs.close();
    }
    ifs.close();
}

//将图书信息从文件中删除
void CBook::DeleteData(int iCount) {
    long resPos;
    int iDataCount = 0;
    fstream file;
    fstream tempFile;
    ofstream ofile;
    char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
    file.open("E:\\book.txt", ios::binary | ios::in | ios::out);
    tempFile.open("E:\\temp.txt", ios::binary | ios::in | ios::out | ios::trunc);
    file.seekg(0, ios::end);
    resPos = file.tellg();
    iDataCount = resPos / (NUM1 + NUM1 + NUM2 + NUM2);
    if (iCount < 0 || iCount > iDataCount) {
        throw "Input number error";
    }
    else {
        file.seekg((iCount) * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        for (int j = 0; j < (iDataCount - iCount); j++) {
            memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
            file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
            tempFile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
        }
        file.close();
        tempFile.seekg(0, ios::beg);
        ofile.open("E:\\book.txt");
        ofile.seekp((iCount - 1) * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        for (int i = 0; i < (iDataCount - iCount); i++) {
            memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
            tempFile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
            ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
        }
    }
    tempFile.close();
    ofile.close();
    remove("E:\\temp.txt");
}