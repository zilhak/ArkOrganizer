#include <pch.h>
#include <resource.h>
#include "ResultViewer.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(ResultViewer, CDialogEx)

ResultViewer::ResultViewer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESULT_VIEWER, pParent)
{

}

ResultViewer::~ResultViewer()
{
}

void ResultViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL ResultViewer::OnInitDialog()
{
	int ret = CDialogEx::OnInitDialog();

	return ret;
}

BEGIN_MESSAGE_MAP(ResultViewer, CDialogEx)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

void ResultViewer::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 900;
	lpMMI->ptMinTrackSize.y = 800;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

BOOL ResultViewer::PreTranslateMessage(MSG * pMsg)
{
    if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)) {
		//if (pMsg->hwnd == output_path_ctrl_.m_hWnd) {
		//	configure::SetSummarizeOutputPath(MFCUtil::GetDlgText(this, IDC_VIDEOSUMMARIZER_OUTPUT_PATH));
		//	configure::SaveConfig();
		//} else if (pMsg->hwnd == video_path_ctrl_.m_hWnd) {
		//	configure::SetSummarizeInputPath(MFCUtil::GetDlgText(this, IDC_VIDEOSUMMARIZER_INPUT_PATH));
		//	configure::SaveConfig();
		//}
		
		return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}
