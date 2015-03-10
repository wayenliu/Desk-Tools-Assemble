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
	//���ļ�
	int LoadFileByName();

	//�ӽ���
	char* AESEncrypt(char* strincode, char* stroutcode);
	char* AESDecrypt(char* strincode, char* stroutcode);

	//�ļ�����
	int InitFileHeader(map <int, filest*> tmpgrp, int inum, int inlen);
	//�����ļ�
	int ParseFileData(char* strindata, int ilen);

public:
	CFile m_filehandle;
	CString g_strFileName;
	int m_allbuflen;
	map <int, filest*> tmpmp;
	AES *aeshandle;
	int GetRetLenth(int ilenin);
};
