// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DeskToolsAssemble.h"
#include "ConfigDlg.h"
#include "AES.h"
#include "FileOperation.h"

#define  IDGRD_DATA 10020

// CConfigDlg dialog

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDICN_LOGO);
	m_lstcolwidth[0] = 0;
	m_lstcolwidth[1] = 0;
	m_lstcolwidth[2] = 0;
	tmpbody = new char[1];
	memset(tmpbody, 0, 2);

	char g_aeskey[32];
	memset(g_aeskey, 0, 32);
	memcpy(g_aeskey, _T("WayenTech-W"), 31);

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_GRID, m_filedatagrd);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConfigDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConfigDlg::OnBnClickedCancel)
	//ON_NOTIFY(NM_DBLCLK, IDLIST_FILES, &CConfigDlg::OnNMDblclkFiles)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CConfigDlg message handlers

void CConfigDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
}

void CConfigDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO:  Add extra initialization here

	InitGridCtrl();

	if (-1 == ReadConfigData())
	{//失败
		FirstEnv();
	}

	MoveWindow(CRect(0, 0, 1010, 500));
	CenterWindow(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//读取配置文件，失败的话直接初始化
//成功返回0； 失败返回-1
int CConfigDlg::ReadConfigData(void)
{
	CFileOperation *tmpfileopr = new CFileOperation;
	bool rdflag = tmpfileopr->LoadFileByName();
	
	if (!rdflag)
	{
		return -1;
	}

	//读到数据喽~
	map <int, filest*> tmpmp = tmpfileopr->tmpmp;
	map <int, filest*>::iterator  iter;

	for (iter = tmpmp.begin(); iter != tmpmp.end(); iter++)
	{
		int rownum = m_filedatagrd.InsertRow(iter->second->strgrpname);
		m_filedatagrd.SetItemText(rownum, 1, iter->second->strfilename);
		m_filedatagrd.SetItemText(rownum, 2, iter->second->strfilepath);
	}

	return 0;
}

int CConfigDlg::FirstEnv(void)
{
	return 0;
}

int CConfigDlg::InitGridCtrl(void)
{
	CRect cltrct;
	GetClientRect(cltrct);
	m_filedatagrd.Create(cltrct, this, IDGRD_DATA, WS_CHILD | WS_TABSTOP | WS_VISIBLE | SS_CENTER);
	m_filedatagrd.SetListMode(TRUE);
	m_filedatagrd.SetFixedColumnSelection(FALSE);

	m_filedatagrd.SetFixedBkColor(RGB(239,244,250));
	m_filedatagrd.SetBkColor(RGB(255,255,255));
	m_filedatagrd.SetEditable(TRUE);

	m_filedatagrd.SetFixedRowCount(1);
	m_filedatagrd.SetColumnCount(3);
	m_filedatagrd.SetItemText(0, 0, _T("Group Name"));
	m_filedatagrd.SetItemText(0, 1, _T("File Name"));
	m_filedatagrd.SetItemText(0, 2, _T("File Path"));
	m_filedatagrd.SetItemFormat(0, 0, DT_CENTER);
	m_filedatagrd.SetItemFormat(0, 1, DT_CENTER);
	m_filedatagrd.SetItemFormat(0, 2, DT_CENTER);

	m_filedatagrd.AutoSize();
	m_filedatagrd.SetColumnWidth(0, 160);
	m_filedatagrd.SetColumnWidth(1, 180);
	m_filedatagrd.SetColumnWidth(2, 300);

	CRect plcrct;
	plcrct.left = cltrct.left + 5;
	plcrct.right = cltrct.right - 3;
	plcrct.top = cltrct.top + 1;
	plcrct.bottom = cltrct.bottom - 3;

	m_filedatagrd.MoveWindow(plcrct);
	m_filedatagrd.ShowWindow(SW_SHOW);
	return 0;
}

void CConfigDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (IsWindow(m_filedatagrd.m_hWnd) && IsWindow(this->m_hWnd))
	{
		CRect cltrct;
		GetClientRect(cltrct);
		CRect plcrct;
		plcrct.left = cltrct.left + 5;
		plcrct.right = cltrct.right - 3;
		plcrct.top = cltrct.top + 1;
		plcrct.bottom = cltrct.bottom - 3;

		m_filedatagrd.MoveWindow(plcrct);
		m_filedatagrd.ShowWindow(SW_SHOW);
		if (cy > 300)
		{
			m_filedatagrd.SetColumnWidth(2, cy + 200);
		}		
	}
}

BOOL CConfigDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//判断是否为键盘消息
	if (pMsg->message == WM_KEYDOWN)
	{
		//判断是否按下键盘A键
		if((pMsg->wParam == 'A' || pMsg->wParam == VK_ADD) && (::GetKeyState(VK_CONTROL)<0))
		{
			//添加一行
			AddFilesInList();
			return TRUE;
		}
		else if((pMsg->wParam == 'D' || pMsg->wParam == VK_SUBTRACT) && (::GetKeyState(VK_CONTROL)<0))
		{
			//删除
			DeleteFileInList();
			return TRUE;
		}
		else if((pMsg->wParam == 'S') && (::GetKeyState(VK_CONTROL)<0))
		{
			//save
			SaveConfigData();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

int CConfigDlg::AddFilesInList(void)
{
	m_filedatagrd.InsertRow(_T(""));
	m_filedatagrd.Refresh();
	return 0;
}

int CConfigDlg::DeleteFileInList(void)
{
	int irow = m_filedatagrd.GetFocusCell().row;
	if (irow > 0)
	{
		m_filedatagrd.DeleteRow(irow);
		m_filedatagrd.Refresh();
	}
	return 0;
}

int CConfigDlg::SaveConfigData(void)
{
	int ilen = 0;
	int icount = m_filedatagrd.GetRowCount();
	m_tmpgrp.clear();
	int inum = 0;
	for (int i = 1; i < icount; i++)
	{
		CString strgroup = m_filedatagrd.GetItemText(i, 0);
		CString strfilename = m_filedatagrd.GetItemText(i, 1);
		CString strfilepath = m_filedatagrd.GetItemText(i, 2);
		strgroup.Trim();
		strfilename.Trim();
		strfilepath.Trim();

		//拼装body
		if (!strgroup.IsEmpty() && !strfilename.IsEmpty() && !strfilepath.IsEmpty())
		{
			filest *tmpf = new filest;
			tmpf->strgrpname = strgroup;
			tmpf->strfilename = strfilename;
			tmpf->strfilepath = strfilepath;
			m_tmpgrp[inum] = tmpf;
			inum++;

			int igrplen = strgroup.GetLength();
			int ifnamelen = strfilename.GetLength();
			int ifpathlen = strfilepath.GetLength();

			int igrpretlen = GetRetLenth(igrplen);
			int ifnameretlen = GetRetLenth(ifnamelen);
			int ifpathretlen = GetRetLenth(ifpathlen);

			ilen += igrpretlen + ifnameretlen + ifpathretlen + 3 + 12;
		}
	}

	//m_tmpgrp   inum   ilen
	//////////////////////////////////////////////////////////////////////////
	CFileOperation *tmpFileopr = new CFileOperation;
	tmpFileopr->InitFileHeader(m_tmpgrp, inum, ilen);

	return 0;
}

int CConfigDlg::GetRetLenth(int ilenin)
{
	int iflag = ilenin / 16;
	int ipre = 0;

	if (ilenin % 16 != 0)
	{
		ipre = 1;
	}

	return ((iflag + ipre) * 16);
}
