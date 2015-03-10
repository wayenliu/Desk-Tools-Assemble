#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "GridCtrl.h"
#include "CommonDef.h"
#include <map>
using namespace std;

// CConfigDlg dialog

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigDlg();

// Dialog Data
	enum { IDD = IDD_CONFIG_DIALOG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	int ReadConfigData(void);
	int FirstEnv(void);

	int m_lstcolwidth[3];
	int m_lstrowheight;

	CGridCtrl m_filedatagrd;
	int InitGridCtrl(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int AddFilesInList(void);
	int DeleteFileInList(void);
	int SaveConfigData(void);

public:
	char *tmpbody;
	char *Aescode;
	char g_aeskey[32];

	map <int, filest*> m_tmpgrp;
	int GetRetLenth(int ilenin);
};
