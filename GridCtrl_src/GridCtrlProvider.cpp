#include "stdafx.h"
#include "GridItemsProvider.h"
#include "GridItems.h"
#include "GridCtrlProvider.h"
#include "GridCtrl.h"

CGridCtrlProvider::CGridCtrlProvider(CGridCtrl *pControl) : m_refCount(1), m_pControl(pControl)
{
	m_controlHwnd = pControl->m_hWnd;
	m_pControl = pControl;
}

CGridCtrlProvider::~CGridCtrlProvider(void)
{
}


// Retrieves the UI Automation provider for a list item.
//
GridItemsProvider* CGridCtrlProvider::GetItemProviderByIndex(int index)
{
	if ((index < 0) || (index > (int)(m_pControl->m_mygrid.size())))
	{
		return NULL;
	}
	int i = 0;
	for (list < GridItems *> ::iterator it = m_pControl->m_mygrid.begin(); it != m_pControl->m_mygrid.end(); ++ it)
	{
		if (index == i)
		{
			GridItems *pItem = *it;
			return pItem->GetmyProvider();
		}
		i++;
	}

	return NULL;
}

// Raises an event when a list item is selected.
//

// IUnknown implementation.
//
IFACEMETHODIMP_(ULONG) CGridCtrlProvider::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

IFACEMETHODIMP_(ULONG) CGridCtrlProvider::Release()
{
	long val = InterlockedDecrement(&m_refCount);
	if (val == 0)
	{
		delete this;
	}
	return val;
}

IFACEMETHODIMP CGridCtrlProvider::QueryInterface(REFIID riid, void** ppInterface)
{
	if(riid == __uuidof(IUnknown))                              *ppInterface =static_cast<IRawElementProviderSimple*>(this);
	else if(riid == __uuidof(IRawElementProviderSimple))        *ppInterface =static_cast<IRawElementProviderSimple*>(this);
	else if(riid == __uuidof(IRawElementProviderFragment))      *ppInterface =static_cast<IRawElementProviderFragment*>(this);
	else if(riid == __uuidof(IRawElementProviderFragmentRoot))  *ppInterface =static_cast<IRawElementProviderFragmentRoot*>(this);
	//else if(riid == __uuidof(ISelectionProvider))               *ppInterface =static_cast<ISelectionProvider*>(this);
	else if(riid == __uuidof(IGridProvider))               *ppInterface =static_cast<IGridProvider*>(this);
	//else if(riid == __uuidof(ITableProvider))               *ppInterface =static_cast<ITableProvider*>(this);
	/*
	public ITableProvider,
	public ITableItemProvider,
	//public IGridItemProvider,
	public IGridProvider
	*/

	else
	{
		*ppInterface = NULL;
		return E_NOINTERFACE;
	}
	(static_cast<IUnknown*>(*ppInterface))->AddRef();
	return S_OK;
}


// IRawElementProviderSimple implementation
//
// Implementation of IRawElementProviderSimple::get_ProviderOptions.
// Gets UI Automation provider options.
//
IFACEMETHODIMP CGridCtrlProvider::get_ProviderOptions(ProviderOptions* pRetVal)
{
	*pRetVal = ProviderOptions_ServerSideProvider;
	return S_OK;
}

// Implementation of IRawElementProviderSimple::get_PatternProvider.
// Gets the object that supports ISelectionPattern.
//
IFACEMETHODIMP CGridCtrlProvider::GetPatternProvider(PATTERNID patternId, IUnknown** pRetVal)
{
	*pRetVal = NULL;
	if (patternId == UIA_GridPatternId)
	{
		*pRetVal =static_cast<IRawElementProviderSimple*>(this);
		AddRef();
	}
	//if (patternId == UIA_TablePatternId)
	//{
	//	*pRetVal =static_cast<IRawElementProviderSimple*>(this);
	//	AddRef();
	//}
	else
	{
		*pRetVal = NULL;   
	}
	return S_OK;
}

// Implementation of IRawElementProviderSimple::get_PropertyValue.
// Gets custom properties.
//
IFACEMETHODIMP CGridCtrlProvider::GetPropertyValue(PROPERTYID propertyId, VARIANT* pRetVal)
{
	// Although it is hard-coded for the purposes of this sample, localizable 
	// text should be stored in, and loaded from, the resource file (.rc). 
	if (propertyId == UIA_LocalizedControlTypePropertyId)
	{
		pRetVal->vt = VT_BSTR;
		pRetVal->bstrVal = SysAllocString(L"BOOWAY_GRID_CTRL_025");
	}
	else if (propertyId == UIA_ControlTypePropertyId)
	{
		pRetVal->vt = VT_I4;
		pRetVal->lVal = UIA_DataGridControlTypeId; 
	}
	else if (propertyId == UIA_IsKeyboardFocusablePropertyId) 
	{
		pRetVal->vt = VT_BOOL;
		pRetVal->boolVal = VARIANT_TRUE;
	}
	else if (propertyId == UIA_NamePropertyId)
	{
		pRetVal->vt = VT_BSTR;
		pRetVal->bstrVal = SysAllocString(L"BOOWAY_GRID_CTRL");
	}
	//else pRetVal is empty, and UI Automation will attempt to get the property from
	// the HostRawElementProvider, which is the default provider for the HWND.
	//Note that the Name property comes from the Caption property of the control window, 
	//  if it has one.
	else if (propertyId == UIA_GridRowCountPropertyId)
	{
		pRetVal->vt = VT_BSTR;
		CString strraw("");
		strraw.Format(_T("%d"), (m_pControl->GetRowCount()));
		WCHAR myid[256];
		wcscpy(myid,  CT2CW(strraw));
		pRetVal->bstrVal = SysAllocString(myid);
	}
	else if (propertyId == UIA_GridColumnCountPropertyId)
	{
		pRetVal->vt = VT_BSTR;
		CString strcol("");
		strcol.Format(_T("%d"), (m_pControl->GetColumnCount()));
		WCHAR myid[256];
		wcscpy(myid,  CT2CW(strcol));
		pRetVal->bstrVal = SysAllocString(myid);
	}

	else if (propertyId == UIA_IsGridItemPatternAvailablePropertyId)
	{
		pRetVal->vt = VT_BOOL;
		pRetVal->boolVal = VARIANT_TRUE;
	}
	else if (propertyId == UIA_IsGridPatternAvailablePropertyId)
	{
		pRetVal->vt = VT_BOOL;
		pRetVal->boolVal = VARIANT_TRUE;
	}
	else if (propertyId == UIA_IsInvokePatternAvailablePropertyId)
	{
		pRetVal->vt = VT_BOOL;
		pRetVal->boolVal = VARIANT_TRUE;
	}

	else
	{
		pRetVal->vt = VT_EMPTY;
	}
	return S_OK;
}

// Implementation of IRawElementProviderSimple::get_HostRawElementProvider.
// Gets the default UI Automation provider for the host window. This provider 
// supplies many properties.
//
IFACEMETHODIMP CGridCtrlProvider::get_HostRawElementProvider(IRawElementProviderSimple** pRetVal)
{
	if (m_controlHwnd == NULL)
	{
		return UIA_E_ELEMENTNOTAVAILABLE;
	}
	HRESULT hr = UiaHostProviderFromHwnd(m_controlHwnd, pRetVal); 
	return hr;
}


// IRawElementProviderFragment implementation
//
// Implementation of IRawElementProviderFragment::Navigate.
// Enables UI Automation to locate the element in the tree.
// Navigation to the parent is handled by the host window provider.
//
IFACEMETHODIMP CGridCtrlProvider::Navigate(NavigateDirection direction, IRawElementProviderFragment** pRetVal)
{
	CGridCtrl * pGridCtrl = this->m_pControl;
	GridItems * pDest = NULL;
	IRawElementProviderFragment* pFrag = NULL;

	switch(direction)
	{
	case NavigateDirection_FirstChild:
		{
			if (0 == (int)(this->m_pControl->m_mygrid.size()))
			{
				pFrag = NULL;
				break;
			}
			list < GridItems *> ::iterator it = this->m_pControl->m_mygrid.begin();
			pDest = *it;
			pFrag = pDest->GetmyProvider();
			break;
		}
	case NavigateDirection_LastChild:
		{
			if (0 == (int)(this->m_pControl->m_mygrid.size()))
			{
				pFrag = NULL;
				break;
			}
			list < GridItems *> ::iterator it = this->m_pControl->m_mygrid.end();
			pDest = *it;
			pFrag = pDest->GetmyProvider();
			break;
		}
	}
	if (pFrag != NULL) 
	{
		pFrag->AddRef();
	}
	*pRetVal = pFrag;

	return S_OK;
}

// Implementation of IRawElementProviderFragment::GetRuntimeId.
// UI Automation gets this value from the host window provider, so supply NULL here.
//
IFACEMETHODIMP CGridCtrlProvider::GetRuntimeId(SAFEARRAY** pRetVal)
{
	*pRetVal = NULL;
	return S_OK;
}

// Implementation of IRawElementProviderFragment::get_BoundingRectangle.
//
// Retrieves the screen location and size of the control. Controls hosted in
// Win32 windows can return an empty rectangle; UI Automation will
// retrieve the rectangle from the HWND provider. However, the method is
// implemented here so that it can be used by the list items to calculate
// their own bounding rectangles.
//
// UI Spy uses the bounding rectangle to draw a red border around the element.
//
IFACEMETHODIMP CGridCtrlProvider::get_BoundingRectangle(UiaRect* pRetVal)
{
	RECT rect;
	GetClientRect(m_controlHwnd, &rect);
	InflateRect(&rect, -2, -2);
	POINT upperLeft;
	upperLeft.x = rect.left;  
	upperLeft.y = rect.top;
	ClientToScreen(m_controlHwnd, &upperLeft);

	pRetVal->left = upperLeft.x;
	pRetVal->top = upperLeft.y;
	pRetVal->width = rect.right - rect.left;
	pRetVal->height = rect.bottom - rect.top;
	return S_OK;
}

// Implementation of IRawElementProviderFragment::GetEmbeddedFragmentRoots.
// Retrieves other fragment roots that may be hosted in this one.
//
IFACEMETHODIMP CGridCtrlProvider::GetEmbeddedFragmentRoots(SAFEARRAY** pRetVal)
{
	*pRetVal = NULL;
	return S_OK;
}

// Implementation of IRawElementProviderFragment::SetFocus.
// Responds to the control receiving focus through a UI Automation request.
// For HWND-based controls, this is handled by the host window provider.
//
IFACEMETHODIMP CGridCtrlProvider::SetFocus()
{
	return S_OK;
}

// Implementation of IRawElementProviderFragment::get_FragmentRoot.
// Retrieves the root element of this fragment.
//
IFACEMETHODIMP CGridCtrlProvider::get_FragmentRoot(IRawElementProviderFragmentRoot** pRetVal)
{
	*pRetVal = static_cast<IRawElementProviderFragmentRoot*>(this);
	AddRef();  
	return S_OK;
}

// IRawElementProviderFragmentRoot implementation
//
// Implementation of IRawElementProviderFragmentRoot::ElementProviderFromPoint.
// Retrieves the IRawElementProviderFragment interface for the item at the specified 
// point (in client coordinates).
// UI Spy uses this to determine what element is under the cursor when Ctrl is pressed.
//
IFACEMETHODIMP CGridCtrlProvider::ElementProviderFromPoint(double x, double y, IRawElementProviderFragment** pRetVal)
{
	//CPoint mypt;
	//mypt.x = x;
	//mypt.y = y;
	//CCellID mycellid =  m_pControl->GetCellFromPt(mypt);
	//CGridCellProvider * pItem = GetItemProviderByIndex(mycellid.row, mycellid.col);
	//if (pItem != NULL)
	//{
	//	*pRetVal = static_cast<IRawElementProviderFragment*>(pItem);
	//	pItem->AddRef();
	//}
	//else 
	//{
	//	*pRetVal = NULL;
	//}

	*pRetVal = NULL;
	return S_OK;
}

// Implementation of IRawElementProviderFragmentRoot::GetFocus.
// Retrieves the provider for the list item that is selected when the control gets focus.
//
IFACEMETHODIMP CGridCtrlProvider::GetFocus(IRawElementProviderFragment** pRetVal)
{
	//*pRetVal = NULL;
	//ListItemProvider* pItem = GetItemProviderByIndex(m_pControl->GetSelectedIndex()); 
	//if (pItem != NULL)
	//{
	//	pItem->AddRef();
	//	*pRetVal = pItem;
	//}
	return S_OK;
}

//// ISelectionProvider implementation
////
//// Implementation of ISelectionProvider::GetSelection.
//// Gets the provider(s) for the items(s) selected in the list box. 
//// In this case, only a single item can be selected.
////
//IFACEMETHODIMP CGridCtrlProvider::GetSelection(SAFEARRAY** pRetVal)
//{
//	//SAFEARRAY *psa = SafeArrayCreateVector(VT_UNKNOWN, 0, 1);
//	//int index = m_pControl->GetSelectedIndex(); 
//	//ListItemProvider* pItem = GetItemProviderByIndex(index); 
//	//if (pItem != NULL)
//	//{
//	//	LONG i = 0;
//	//	SafeArrayPutElement(psa, &i, pItem);
//	//}
//	//*pRetVal = psa;
//	return S_OK;
//}
//
//// Implementation of ISelectionProvider::get_CanSelectMultiple.
////
//IFACEMETHODIMP CGridCtrlProvider::get_CanSelectMultiple(BOOL *pRetVal)
//{
//	*pRetVal = FALSE;
//	return S_OK;
//}
//// Implementation of ISelectionProvider::get_IsSelectionRequired.
////
//IFACEMETHODIMP CGridCtrlProvider::get_IsSelectionRequired(BOOL *pRetVal)
//{
//	*pRetVal = TRUE;
//	return S_OK;
//}
//
//IFACEMETHODIMP CGridCtrlProvider::GetRowHeaders(SAFEARRAY * *pRetVal)
//{
//	*pRetVal = NULL;
//	return S_OK;
//}
//
//IFACEMETHODIMP CGridCtrlProvider::GetColumnHeaders(SAFEARRAY * *pRetVal)
//{
//	*pRetVal = NULL;
//	return S_OK;
//}
//
//IFACEMETHODIMP CGridCtrlProvider::get_RowOrColumnMajor(enum RowOrColumnMajor *pRetVal)
//{
//	return S_OK;
//};
//
//IFACEMETHODIMP CGridCtrlProvider::GetRowHeaderItems(SAFEARRAY * *pRetVal)
//{
//	return S_OK;
//}
//
//IFACEMETHODIMP CGridCtrlProvider::GetColumnHeaderItems(SAFEARRAY * *pRetVal)
//{
//	return S_OK;
//}

IFACEMETHODIMP CGridCtrlProvider::GetItem(int row, int column, IRawElementProviderSimple **pRetVal)
{
	CGridCellBase *mycellbase = m_pControl->GetCell(row, column);
	GridItems *mygrid = new GridItems(m_pControl, row, column, mycellbase->GetText());
	*pRetVal = (IRawElementProviderSimple *)mygrid->GetmyProvider();
	return S_OK;
}

IFACEMETHODIMP CGridCtrlProvider::get_RowCount(int *pRetVal)
{
	*pRetVal = m_pControl->GetRowCount();
	return S_OK;
}

IFACEMETHODIMP CGridCtrlProvider::get_ColumnCount(int *pRetVal)
{
	*pRetVal = m_pControl->GetColumnCount();
	return S_OK;
}

