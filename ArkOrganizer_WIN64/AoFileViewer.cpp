#include "pch.h"
#include "ArkOrganizer_WIN64.h"
#include "AoFileViewer.h"

IMPLEMENT_DYNCREATE(AoFileViewer, CFormView)

AoFileViewer::AoFileViewer()
	: CFormView(IDD_ARKORGANIZER_WIN64_DIALOG)
{

}

AoFileViewer::~AoFileViewer()
{
}

void AoFileViewer::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(AoFileViewer, CFormView)
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


// AoFileViewer 메시지 처리기
