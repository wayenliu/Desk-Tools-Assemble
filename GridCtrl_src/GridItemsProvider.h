#pragma once

class GridItems;
class CGridCtrl;
class CGridCtrlProvider;

class GridItemsProvider : public IRawElementProviderSimple, 
	public IRawElementProviderFragment, 
	//public ISelectionItemProvider,
	//public ITableProvider,
	//public ITableItemProvider,
	public IGridItemProvider
{
public:

	// Constructor / destructor
	GridItemsProvider(GridItems* pControl); 

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

	//// ISelectionItemProvider methods
	//IFACEMETHODIMP Select();
	//IFACEMETHODIMP AddToSelection();
	//IFACEMETHODIMP RemoveFromSelection();
	//IFACEMETHODIMP get_IsSelected(BOOL *pRetVal);
	//IFACEMETHODIMP get_SelectionContainer(IRawElementProviderSimple **pRetVal);

	////ITableProvider methods
	//IFACEMETHODIMP GetRowHeaders(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP GetColumnHeaders(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP get_RowOrColumnMajor(enum RowOrColumnMajor *pRetVal);

	////ItableitemProvider methods
	//IFACEMETHODIMP GetRowHeaderItems(SAFEARRAY * *pRetVal);
	//IFACEMETHODIMP GetColumnHeaderItems(SAFEARRAY * *pRetVal);

	//Griditemsprovider methods
	IFACEMETHODIMP get_Row(int *pRetVal);
	IFACEMETHODIMP get_Column(int *pRetVal);
	IFACEMETHODIMP get_RowSpan(int *pRetVal);
	IFACEMETHODIMP get_ColumnSpan(int *pRetVal);
	IFACEMETHODIMP get_ContainingGrid(IRawElementProviderSimple **pRetVal);


	// Various methods
	void NotifyItemAdded();
	void NotifyItemRemoved();
	void NotifyElementSelected();
	void NotifyTextChanged();

private:
	virtual ~GridItemsProvider();

	// Ref Counter for this COM object
	ULONG m_refCount;

	// Pointers to the owning item control and list control.
	GridItems* m_griditem;
	CGridCtrl* m_parentgrid;

};
