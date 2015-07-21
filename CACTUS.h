// CACTUS.h : main header file for the CACTUS application
//

#if !defined(AFX_CACTUS_H__41BE4124_224E_11D7_A510_B0A458C10700__INCLUDED_)
#define AFX_CACTUS_H__41BE4124_224E_11D7_A510_B0A458C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCACTUSApp:
// See CACTUS.cpp for the implementation of this class
//

class CCACTUSApp : public CWinApp
{
public:
	CCACTUSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCACTUSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCACTUSApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACTUS_H__41BE4124_224E_11D7_A510_B0A458C10700__INCLUDED_)
