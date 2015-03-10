
// Desk Tools AssembleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DeskToolsAssemble.h"
#include "DeskToolsAssembleDlg.h"
#include "ConfigDlg.h"

#define  COMMONBTNID 11110

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDeskToolsAssembleDlg dialog




CDeskToolsAssembleDlg::CDeskToolsAssembleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeskToolsAssembleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDICN_LOGO);
	m_strcfgfilename.Format(_T(".\\Conf\\DTA.cfg"));
}

void CDeskToolsAssembleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDeskToolsAssembleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CDeskToolsAssembleDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDeskToolsAssembleDlg::OnBnClickedOk)
	ON_COMMAND(ID_OPTION_TOOLSCONFIG, &CDeskToolsAssembleDlg::OnOptionToolsconfig)
END_MESSAGE_MAP()


// CDeskToolsAssembleDlg message handlers

BOOL CDeskToolsAssembleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	CHAR curdir[200];
	memset(curdir, 0, 200);
	GetCurrentDirectory(200, curdir);
	m_rootdir = curdir;

	AddDir();
	// TODO: Add extra initialization here
	int ret = InitWindowItems();
	if (0 != ret)
	{
		AfxMessageBox(_T("No tools load, Please config tools first!"));
		CConfigDlg tmpdlg;
		tmpdlg.DoModal();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDeskToolsAssembleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDeskToolsAssembleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDeskToolsAssembleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDeskToolsAssembleDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDeskToolsAssembleDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
}

int CDeskToolsAssembleDlg::InitWindowItems(void)
{
	CFileOperation *tmpfileopr = new CFileOperation;
	int ifnum = tmpfileopr->LoadFileByName();

	//load 完以后再map里面
	//读到数据喽~
	tmpmp = tmpfileopr->tmpmp;
	map <int, filest*>::iterator  iter;

	CString strtmpcmpgrpname(_T(""));
	for (iter = tmpmp.begin(); iter != tmpmp.end(); iter++)
	{
		//搞定按钮
		DWORD did = 11110 + iter->first;
		CButton *tmpbtn = new CButton;
		tmpbtn->Create(iter->second->strfilename, WS_VISIBLE | WS_CHILD, CRect(0 ,0, btn_width, btn_height), this, did);
		m_btnmap.push_back(tmpbtn);

	}

	InitButtonMap(ifnum);
	return 0;
}

void CDeskToolsAssembleDlg::OnOptionToolsconfig()
{
	// TODO: Add your command handler code here
	CConfigDlg tmpdlg;
	tmpdlg.DoModal();
	ReleaseBtn();
	InitWindowItems();
}


int CDeskToolsAssembleDlg::InitButtonMap(int ifilenum)
{
	//根据 map 建立按钮矩阵  
	ParseGroup();
	CRect clientrct;
	GetClientRect(clientrct);
	CRect grprct;
	grprct.left = clientrct.left + 5;
	grprct.right = clientrct.right - 5;
	grprct.top = clientrct.top + 5;
	grprct.bottom = clientrct.bottom - 5;

	int iwidth = grprct.Width() - 10;
	//int iwdnum = iwidth / btn_width;
	int iwdnum = 2;
	int ihtnum = ifilenum / iwdnum;

	CRect windowrect;
	windowrect.left = 0;
	windowrect.top = 0;
	windowrect.right = iwdnum * (btn_width + 5) + 10;
	windowrect.bottom = ihtnum * (btn_height + 5) + 10 + 85;

	MoveWindow(windowrect);
	CenterWindow();

	int ictn = 0;

	list <CButton*>::iterator iter;
	for (iter = m_btnmap.begin(); iter != m_btnmap.end(); iter++)
	{
		CRect tmprct;
		tmprct.left = (ictn % iwdnum) * (btn_width + 5) + 5;
		tmprct.top = (ictn / iwdnum) * (btn_height + 5) + 8;

		tmprct.right = tmprct.left + btn_width;
		tmprct.bottom = tmprct.top + btn_height;

		CButton *tmpbtn = *iter;
		tmpbtn->MoveWindow(tmprct);
		tmpbtn->ShowWindow(SW_SHOW);
		ictn++;
	}
	return 0;
}

int CDeskToolsAssembleDlg::ParseGroup(void)
{
	return 0;
}

BOOL CDeskToolsAssembleDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	DealWithparam(wParam, lParam);

	return CDialog::OnCommand(wParam, lParam);
}

CString CDeskToolsAssembleDlg::GetFilePath(CString strFileName)
{		
	map <int, filest*>::iterator  iter;
	for (iter = tmpmp.begin(); iter != tmpmp.end(); iter++)
	{		
		if (!strFileName.Compare(iter->second->strfilename))
		{
			return iter->second->strfilepath;
		}
		else
		{
			continue;
		}
	}
	return CString();
}

int CDeskToolsAssembleDlg::ReleaseBtn(void)
{
	list <CButton*>::iterator iter;
	if (!m_btnmap.empty())
	{
		for (iter = m_btnmap.begin(); iter != m_btnmap.end(); iter++)
		{
			CButton *tmpbtn = *iter;
			delete tmpbtn;
		}
	}
	m_btnmap.clear();

	return 0;
}

int CDeskToolsAssembleDlg::DealWithparam(WPARAM wParam, LPARAM lParam)
{
	map <int, filest*>::iterator iter;
	for (iter = tmpmp.begin(); iter != tmpmp.end(); iter++)
	{
		//搞定按钮
		DWORD did = 11110 + iter->first;
		if (wParam == did)
		{
			//找到控件
			CString tmpfname(_T(""));
			GetDlgItemText(did, tmpfname);
			CString tmpfpath = GetFilePath(tmpfname);

			if (tmpfpath[0] == '\\')
			{
				tmpfpath = m_rootdir + tmpfpath;
			}
			
			WinExec(tmpfpath, SW_SHOW);
			int ret = GetLastError();
			return 0;
		}
	}
	return 0;
}

int CDeskToolsAssembleDlg::AddDir(void)
{
	//创建文件夹
	CString tmpfpath(_T(""));
	tmpfpath = (m_rootdir + _T("\\Conf"));
	int ret = CreateDirectory(tmpfpath, NULL);

	CString tmpfilename(_T(""));
	tmpfilename = (tmpfpath + _T("\\DTA.cfg"));
	CFile tmpf;
	tmpf.Open(tmpfilename, CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	tmpf.Close();
	tmpf.~CFile();
	return 0;
}
