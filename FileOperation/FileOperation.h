#pragma once
#include <fstream>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include "AES.h"
#include "CommonDef.h"
using namespace std;

class CFileOperation
{
public:
	CFileOperation();
	~CFileOperation();

public:
	//读文件
	int LoadFileByName();

	//加解密
	char* AESEncrypt(char* strincode, char* stroutcode);
	char* AESDecrypt(char* strincode, char* stroutcode);

	//文件操作
	int InitFileHeader(map <int, filest*> tmpgrp, int inum, int inlen);
	//解析文件
	int ParseFileData(char* strindata, int ilen);

public:
	CFile m_filehandle;
	CString g_strFileName;
	int m_allbuflen;
	map <int, filest*> tmpmp;
	AES *aeshandle;
	int GetRetLenth(int ilenin);
};
