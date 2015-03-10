#include "stdafx.h"
#include "GridItemsProvider.h"
#include "GridItems.h"
#include "GridCtrl.h"
#include "GridCtrlProvider.h"

GridItemsProvider::GridItemsProvider(GridItems* pControl) : m_refCount(1)
{
	m_griditem = pControl;
	m_parentgrid = pControl->GetmyParentCtrl();
}

GridItemsProvider::~GridItemsProvider(void)
{
}


 //IUnknown implementation.

IFACEMETHODIMP_(ULONG) GridItemsProvider::AddRef()
{
	return S_OK;
    //return InterlockedIncrement(&m_refCount);
}

IFACEMETHODIMP_(ULONG) GridItemsProvider::Release()
{
    //long val = InterlockedDecrement(&m_refCount);
    //if (val == 0)
    //{
    //    delete this;
    //}
    //return val;
	return S_OK;
}

IFACEMETHODIMP GridItemsProvider::QueryInterface(REFIID riid, void** ppInterface)
{
    if(riid == __uuidof(IUnknown))                              *ppInterface =static_cast<IRawElementProviderSimple*>(this);
    else if(riid == __uuidof(IRawElementProviderSimple))        *ppInterface =static_cast<IRawElementProviderSimple*>(this);
    else if(riid == __uuidof(IRawElementProviderFragment))      *ppInterface =static_cast<IRawElementProviderFragment*>(this);
    //else if(riid == __uuidof(ISelectionItemProvider))           *ppInterface =static_cast<ISelectionItemProvider*>(this);
	else if(riid == __uuidof(IGridItemProvider))           *ppInterface =static_cast<IGridItemProvider*>(this);
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
// Implementation of IRawElementProviderSimple::GetProviderOptions.
////
IFACEMETHODIMP GridItemsProvider::get_ProviderOptions(ProviderOptions* pRetVal)
{
    *pRetVal = ProviderOptions_ServerSideProvider;
    return S_OK;
}
//
//// Implementation of IRawElementProviderSimple::GetPatternProvider.
//// Gets the object that supports the specified pattern.
////
IFACEMETHODIMP GridItemsProvider::GetPatternProvider(PATTERNID patternId, IUnknown** pRetVal)
{
	*pRetVal = NULL; 
    if (patternId == UIA_GridItemPatternId)
    {
        *pRetVal =static_cast<IRawElementProviderSimple*>(this);
        AddRef();
    }
    else
    {
        *pRetVal = NULL;   
    }
    return S_OK;
}
// Implementation of IRawElementProviderSimple::GetPropertyValue.
// Gets custom properties. Because list items are not directly hosted in an HWND, 
// more properties should be supported here than for the list box itself. 
//
IFACEMETHODIMP GridItemsProvider::GetPropertyValue(PROPERTYID propertyId, VARIANT* pRetVal)
{
	if (propertyId == UIA_LocalizedControlTypePropertyId)
	{
		pRetVal->vt = VT_BSTR;
		pRetVal->bstrVal = SysAllocString(L"My items");
	}
    if (propertyId == UIA_AutomationIdPropertyId)
    {
        pRetVal->vt = VT_BSTR;
		CString strid("");
		strid.Format(_T("%d"), ( (m_griditem->m_raw) * (m_parentgrid->GetColumnCount()) + m_griditem->m_col ));
		WCHAR myid[256];
		wcscpy(myid,  CT2CW(strid));
		pRetVal->bstrVal = SysAllocString(myid);
    }
    else if (propertyId == UIA_NamePropertyId)
    {
        pRetVal->vt = VT_BSTR;
		WCHAR myname[256];
		wcscpy(myname,  CT2CW(m_griditem->m_data));
        pRetVal->bstrVal = SysAllocString(myname);
    }
    else if (propertyId == UIA_ControlTypePropertyId)
    {
        pRetVal->vt = VT_I4;
        pRetVal->lVal = UIA_DataItemControlTypeId;
    }
    // HasKeyboardFocus is true if the list has focus, and this item is selected.
    else if(propertyId == UIA_HasKeyboardFocusPropertyId)
    {
        pRetVal->vt = VT_BOOL;
        pRetVal->boolVal = VARIANT_TRUE;
    }
	else if(propertyId == UIA_IsEnabledPropertyId)
	{
		pRetVal->vt = VT_BOOL;
		pRetVal->boolVal = VARIANT_TRUE;
	}
	
    else if (propertyId == UIA_IsControlElementPropertyId)
    {
        pRetVal->vt = VT_BOOL;
        pRetVal->boolVal = VARIANT_TRUE;
    }
    else if (propertyId == UIA_IsContentElementPropertyId)
    {
        pRetVal->vt = VT_BOOL;
        pRetVal->boolVal = VARIANT_TRUE;
    }
    else if (propertyId == UIA_IsKeyboardFocusablePropertyId)
    {
        pRetVal->vt = VT_BOOL;
        pRetVal->boolVal = VARIANT_TRUE;
    }
    //else if (propertyId == UIA_ItemStatusPropertyId)
    //{
    //    pRetVal->vt = VT_BSTR;
    //    if (m_pListItemControl->GetStatus() == Status_Online)
    //    {
    //        pRetVal->bstrVal = SysAllocString(L"Online");
    //    }
    //    else
    //    {
    //        pRetVal->bstrVal = SysAllocString(L"Offline");
    //    }
    //}

	else if (propertyId == UIA_GridItemRowPropertyId)
	{
		pRetVal->vt = VT_BSTR;
		CString strraw("");
		strraw.Format(_T("%d"), (m_griditem->m_raw));
		WCHAR myid[256];
		wcscpy(myid,  CT2CW(strraw));
		pRetVal->bstrVal = SysAllocString(myid);
	}
	else if (propertyId == UIA_GridItemColumnPropertyId)
	{
		pRetVal->vt = VT_BSTR;
		CString strcol("");
		strcol.Format(_T("%d"), (m_griditem->m_col));
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
	//else if (propertyId == UIA_IsInvokePatternAvailablePropertyId)
	//{
	//	pRetVal->vt = VT_BOOL;
	//	pRetVal->boolVal = VARIANT_TRUE;
	//}
	else if (propertyId == UIA_ItemStatusPropertyId)
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
// Gets the UI Automation provider for the host window. 
// Return NULL. because the list items are not directly hosted in a window.
//
IFACEMETHODIMP GridItemsProvider::get_HostRawElementProvider(IRawElementProviderSimple** pRetVal)
{
    *pRetVal = NULL; 
    return S_OK; 
}

// IRawElementProviderFragment implementation.
//
// Implementation of IRawElementProviderFragment::Navigate.
// Enables UI Automation to locate the element in the tree.
//
IFACEMETHODIMP GridItemsProvider::Navigate(NavigateDirection direction, IRawElementProviderFragment ** pRetVal)
{
    IRawElementProviderFragment* pFrag = NULL;
	switch(direction)
	{
	case NavigateDirection_Parent:
		{
			pFrag = (IRawElementProviderFragment*)m_parentgrid->GetGridProvider(); 
			break;
		}
	case NavigateDirection_PreviousSibling:
		{
			if ((m_griditem->m_raw == 0) && (m_griditem->m_col == 0))
			{
				pFrag = NULL;
				break;
			}
			for (list < GridItems *> ::iterator it = m_parentgrid->m_mygrid.begin(); it != m_parentgrid->m_mygrid.end(); ++ it)
			{
				if (m_griditem == *it)
				{
					GridItems *pNext = *(--it);
					pFrag = pNext->GetmyProvider();
					break;
				}
				pFrag = NULL;
			}
            break;
        }

    case NavigateDirection_NextSibling:  
        {
			for (list < GridItems *> ::iterator it = m_parentgrid->m_mygrid.begin(); it != m_parentgrid->m_mygrid.end(); ++ it)
			{
				if (*it == m_parentgrid->m_mygrid.back())
				{
					pFrag = NULL;
					break;
				}
				if (m_griditem == *it)
				{
					GridItems *pNext = *(++it);
					pFrag = pNext->GetmyProvider();
					break;
				}
				pFrag = NULL;
			}
            break;
        }
    }
    *pRetVal = pFrag;
    if (pFrag != NULL) 
    {   
        pFrag->AddRef();
    }
    return S_OK;
}

// Implementation of IRawElementProviderFragment::GetRuntimeId.
// Gets the runtime identifier. This is an array consisting of UiaAppendRuntimeId, 
// which makes the ID unique among instances of the control, and the Automation Id.
//
IFACEMETHODIMP GridItemsProvider::GetRuntimeId(SAFEARRAY ** pRetVal)
{
	*pRetVal = NULL;
    return S_OK;
}

// Implementation of IRawElementProviderFragment::get_BoundingRectangle.
// Gets the bounding rectangle of the item, in screen coordinates.
//
IFACEMETHODIMP GridItemsProvider::get_BoundingRectangle(UiaRect * pRetVal)
{
	CRect myrect;
	m_parentgrid->GetCellRect(m_griditem->m_raw, m_griditem->m_col, myrect);

	RECT rect;
	GetClientRect(m_parentgrid->m_hWnd, &rect);
	InflateRect(&rect, -2, -2);
	POINT upperLeft;
	upperLeft.x = rect.left;  
	upperLeft.y = rect.top;
	ClientToScreen(m_parentgrid->m_hWnd, &upperLeft);

	pRetVal->left = myrect.left + upperLeft.x - 2;
	pRetVal->top = myrect.top + upperLeft.y - 2;
	pRetVal->width = myrect.Width();
	pRetVal->height = myrect.Height();

	return S_OK;
}


// Implementation of IRawElementProviderFragment::GetEmbeddedFragmentRoots.
// Retrieves any fragment roots that may be hosted in this element.
//
IFACEMETHODIMP GridItemsProvider::GetEmbeddedFragmentRoots(SAFEARRAY ** pRetVal)
{
    *pRetVal = NULL;
    return S_OK;
}

// Implementation of IRawElementProviderFragment::SetFocus.
// Responds to the control receiving focus through a UI Automation request.
//
IFACEMETHODIMP GridItemsProvider::SetFocus()
{
    //Select();
    return S_OK;
}

// Implementation of IRawElementProviderFragment::get_FragmentRoot.
// Retrieves the root element of this fragment.
//
IFACEMETHODIMP GridItemsProvider::get_FragmentRoot(IRawElementProviderFragmentRoot** pRetVal)
{
    IRawElementProviderFragmentRoot* pRoot = (IRawElementProviderFragmentRoot*)this->m_parentgrid->GetGridProvider();
    if (pRoot == NULL)
    {
        return E_FAIL;
    }
    pRoot->AddRef();
    *pRetVal = pRoot;
    return S_OK;
}

//
//// ISelectionItemProvider implementation.
//
//// Implementation of ISelectionItemProvider::Select.
//// Responds to a request by UI Automation to select the item.
////
//IFACEMETHODIMP GridItemsProvider::Select()
//{
//	m_parentgrid->SetFocusCell(CCellID(m_griditem->m_raw, m_griditem->m_col));
//    return S_OK;
//}
//
//// Implementation of ISelectionItemProvider::AddToSelection.
//// Responds to a request by UI Automation to add the item to the selection.
//// Because this is a single-selection list box, the call is equivalent to Select().
////
//IFACEMETHODIMP GridItemsProvider::AddToSelection()
//{
//    Select();
//    return S_OK;
//}
//
//// Implementation of ISelectionItemProvider::RemoveFromSelection.
//// Responds to a request by UI Automation to remove the item from the selection.
//// One and only one item must always be selected, so this is not implemented.
////
//IFACEMETHODIMP GridItemsProvider::RemoveFromSelection()
//{
//    return UIA_E_INVALIDOPERATION;
//}
//
//// Implementation of ISelectionItemProvider::get_IsSelected.
//// Advises whether the item is selected.
////
//IFACEMETHODIMP GridItemsProvider::get_IsSelected(BOOL *pRetVal)
//{
//    *pRetVal = (m_parentgrid->IsCellSelected(CCellID(m_griditem->m_raw, m_griditem->m_col)));
//    return S_OK;
//}
//
//// Implementation of ISelectionItemProvider::get_SelectionContainer.
//// Returns the UI Automation provider for the list control.
////
//IFACEMETHODIMP GridItemsProvider::get_SelectionContainer(
//    IRawElementProviderSimple **pRetVal)
//{
//    IRawElementProviderSimple* pParent = (IRawElementProviderSimple*)(m_parentgrid->GetGridProvider());
//    pParent->AddRef();
//    *pRetVal = pParent;
//    return S_OK;
//}

// Raises an event when an item is added to the list.
//
void GridItemsProvider::NotifyItemAdded()
{
    if (UiaClientsAreListening())
    {
        UiaRaiseStructureChangedEvent(this, StructureChangeType_ChildAdded, NULL, 0);
    }
}

// Raises an event when an item is removed from the list.
//
// StructureType_ChildRemoved is unusual in that it is raised on the parent provider,
// since the child provider may not exist anymore, but it uses the child's runtime ID.
void GridItemsProvider::NotifyItemRemoved()
{
    if (UiaClientsAreListening())
    {
        CGridCtrlProvider* MyGridProvider = m_parentgrid->GetGridProvider();

        // Construct the partial runtime ID for the removed child
        int id = m_griditem->m_index;
        int rId[] = { UiaAppendRuntimeId, id };

        UiaRaiseStructureChangedEvent(MyGridProvider, StructureChangeType_ChildRemoved, rId, ARRAYSIZE(rId));
    }
}

// Raises an event when a list item is selected.
//
void GridItemsProvider::NotifyElementSelected()
{
    if (UiaClientsAreListening())
    {
        UiaRaiseAutomationEvent(this, UIA_SelectionItem_ElementSelectedEventId);
    }
}

void GridItemsProvider::NotifyTextChanged()
{
	if (UiaClientsAreListening())
	{
		UiaRaiseAutomationEvent(this, UIA_Text_TextChangedEventId);
	}
}

//
//
//IFACEMETHODIMP GridItemsProvider::GetRowHeaders(SAFEARRAY * *pRetVal)
//{
//	return S_OK;
//}
//
//IFACEMETHODIMP GridItemsProvider::GetColumnHeaders(SAFEARRAY * *pRetVal)
//{
//	return S_OK;
//}
//
//IFACEMETHODIMP GridItemsProvider::get_RowOrColumnMajor(enum RowOrColumnMajor *pRetVal)
//{
//	return S_OK;
//};
//
//IFACEMETHODIMP GridItemsProvider::GetRowHeaderItems(SAFEARRAY * *pRetVal)
//{
//	return S_OK;
//}
//
//IFACEMETHODIMP GridItemsProvider::GetColumnHeaderItems(SAFEARRAY * *pRetVal)
//{
//	return S_OK;
//}

IFACEMETHODIMP GridItemsProvider::get_Row(int *pRetVal)
{
	*pRetVal = m_griditem->m_raw;
	return S_OK;
}
IFACEMETHODIMP GridItemsProvider::get_Column(int *pRetVal)
{
	*pRetVal = m_griditem->m_col;
	return S_OK;
}

IFACEMETHODIMP GridItemsProvider::get_RowSpan(int *pRetVal)
{
	*pRetVal = NULL;
	return S_OK;
}

IFACEMETHODIMP GridItemsProvider::get_ColumnSpan(int *pRetVal)
{
	*pRetVal = NULL;
	return S_OK;
}

IFACEMETHODIMP GridItemsProvider::get_ContainingGrid(IRawElementProviderSimple **pRetVal)
{
	*pRetVal = NULL;
	return S_OK;
}