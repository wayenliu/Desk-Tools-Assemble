#include "stdafx.h"
#include "GridCellProvider.h"
#include "GridCell.h"
#include "GridCtrl.h"
#include "GridCtrlProvider.h"
////#include <ole2.h>
//#include <assert.h>
//#include <UIAutomation.h>
////#include <UIAutomationCore.h>
//////#include <UIAutomationClient.h>
////#include <UIAutomationCoreApi.h>
//using namespace std;
//#pragma comment(lib, "uiautomationcore.lib")

//#import "UIAutomationCore.idl"

CGridCellProvider::CGridCellProvider(CGridCell* pControl) : m_refCount(1)
{
	m_pGridCellContol = pControl;
	m_pGridCtl = pControl->GetParentGridCtl();
}

CGridCellProvider::~CGridCellProvider()
{
}

 //IUnknown implementation.

IFACEMETHODIMP_(ULONG) CGridCellProvider::AddRef()
{
	return S_OK;
    //return InterlockedIncrement(&m_refCount);
}

IFACEMETHODIMP_(ULONG) CGridCellProvider::Release()
{
    //long val = InterlockedDecrement(&m_refCount);
    //if (val == 0)
    //{
    //    delete this;
    //}
    //return val;
	return S_OK;
}

IFACEMETHODIMP CGridCellProvider::QueryInterface(REFIID riid, void** ppInterface)
{
    if(riid == __uuidof(IUnknown))                              *ppInterface =static_cast<IRawElementProviderSimple*>(this);
    else if(riid == __uuidof(IRawElementProviderSimple))        *ppInterface =static_cast<IRawElementProviderSimple*>(this);
    else if(riid == __uuidof(IRawElementProviderFragment))      *ppInterface =static_cast<IRawElementProviderFragment*>(this);
    else if(riid == __uuidof(ISelectionItemProvider))           *ppInterface =static_cast<ISelectionItemProvider*>(this);
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
IFACEMETHODIMP CGridCellProvider::get_ProviderOptions(ProviderOptions* pRetVal)
{
    *pRetVal = ProviderOptions_ServerSideProvider;
    return S_OK;
}
//
//// Implementation of IRawElementProviderSimple::GetPatternProvider.
//// Gets the object that supports the specified pattern.
////
IFACEMETHODIMP CGridCellProvider::GetPatternProvider(PATTERNID patternId, IUnknown** pRetVal)
{
    if (patternId == UIA_SelectionItemPatternId)
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
IFACEMETHODIMP CGridCellProvider::GetPropertyValue(PROPERTYID propertyId, VARIANT* pRetVal)
{
	if (propertyId == UIA_LocalizedControlTypePropertyId)
	{
		pRetVal->vt = VT_BSTR;
		pRetVal->bstrVal = SysAllocString(L"BOOWAY_GRID_ITEM_025");
	}
    if (propertyId == UIA_AutomationIdPropertyId)
    {
        pRetVal->vt = VT_BSTR;
        int Id = 123;
        // Convert int to BSTR.
        WCHAR idString[3];
        swprintf_s(idString, 3, L"%d", Id);
        pRetVal->bstrVal = SysAllocString(L"BOOWAY_GRID_ITEM_025_123");
    }
    else if (propertyId == UIA_NamePropertyId)
    {
        pRetVal->vt = VT_BSTR;
        pRetVal->bstrVal = SysAllocString(L"BOOWAY_GRID_ITEMS");
		//pRetVal->bstrVal = SysAllocString(L"fuck");
    }
    else if (propertyId == UIA_ControlTypePropertyId)
    {
        pRetVal->vt = VT_I4;
        pRetVal->lVal = UIA_DataItemControlTypeId;
    }
	else if (propertyId == UIA_IsControlElementPropertyId)
	{
		pRetVal->vt = VT_BOOL;
		pRetVal->boolVal = VARIANT_TRUE;
	}
    // HasKeyboardFocus is true if the list has focus, and this item is selected./*
	/*
    else if(propertyId == UIA_HasKeyboardFocusPropertyId)
    {
        int myIndex = m_pListItemControl->GetItemIndex();
        BOOL hasFocus = ((m_pListControl->GetSelectedIndex() == myIndex) 
            && (m_pListControl->GetIsFocused() == true));
        pRetVal->vt = VT_BOOL;
        pRetVal->boolVal = hasFocus ? VARIANT_TRUE : VARIANT_FALSE;
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
    else if (propertyId == UIA_ItemStatusPropertyId)
    {
        pRetVal->vt = VT_BSTR;
        if (m_pListItemControl->GetStatus() == Status_Online)
        {
            pRetVal->bstrVal = SysAllocString(L"Online");
        }
        else
        {
            pRetVal->bstrVal = SysAllocString(L"Offline");
        }
    }*/
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
IFACEMETHODIMP CGridCellProvider::get_HostRawElementProvider(IRawElementProviderSimple** pRetVal)
{
    *pRetVal = NULL; 
    return S_OK; 
}

// IRawElementProviderFragment implementation.
//
// Implementation of IRawElementProviderFragment::Navigate.
// Enables UI Automation to locate the element in the tree.
//
IFACEMETHODIMP CGridCellProvider::Navigate(NavigateDirection direction, IRawElementProviderFragment ** pRetVal)
{
    IRawElementProviderFragment* pFrag = NULL;
	//switch(direction)
	//{
	//case NavigateDirection_Parent:
	//	{
	//		pFrag = m_pGridCtl->GetGridProvider(); 
	//		break;
	//	}
	//case NavigateDirection_NextSibling:
	//	{
	//		//pFrag = m_pGridCellContol->GetCellProvider();
	//		break;
	//	}

 //   case NavigateDirection_PreviousSibling:  
 //       {
	//		//pFrag = m_pGridCellContol->GetCellProvider();
	//		break;
 //       }
 //   }
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
IFACEMETHODIMP CGridCellProvider::GetRuntimeId(SAFEARRAY ** pRetVal)
{
    //int id = m_pListItemControl->GetId();
    //int rId[] = { UiaAppendRuntimeId, id };

    //SAFEARRAY *psa = SafeArrayCreateVector(VT_I4, 0, 2);
    //for (LONG i = 0; i < 2; i++)
    //{
    //    SafeArrayPutElement(psa, &i, &(rId[i]));
    //}
    *pRetVal = NULL;
    return S_OK;
}

// Implementation of IRawElementProviderFragment::get_BoundingRectangle.
// Gets the bounding rectangle of the item, in screen coordinates.
//
IFACEMETHODIMP CGridCellProvider::get_BoundingRectangle(UiaRect * pRetVal)
{
  //  IRawElementProviderFragment* pParent = m_pListControl->GetListProvider();
  //  int myIndex = m_pListItemControl->GetItemIndex();
  //  UiaRect parentRect;

    //HRESULT hr = pParent->get_BoundingRectangle(&parentRect);
    //if (SUCCEEDED(hr))
    //{
    //    pRetVal->left = parentRect.left;
    //    pRetVal->top = parentRect.top + (m_pListControl->ItemHeight * myIndex);
    //    pRetVal->width = parentRect.width;
    //    pRetVal->height = m_pListControl->ItemHeight;
    //}
	CRect myrect;
	//m_pGridCellContol->GetTextRect(&myrect);

	//CCellID myid = m_pGridCellContol->AssertValid
	//m_pGridCtl->GetCellRect( , &myrect);

	pRetVal->left = 0;
	pRetVal->top = 0;
	pRetVal->width = 20;
	pRetVal->height = 10;
    return S_OK;
}


// Implementation of IRawElementProviderFragment::GetEmbeddedFragmentRoots.
// Retrieves any fragment roots that may be hosted in this element.
//
IFACEMETHODIMP CGridCellProvider::GetEmbeddedFragmentRoots(SAFEARRAY ** pRetVal)
{
    *pRetVal = NULL;
    return S_OK;
}

// Implementation of IRawElementProviderFragment::SetFocus.
// Responds to the control receiving focus through a UI Automation request.
//
IFACEMETHODIMP CGridCellProvider::SetFocus()
{
    //Select();
    return S_OK;
}

// Implementation of IRawElementProviderFragment::get_FragmentRoot.
// Retrieves the root element of this fragment.
//
IFACEMETHODIMP CGridCellProvider::get_FragmentRoot(IRawElementProviderFragmentRoot** pRetVal)
{
    IRawElementProviderFragmentRoot* pRoot = this->m_pGridCtl->GetGridProvider();
    if (pRoot == NULL)
    {
        return E_FAIL;
    }
    pRoot->AddRef();
    *pRetVal = pRoot;
    return S_OK;
}
//
//// IRawElementProviderFragmentRoot implementation
////
//// Implementation of IRawElementProviderFragmentRoot::ElementProviderFromPoint.
//// Retrieves the IRawElementProviderFragment interface for the item at the specified 
//// point (in client coordinates).
//// UI Spy uses this to determine what element is under the cursor when Ctrl is pressed.
////
//IFACEMETHODIMP CGridCellProvider::ElementProviderFromPoint(double x, double y, IRawElementProviderFragment** pRetVal)
//{
//	//POINT pt;
//	//pt.x = (LONG)x;
//	//pt.y = (LONG)y;
//	//ScreenToClient(m_pGridCtl->m_hWnd, &pt);
//	///*
//	//int itemIndex = m_pControl->IndexFromY(pt.y);
//	//ListItemProvider* pItem = GetItemProviderByIndex(itemIndex);  
//	//if (pItem != NULL)
//	//{
//	//	*pRetVal = static_cast<IRawElementProviderFragment*>(pItem);
//	//	pItem->AddRef();
//	//}
//	//else 
//	//{
//	//	*pRetVal = NULL;
//	//}*/
//
//	//*pRetVal = NULL;
//	return S_OK;
//}
//
//// Implementation of IRawElementProviderFragmentRoot::GetFocus.
//// Retrieves the provider for the list item that is selected when the control gets focus.
////
//IFACEMETHODIMP CGridCellProvider::GetFocus(IRawElementProviderFragment** pRetVal)
//{
//	//*pRetVal = NULL;
//	//ListItemProvider* pItem = GetItemProviderByIndex(m_pControl->GetSelectedIndex()); 
//	//if (pItem != NULL)
//	//{
//	//	pItem->AddRef();
//	//	*pRetVal = pItem;
//	//}
//	*pRetVal = NULL;
//	return S_OK;
//}
//
//
//// ISelectionProvider implementation
////
//// Implementation of ISelectionProvider::GetSelection.
//// Gets the provider(s) for the items(s) selected in the list box. 
//// In this case, only a single item can be selected.
////
//IFACEMETHODIMP CGridCellProvider::GetSelection(SAFEARRAY** pRetVal)
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
//	*pRetVal = NULL;
//	return S_OK;
//}
//
//// Implementation of ISelectionProvider::get_CanSelectMultiple.
////
//IFACEMETHODIMP CGridCellProvider::get_CanSelectMultiple(BOOL *pRetVal)
//{
//	*pRetVal = FALSE;
//	return S_OK;
//}
//// Implementation of ISelectionProvider::get_IsSelectionRequired.
////
//IFACEMETHODIMP CGridCellProvider::get_IsSelectionRequired(BOOL *pRetVal)
//{
//	*pRetVal = TRUE;
//	return S_OK;
//}
//
//
// ISelectionItemProvider implementation.

// Implementation of ISelectionItemProvider::Select.
// Responds to a request by UI Automation to select the item.
//
IFACEMETHODIMP CGridCellProvider::Select()
{
//    int index = m_pListItemControl->GetItemIndex();
//    m_pListControl->SelectItem(index);
//
//    // Force refresh even when app doesn't have focus.
//    InvalidateRect(m_pListControl->GetHwnd(), NULL, false); 
    return S_OK;
}

// Implementation of ISelectionItemProvider::AddToSelection.
// Responds to a request by UI Automation to add the item to the selection.
// Because this is a single-selection list box, the call is equivalent to Select().
//
IFACEMETHODIMP CGridCellProvider::AddToSelection()
{
    //Select();
    return S_OK;
}

// Implementation of ISelectionItemProvider::RemoveFromSelection.
// Responds to a request by UI Automation to remove the item from the selection.
// One and only one item must always be selected, so this is not implemented.
//
IFACEMETHODIMP CGridCellProvider::RemoveFromSelection()
{
    return UIA_E_INVALIDOPERATION;
}

// Implementation of ISelectionItemProvider::get_IsSelected.
// Advises whether the item is selected.
//
IFACEMETHODIMP CGridCellProvider::get_IsSelected(BOOL *pRetVal)
{
    //*pRetVal = 
    //    (m_pListItemControl->GetItemIndex() == m_pListControl->GetSelectedIndex());
	*pRetVal = NULL;
    return S_OK;
}

// Implementation of ISelectionItemProvider::get_SelectionContainer.
// Returns the UI Automation provider for the list control.
//
IFACEMETHODIMP CGridCellProvider::get_SelectionContainer(
    IRawElementProviderSimple **pRetVal)
{
    IRawElementProviderSimple* pParent = 
        static_cast<IRawElementProviderSimple*>(m_pGridCtl->GetGridProvider());
    pParent->AddRef();
    *pRetVal = pParent;
	//*pRetVal = NULL;
    return S_OK;
}

// Raises an event when an item is added to the list.
//
void CGridCellProvider::NotifyItemAdded()
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
void CGridCellProvider::NotifyItemRemoved()
{
    //if (UiaClientsAreListening())
    //{
    //    ListProvider* listProvider = m_pListControl->GetListProvider();

    //    // Construct the partial runtime ID for the removed child
    //    int id = m_pListItemControl->GetId();
    //    int rId[] = { UiaAppendRuntimeId, id };

    //    UiaRaiseStructureChangedEvent(listProvider, StructureChangeType_ChildRemoved, rId, ARRAYSIZE(rId));
    //}
}

// Raises an event when a list item is selected.
//
void CGridCellProvider::NotifyElementSelected()
{
    //if (UiaClientsAreListening())
    //{
    //    UiaRaiseAutomationEvent(this, UIA_SelectionItem_ElementSelectedEventId);
    //}
}


