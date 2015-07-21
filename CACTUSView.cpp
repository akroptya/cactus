// CACTUSView.cpp : implementation of the CCACTUSView class
//

#include "stdafx.h"
#include "CACTUS.h"

#include "CACTUSDoc.h"
#include "CACTUSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCACTUSView

IMPLEMENT_DYNCREATE(CCACTUSView, CView)

BEGIN_MESSAGE_MAP(CCACTUSView, CView)
	//{{AFX_MSG_MAP(CCACTUSView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCACTUSView construction/destruction

CCACTUSView::CCACTUSView()
{
	// TODO: add construction code here

}

CCACTUSView::~CCACTUSView()
{
}

BOOL CCACTUSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCACTUSView drawing

void CCACTUSView::OnDraw(CDC* pDC)
{
	CCACTUSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCACTUSView printing

BOOL CCACTUSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCACTUSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCACTUSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCACTUSView diagnostics

#ifdef _DEBUG
void CCACTUSView::AssertValid() const
{
	CView::AssertValid();
}

void CCACTUSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCACTUSDoc* CCACTUSView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCACTUSDoc)));
	return (CCACTUSDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCACTUSView message handlers
