#include <pch.h>
#include <resource.h>
#include "ResultViewer.h"
#include "afxdialogex.h"

#include <ResultManager/ResultManager.h>
#include <Data/MFCUtil.h>
#include <Data/AoConfig.h>

IMPLEMENT_DYNAMIC(ResultViewer, CDialogEx)

ResultViewer::ResultViewer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESULT_VIEWER, pParent)
{

}

ResultViewer::~ResultViewer()
{
	if (result_manager_) {
		delete result_manager_;
		result_manager_ = nullptr;
	}
}

void ResultViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, VIEWER_IMAGE_PANEL, image_panel_);
	DDX_Control(pDX, VIEWER_MATCHING, matching_icon_);
}

BOOL ResultViewer::OnInitDialog()
{
	int ret = CDialogEx::OnInitDialog();
	
	result_manager_ = new ResultManager();

	SetDlgItemTextW(VIEWER_IMAGE_HOME, configure::GetViewerImagePath().c_str());
	SetDlgItemTextW(VIEWER_VIDEO_HOME, configure::GetViewerVideoPath().c_str());

	return ret;
}

void ResultViewer::ShowImage()
{

}

void ResultViewer::NextImage()
{

}

void ResultViewer::PrevImage()
{ 
}

void ResultViewer::MoveVideo(int command_index)
{

}

BEGIN_MESSAGE_MAP(ResultViewer, CDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(VIEWER_BUTTON_LOAD, ResultViewer::OnClickLoad)
END_MESSAGE_MAP()

void ResultViewer::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 900;
	lpMMI->ptMinTrackSize.y = 800;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void ResultViewer::OnClickLoad()
{
	result_manager_->SetImageHome(MFCUtil::GetDlgText(this, VIEWER_IMAGE_HOME));
	result_manager_->SetVideoHome(MFCUtil::GetDlgText(this, VIEWER_VIDEO_HOME));
	image_list_ = result_manager_->MakeImageList();
}

BOOL ResultViewer::PreTranslateMessage(MSG * pMsg)
{
    if (pMsg->message == WM_KEYDOWN) { 
		if (pMsg->wParam == VK_RETURN) {
            if (pMsg->hwnd == GetDlgItem(VIEWER_IMAGE_HOME)->m_hWnd) {
                configure::SetSummarizeOutputPath(MFCUtil::GetDlgText(this, VIEWER_IMAGE_HOME));
                configure::SaveConfig();
            } else if (pMsg->hwnd == GetDlgItem(VIEWER_VIDEO_HOME)->m_hWnd) {
                configure::SetSummarizeInputPath(MFCUtil::GetDlgText(this, VIEWER_VIDEO_HOME));
                configure::SaveConfig();
            }
		}
		
		return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}
