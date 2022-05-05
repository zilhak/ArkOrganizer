#include "pch.h"
#include "../ArkOrganizer_WIN64.h"
#include "AoFileViewer.h"

IMPLEMENT_DYNCREATE(AoFileViewer, CFormView)

AoFileViewer::AoFileViewer() : CFormView(IDD_FILEVIEWER)
{
	
}

AoFileViewer::~AoFileViewer()
{
}

void AoFileViewer::Update()
{
	RedrawWindow();
}

BOOL AoFileViewer::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, 
                          const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void AoFileViewer::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(AoFileViewer, CFormView)
    ON_WM_SIZE()
END_MESSAGE_MAP()

#ifdef _DEBUG
void AoFileViewer::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void AoFileViewer::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void AoFileViewer::OnDraw(CDC* dc)
{
	RECT rect;
	this->GetClientRect(&rect);
	dc->DrawTextW(_T("haha"), &rect, DT_CENTER | DT_VCENTER | DT_SMART);
	dc->DrawFocusRect(&rect);
}

void AoFileViewer::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);
}
