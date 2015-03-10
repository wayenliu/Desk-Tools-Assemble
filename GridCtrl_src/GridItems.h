#pragma once

////#include <ole2.h>
//#include <assert.h>
//#include <UIAutomation.h>
////#include <UIAutomationCore.h>
//////#include <UIAutomationClient.h>
////#include <UIAutomationCoreApi.h>
//
//using namespace std;
//#pragma comment(lib, "uiautomationcore.lib")

//#import "UIAutomationCore.idl"


class CGridCtrl;
class GridItemsProvider;

class GridItems
{
public:
	GridItems();
	GridItems(CGridCtrl *myparent, int raw, int col, CString data);
	void SetIndex(int index);
	~GridItems(void);
public:
	int m_raw;
	int m_col;
	int m_index;
	CString m_data;
	GridItemsProvider *m_griditemprovider;
	CGridCtrl *m_gridcontrl;
public:
	GridItemsProvider * GetmyProvider();
	CGridCtrl * GetmyParentCtrl();
};
