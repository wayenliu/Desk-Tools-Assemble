
// Desk Tools Assemble.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDeskToolsAssembleApp:
// See Desk Tools Assemble.cpp for the implementation of this class
//

class CDeskToolsAssembleApp : public CWinAppEx
{
public:
	CDeskToolsAssembleApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDeskToolsAssembleApp theApp;