
// Desk Tools AssembleDlg.h : header file
//

#pragma once

#include "FileOperation.h"
#include "afxwin.h"
#include <map>
#include <list>
using namespace std;

const int btn_width = 120;
const int btn_height = 30;
struct stfiles 
{
	CString st_filename;
	CString st_filepath;
};

// CDeskToolsAssembleDlg dialog
class CDeskToolsAssembleDlg : public CDialog
{
// Construction
public:
	CDeskToolsAssembleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DESKTOOLSASSEMBLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	int InitWindowItems();
	afx_msg void OnOptionToolsconfig();

public://File opreation
	CString m_strcfgfilename;
	map <int, filest*> tmpmp;
	int InitButtonMap(int ifilenum);
	int ParseGroup(void);

	map <CString, list<stfiles*>> m_tmpgrps;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

public:
	list <CButton*> m_btnmap;
	CString GetFilePath(CString strFileName);
	int ReleaseBtn(void);
	int DealWithparam(WPARAM wParam, LPARAM lParam);
	CString m_rootdir;

	int AddDir(void);
};
