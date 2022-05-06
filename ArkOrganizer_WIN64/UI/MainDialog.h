#pragma once
#include <filesystem>
#include <memory>

#include <UI/FileVeiwer/AoFileViewer.h>
#include <UI/VideoSummarizer/VideoSummarizerDialog.h>
#include <UI/ResultViewer/ResultViewer.h>

#include <OneFileBringer/OneFileBringer.h>

class MainDialog : public CDialogEx
{
protected:
	DECLARE_MESSAGE_MAP()
public:
	MainDialog(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARKORGANIZER_WIN64_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	void AllocForm();


protected:
	HICON m_hIcon;
	AoFileViewer* file_viewer_ = nullptr;
	VideoSummarizerDialog* video_summarizer = nullptr;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();

private:
	afx_msg void OnVideoSummarize();
	afx_msg void OnFileBring();
	afx_msg void OnViewOutput();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedPathUndo();
	afx_msg void OnEnChangeEdit();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg) override;
};
