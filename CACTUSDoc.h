// CACTUSDoc.h : interface of the CCACTUSDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CACTUSDOC_H__41BE412A_224E_11D7_A510_B0A458C10700__INCLUDED_)
#define AFX_CACTUSDOC_H__41BE412A_224E_11D7_A510_B0A458C10700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSet.h"

class CCACTUSDoc : public CDocument
{
protected: // create from serialization only
	CCACTUSDoc();
	DECLARE_DYNCREATE(CCACTUSDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCACTUSDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCACTUSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCACTUSDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACTUSDOC_H__41BE412A_224E_11D7_A510_B0A458C10700__INCLUDED_)
