// CACTUSDoc.cpp : implementation of the CCACTUSDoc class
//

#include "stdafx.h"
#include "CACTUS.h"

#include "CACTUSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCACTUSDoc

IMPLEMENT_DYNCREATE(CCACTUSDoc, CDocument)

BEGIN_MESSAGE_MAP(CCACTUSDoc, CDocument)
	//{{AFX_MSG_MAP(CCACTUSDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCACTUSDoc construction/destruction

CCACTUSDoc::CCACTUSDoc()
{
	// TODO: add one-time construction code here

}

CCACTUSDoc::~CCACTUSDoc()
{
}

BOOL CCACTUSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCACTUSDoc serialization

void CCACTUSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCACTUSDoc diagnostics

#ifdef _DEBUG
void CCACTUSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCACTUSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCACTUSDoc commands

BOOL CCACTUSDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	CDataSet* Data = new CDataSet;

	Data->CACTUS( lpszPathName );
	
	delete Data;

	return TRUE;
}

BOOL CCACTUSDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::CanCloseFrame(pFrame);
}
