#pragma once
////#include <ole2.h>
//#include <assert.h>
//#include <UIAutomation.h>
////#include <UIAutomationCore.h>
//////#include <UIAutomationClient.h>
////#include <UIAutomationCoreApi.h>
//using namespace std;
//#pragma comment(lib, "uiautomationcore.lib")

//#import "UIAutomationCore.idl"

class CGridCell;
class CGridCtrl;
class CGridCtrlProvider;

class CGridCellProvider : public IRawElementProviderSimple, 
	public IRawElementProviderFragment, 
	public ISelectionItemProvider

{

public:
	// Constructor / destructor
	CGridCellProvider(CGridCell* pControl); 

	// IUnknown methods
	IFACEMETHODIMP_(ULONG) AddRef();
	IFACEMETHODIMP_(ULONG) Release();
	IFACEMETHODIMP QueryInterface(REFIID riid, void**ppInterface);

	// IRawElementProviderSimple methods
	IFACEMETHODIMP get_ProviderOptions(ProviderOptions * pRetVal);
	IFACEMETHODIMP GetPatternProvider(PATTERNID iid,IUnknown * * pRetVal );
	IFACEMETHODIMP GetPropertyValue(PROPERTYID idProp,VARIANT * pRetVal );
	IFACEMETHODIMP get_HostRawElementProvider(IRawElementProviderSimple ** pRetVal );

	// IRawElementProviderFragment methods
	IFACEMETHODIMP Navigate(NavigateDirection direction, IRawElementProviderFragment ** pRetVal );
	IFACEMETHODIMP GetRuntimeId(SAFEARRAY ** pRetVal );
	IFACEMETHODIMP get_BoundingRectangle(UiaRect * pRetVal );
	IFACEMETHODIMP GetEmbeddedFragmentRoots(SAFEARRAY ** pRetVal );
	IFACEMETHODIMP SetFocus();
	IFACEMETHODIMP get_FragmentRoot( IRawElementProviderFragmentRoot * * pRetVal );

	//// IRawElementProviderFragmenRoot methods
	//IFACEMETHODIMP ElementProviderFromPoint(double x, double y, IRawElementProviderFragment ** pRetVal );
	//IFACEMETHODIMP GetFocus(IRawElementProviderFragment ** pRetVal );

	//// ISelectionProvider methods
	//IFACEMETHODIMP GetSelection(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP get_CanSelectMultiple(BOOL *pRetVal);
	//IFACEMETHODIMP get_IsSelectionRequired(BOOL *pRetVal);

	// ISelectionItemProvider methods
	IFACEMETHODIMP Select();
	IFACEMETHODIMP AddToSelection();
	IFACEMETHODIMP RemoveFromSelection();
	IFACEMETHODIMP get_IsSelected(BOOL *pRetVal);
	IFACEMETHODIMP get_SelectionContainer(IRawElementProviderSimple **pRetVal);

	// Various methods
	void NotifyItemAdded();
	void NotifyItemRemoved();
	void NotifyElementSelected();

private:
	virtual ~CGridCellProvider();

	// Ref Counter for this COM object
	ULONG m_refCount;
	// Pointers to the owning item control and list control.
	CGridCell* m_pGridCellContol;
	CGridCtrl* m_pGridCtl;
};
