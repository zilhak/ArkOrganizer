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
	
	for (auto bitmap_ptr : caching_image_list_) {
		if (bitmap_ptr != nullptr) {
			delete(bitmap_ptr);
		}
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
    image_panel_.ModifyStyle(SS_TYPEMASK,SS_BITMAP);

	SetDlgItemTextW(VIEWER_IMAGE_HOME, configure::GetViewerImagePath().c_str());
	SetDlgItemTextW(VIEWER_VIDEO_HOME, configure::GetViewerVideoPath().c_str());
	hwnd_image_path_edit_= GetDlgItem(VIEWER_IMAGE_HOME)->m_hWnd;
	hwnd_video_path_edit_= GetDlgItem(VIEWER_VIDEO_HOME)->m_hWnd;

	return ret;
}

void ResultViewer::RunCaching()
{
	if (caching_image_list_.size() <= image_index_)
		return;

	if (caching_image_list_[image_index_] != nullptr)
		return;

	int index = image_index_ - caching_range_;
	if (index < 0)
		index = 0;
	int end_index = image_index_ + caching_range_ + 1;
	if (caching_image_list_.size() <= end_index) {
		end_index = caching_image_list_.size() - 1;
	}

	for (; index < end_index; index++) {
		if (caching_image_list_[index] == nullptr) {
            std::wstring image_path = image_list_[index];
            CImage image;
            CString path_cstring = image_path.c_str();
			CBitmap *bitmap = new CBitmap();
            image.Load(path_cstring);
            bitmap->Attach(image.Detach());
			caching_image_list_[index] = bitmap;
		}
	}
}

void ResultViewer::ShowImage()
{
	if (image_list_.size() <= image_index_)
		return;

	if (use_image_cache_)
		RunCaching();

	std::wstring image_path = image_list_[image_index_];
	CBitmap bitmap;

	if (caching_image_list_[image_index_] != nullptr) {
        image_panel_.SetBitmap((HBITMAP)*caching_image_list_[image_index_]);
	} else {
        CImage image;
        CString path_cstring = image_path.c_str();
        image.Load(path_cstring);
        bitmap.Attach(image.Detach());
        image_panel_.SetBitmap(bitmap);
	}

	SetDlgItemTextW(VIEWER_NUMBER_CURRENT, std::to_wstring(image_index_ + 1).c_str());
	SetDlgItemTextW(VIEWER_CUR_IMAGENAME, image_path.c_str());

	std::wstring matching_file = result_manager_->SetAndGetMatchingFileName(image_path);
	if (matching_file.empty())
		matching_icon_.SetCheck(0);
	else 
		matching_icon_.SetCheck(1);
}

void ResultViewer::NextImage()
{
	image_index_++;
	if (image_list_.size() <= image_index_) {
		image_index_--;
		return;
		
	}

	ShowImage();
}

void ResultViewer::PrevImage()
{ 
	if (0 < image_index_)
		image_index_--;
	else
		return;

	ShowImage();
}

void ResultViewer::MoveVideo(int command_index)
{
	result_manager_->StoreMatchingFile(command_index);
    matching_icon_.SetCheck(0);
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
	image_index_ = 0;
	result_manager_->SetImageHome(MFCUtil::GetDlgText(this, VIEWER_IMAGE_HOME));
	result_manager_->SetVideoHome(MFCUtil::GetDlgText(this, VIEWER_VIDEO_HOME));
	image_list_ = result_manager_->MakeImageList();
	std::wstring image_total_num_str = std::to_wstring(image_list_.size());
	GetDlgItem(VIEWER_NUMBER_TOTAL)->SetWindowTextW(image_total_num_str.c_str());

	caching_image_list_.resize(image_list_.size(), nullptr);
	ShowImage();
}

BOOL ResultViewer::PreTranslateMessage(MSG * pMsg)
{
    if (pMsg->hwnd == hwnd_image_path_edit_) {
        if (pMsg->wParam == VK_RETURN) {
            configure::SetViewerImagePath(MFCUtil::GetDlgText(this, VIEWER_IMAGE_HOME));
            configure::SaveConfig();
            return TRUE;
		} 
    } else if (pMsg->hwnd == hwnd_video_path_edit_) {
        if (pMsg->wParam == VK_RETURN) {
            configure::SetViewerVideoPath(MFCUtil::GetDlgText(this, VIEWER_VIDEO_HOME));
            configure::SaveConfig();
            return TRUE;
		}
    } else if (pMsg->message == WM_KEYDOWN) { 
		if (pMsg->wParam == 'A') {
			PrevImage();
		} else if (pMsg->wParam == 'D') {
			NextImage();
		} else if (pMsg->wParam == 'Z') {
			MoveVideo(1);
		} else if (pMsg->wParam == 'X') {
			MoveVideo(2);
		} else if (pMsg->wParam == 'C') {
			MoveVideo(3);
		} else if (pMsg->wParam == 'V') {
			MoveVideo(4);
		}

        return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}

