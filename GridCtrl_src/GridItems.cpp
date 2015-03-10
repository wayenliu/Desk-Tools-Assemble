#include "stdafx.h"
#include "GridItems.h"
#include "GridItemsProvider.h"

GridItems::GridItems()
{
	m_griditemprovider = NULL;
}

GridItems::GridItems(CGridCtrl *myparent, int raw, int col, CString data)
{
	m_gridcontrl = myparent;
	m_raw = raw;
	m_col = col;
	m_data = data;
	m_griditemprovider = NULL;
}

void GridItems::SetIndex(int index)
{
	m_index = index;
}

GridItems::~GridItems(void)
{
}

CGridCtrl* GridItems::GetmyParentCtrl()
{
	return m_gridcontrl;
}

GridItemsProvider* GridItems::GetmyProvider()
{
	if (m_griditemprovider == NULL)
	{
		m_griditemprovider = new (std::nothrow) GridItemsProvider(this);  
	}
	return m_griditemprovider;
}