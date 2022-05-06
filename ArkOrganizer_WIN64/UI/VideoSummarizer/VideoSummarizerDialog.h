#pragma once

class VideoSummarizerRunner;

class VideoSummarizerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(VideoSummarizerDialog)
	DECLARE_MESSAGE_MAP()

public:
	VideoSummarizerDialog(CWnd* pParent = nullptr);
	virtual ~VideoSummarizerDialog();

public:
	void SetInputPath(std::wstring const & path);
	void SetOutputPath(std::wstring const & path);

private:
	VideoSummarizerRunner* runner_ = nullptr;
	CMFCEditBrowseCtrl video_path_ctrl_;
	CMFCEditBrowseCtrl output_path_ctrl_;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEO_SUMMARIZER };
#endif
public:
	afx_msg BOOL OnInitDialog() override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

private:
	void OnClickRun();
	void OnClickStop();
};
