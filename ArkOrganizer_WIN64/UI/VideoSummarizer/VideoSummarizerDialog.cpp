#include <pch.h>
#include <resource.h>
#include "VideoSummarizerDialog.h"
#include "afxdialogex.h"

#include <VideoSummarize/VideoSummarizeRunner.h>
#include <Data/MFCUtil.h>
#include <Data/AoConfig.h>

IMPLEMENT_DYNAMIC(VideoSummarizerDialog, CDialogEx)

VideoSummarizerDialog::VideoSummarizerDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEO_SUMMARIZER, pParent)
{

}

VideoSummarizerDialog::~VideoSummarizerDialog()
{
	if (runner_) {
		delete runner_;
		runner_ = nullptr;
	}
}

BOOL VideoSummarizerDialog::OnInitDialog()
{
	int ret = CDialogEx::OnInitDialog();

	runner_ = new VideoSummarizerRunner();

	return ret;
}

void VideoSummarizerDialog::SetInputPath(std::wstring const & path)
{
	SetDlgItemTextW(IDC_VIDEOSUMMARIZER_INPUT_PATH, path.c_str());
}

void VideoSummarizerDialog::SetOutputPath(std::wstring const & path)
{
	SetDlgItemTextW(IDC_VIDEOSUMMARIZER_OUTPUT_PATH, path.c_str());
}

void VideoSummarizerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEOSUMMARIZER_INPUT_PATH, video_path_ctrl_);
	DDX_Control(pDX, IDC_VIDEOSUMMARIZER_OUTPUT_PATH, output_path_ctrl_);
}


BEGIN_MESSAGE_MAP(VideoSummarizerDialog, CDialogEx)
	ON_BN_CLICKED(BUTTON_VIDEOSUMMARIZER_RUN, VideoSummarizerDialog::OnClickRun)
END_MESSAGE_MAP()


void VideoSummarizerDialog::OnClickRun()
{
	CString input_home_path;
	CString output_home_path;
	GetDlgItemTextW(IDC_VIDEOSUMMARIZER_INPUT_PATH, input_home_path);
	GetDlgItemTextW(IDC_VIDEOSUMMARIZER_OUTPUT_PATH, output_home_path);
	std::wstring input_path_wstr(input_home_path);
	std::wstring output_path_wstr(output_home_path);

	runner_->SetInputHomeDirPath(input_path_wstr);
	runner_->SetOutputHomeDirPath(output_path_wstr);
	runner_->Run();
}

void VideoSummarizerDialog::OnClickStop()
{

}

BOOL VideoSummarizerDialog::PreTranslateMessage(MSG * pMsg)
{
    if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)) {
		if (pMsg->hwnd == output_path_ctrl_.m_hWnd) {
			configure::SetSummarizeOutputPath(MFCUtil::GetDlgText(this, IDC_VIDEOSUMMARIZER_OUTPUT_PATH));
			configure::SaveConfig();
		} else if (pMsg->hwnd == video_path_ctrl_.m_hWnd) {
			configure::SetSummarizeInputPath(MFCUtil::GetDlgText(this, IDC_VIDEOSUMMARIZER_INPUT_PATH));
			configure::SaveConfig();
		}
		
		return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}
