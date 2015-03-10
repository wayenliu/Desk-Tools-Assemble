#include "StdAfx.h"
#include "FileOperation.h"


CFileOperation::CFileOperation()
{
}

CFileOperation::~CFileOperation()
{
}

int CFileOperation::LoadFileByName()
{
	g_strFileName.Format(_T(".\\Conf\\DTA.cfg"));
	int ret = m_filehandle.Open(g_strFileName, CFile::modeRead);
	ret = GetLastError();

	ULONG iflen = m_filehandle.GetLength();

	char *tmpbuf = new char[iflen + 1];
	memset(tmpbuf, 0, iflen + 1);

	m_filehandle.Read(tmpbuf, iflen);
	m_filehandle.Close();
	
	int rgpnum = ParseFileData(tmpbuf, iflen);
	return rgpnum;
}

char* CFileOperation::AESEncrypt(char* strincode, char* stroutcode)
{
	return NULL;
}

char* CFileOperation::AESDecrypt(char* strincode, char* stroutcode)
{
	return NULL;
}

int CFileOperation::ParseFileData(char* strindata, int ilen)
{
	int inum = 0;

	if (strindata[0] == 0x0C && strindata[1] == 0x0D && strindata[2] == 0x0A && strindata[3] == 0x0E && strindata[4] == 0x0F)
	{//是文件
		char *allbuf = new char[ilen - 5];
		memset(allbuf, 0, ilen - 5);
		memcpy(allbuf, strindata + 5, ilen - 5);

		int iend = 0;
		//		
		int igrplen = 0;
		int ifnamelen = 0;
		int ifpathlen = 0;
		char *tmpbuf;
		//
		while(iend <= (ilen - 5))
		{
			//一轮拼装解密:
			//grp
			aeshandle = new AES((BYTE*)g_key);
			memcpy((char*)&igrplen, allbuf + iend, 4);//len
			tmpbuf = new char[igrplen + 1];
			memset(tmpbuf, 0, igrplen + 1);
			iend += 4;
			memcpy(tmpbuf, allbuf + iend, igrplen);
			iend += igrplen;
			iend += 1;
		
			char *tmpgrpdecodestr = new char[igrplen + 1];
			memset(tmpgrpdecodestr, 0, igrplen + 1);
			aeshandle->Decrypt((BYTE*)tmpbuf, (BYTE*)tmpgrpdecodestr, igrplen);
			
			delete aeshandle;
			aeshandle = NULL;
			delete []tmpbuf;
			tmpbuf = NULL;
			
			//fname
			aeshandle = new AES((BYTE*)g_key);
			memcpy((char*)&ifnamelen, allbuf + iend, 4);//len
			tmpbuf = new char[ifnamelen + 1];
			memset(tmpbuf, 0, ifnamelen + 1);
			iend += 4;
			memcpy(tmpbuf, allbuf + iend, ifnamelen);
			iend += ifnamelen;
			iend += 1;
			
			char *tmpfnamedecodestr = new char[ifnamelen + 1];
			memset(tmpfnamedecodestr, 0, ifnamelen + 1);
			aeshandle->Decrypt((BYTE*)tmpbuf, (BYTE*)tmpfnamedecodestr, ifnamelen);
			delete aeshandle;
			aeshandle = NULL;
			delete []tmpbuf;
			tmpbuf = NULL;

			//fpath
			aeshandle = new AES((BYTE*)g_key);
			memcpy((char*)&ifpathlen, allbuf + iend, 4);//len
			tmpbuf = new char[ifpathlen + 1];
			memset(tmpbuf, 0, ifpathlen + 1);
			iend += 4;
			memcpy(tmpbuf, allbuf + iend, ifpathlen);
			iend += ifpathlen;
			iend += 1;			

			char *tmpfpathdecodestr = new char[ifpathlen + 1];
			memset(tmpfpathdecodestr, 0, ifpathlen + 1);
			aeshandle->Decrypt((BYTE*)tmpbuf, (BYTE*)tmpfpathdecodestr, ifpathlen);
			delete aeshandle;
			aeshandle = NULL;
			delete []tmpbuf;
			tmpbuf = NULL;

			//后期处理
			filest *tmpfst = new filest;
			tmpfst->strgrpname = tmpgrpdecodestr;
			tmpfst->strfilename = tmpfnamedecodestr;
			tmpfst->strfilepath = tmpfpathdecodestr;

			tmpmp[inum] = tmpfst;
			
			delete []tmpgrpdecodestr;
			delete []tmpfnamedecodestr;
			delete []tmpfpathdecodestr;
			tmpgrpdecodestr = NULL;
			tmpfnamedecodestr = NULL;
			tmpfpathdecodestr = NULL;

			igrplen = 0;
			ifnamelen = 0;
			ifpathlen = 0;

			inum++;

			if (iend >= (ilen - 5))
			{
				return inum;
			}
			continue;
		}
	}
	else
	{
		return -1;
	}

	return inum;
}

int CFileOperation::InitFileHeader(map <int, filest*> m_tmpgrp, int inum, int inlen)
{
	g_strFileName.Format(_T(".\\Conf\\DTA.cfg"));
	int ipre = 5;
	int ilen = inlen + ipre;
	char *tmpbuf = new char[ilen];
	memset(tmpbuf, 0, ilen);
	
	tmpbuf[0] = 0x0C;
	tmpbuf[1] = 0x0D;
	tmpbuf[2] = 0x0A;
	tmpbuf[3] = 0x0E;
	tmpbuf[4] = 0x0F;

	map <int, filest*>::iterator  iter;
	for (iter = m_tmpgrp.begin(); iter != m_tmpgrp.end(); iter++)
	{
		aeshandle = new AES((BYTE*)g_key);

		CString strtmpgrpname = iter->second->strgrpname;
		CString strtmpfilename = iter->second->strfilename;
		CString strtmpfilepath = iter->second->strfilepath;

		int igrplen = strtmpgrpname.GetLength();
		int ifnamelen = strtmpfilename.GetLength();
		int ifpathlen = strtmpfilepath.GetLength();

		/////code
		//group
		int igrpretlen = GetRetLenth(igrplen);
		char *tmpgrpdata = new char[igrpretlen + 1];
		memset(tmpgrpdata, 0, igrpretlen + 1);
		aeshandle->Encrypt((BYTE *)strtmpgrpname.GetBuffer(), (BYTE *)tmpgrpdata, igrplen);
		memcpy(tmpbuf + ipre, (char*)&igrpretlen, 4);
		memcpy(tmpbuf + ipre + 4, tmpgrpdata, igrpretlen);

		//filename
		int ifnameretlen = GetRetLenth(ifnamelen);
		char *tmpfnamedata = new char[ifnameretlen + 1];
		memset(tmpfnamedata, 0, ifnameretlen + 1);
		aeshandle->Encrypt((BYTE *)strtmpfilename.GetBuffer(), (BYTE *)tmpfnamedata, ifnamelen);
		memcpy(tmpbuf + ipre + 4 + igrpretlen + 1, (char*)&ifnameretlen, 4);
		memcpy(tmpbuf + ipre + 4 + igrpretlen + 1 + 4, tmpfnamedata, ifnameretlen);

		//filepath
		int ifpathretlen = GetRetLenth(ifpathlen);
		char *tmpfpathdata = new char[ifpathretlen + 1];
		memset(tmpfpathdata, 0, ifpathretlen + 1);
		aeshandle->Encrypt((BYTE *)strtmpfilepath.GetBuffer(), (BYTE *)tmpfpathdata, ifpathlen);
		memcpy(tmpbuf + ipre + 4 + igrpretlen + 1 + 4 + ifnameretlen + 1, (char*)&ifpathretlen, 4);
		memcpy(tmpbuf + ipre + 4 + igrpretlen + 1 + 4 + ifnameretlen + 1 + 4, tmpfpathdata, ifpathretlen);

		ipre += (igrpretlen + 1 + ifnameretlen + 1 + ifpathretlen + 1 + 12);

		aeshandle->~AES();
		delete []tmpgrpdata;
		tmpgrpdata = NULL;
		delete []tmpfnamedata;
		tmpfnamedata = NULL;
		delete []tmpfpathdata;
		tmpfpathdata = NULL;
	}

	m_filehandle.Open(g_strFileName, CFile::modeWrite | CFile::modeCreate);
	m_filehandle.Write(tmpbuf, ilen);
	m_filehandle.Close();

	delete []tmpbuf;
	tmpbuf = NULL;
	return 0;
}

int CFileOperation::GetRetLenth(int ilenin)
{
	int iflag = ilenin / 16;
	int ipre = 0;

	if (ilenin % 16 != 0)
	{
		ipre = 1;
	}

	return ((iflag + ipre) * 16);
}