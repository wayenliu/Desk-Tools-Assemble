#pragma once

class GridItems;
class GridItemsProvider;
class CGridCtrl;

class CGridCtrlProvider : public IRawElementProviderSimple, 
	public IRawElementProviderFragment, 
	public IRawElementProviderFragmentRoot, 
	//public ISelectionProvider,
	//public ITableProvider,
	//public ITableItemProvider,
	public IGridProvider
{
public:
	CGridCtrlProvider(CGridCtrl* pControl);

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

	// IRawElementProviderFragmenRoot methods
	IFACEMETHODIMP ElementProviderFromPoint(double x, double y, IRawElementProviderFragment ** pRetVal );
	IFACEMETHODIMP GetFocus(IRawElementProviderFragment ** pRetVal );

	//// ISelectionProvider methods
	//IFACEMETHODIMP GetSelection(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP get_CanSelectMultiple(BOOL *pRetVal);
	//IFACEMETHODIMP get_IsSelectionRequired(BOOL *pRetVal);

	////ITableProvider methods
	//IFACEMETHODIMP GetRowHeaders(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP GetColumnHeaders(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP get_RowOrColumnMajor(enum RowOrColumnMajor *pRetVal);

	////ItableitemProvider methods
	//IFACEMETHODIMP GetRowHeaderItems(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP GetColumnHeaderItems(SAFEARRAY * *pRetVal);

	//IGridProvider methods
	IFACEMETHODIMP GetItem(int row, int column, IRawElementProviderSimple **pRetVal);
	IFACEMETHODIMP get_RowCount(int *pRetVal);
	IFACEMETHODIMP get_ColumnCount(int *pRetVal);

	// Various methods.
	GridItemsProvider* GetItemProviderByIndex(int index);

private:
	virtual ~CGridCtrlProvider();

	// Ref counter for this COM object.
	ULONG m_refCount;
	// Parent control.
	HWND m_controlHwnd;
	CGridCtrl* m_pControl;
};
