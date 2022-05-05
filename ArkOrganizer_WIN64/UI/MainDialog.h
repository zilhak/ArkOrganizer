#pragma once
#include <string>
#include <filesystem>
#include <memory>

#include <VideoSummarize/VideoSummarizeRunner.h>
#include <OneFileBringer/OneFileBringer.h>
#include <ResultManager/ResultManager.h>
#include <UI/FileVeiwer/AoFileViewer.h>

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


// 구현입니다.
protected:
	HICON m_hIcon;
	AoFileViewer* file_viewer_ = nullptr;

	// 생성된 메시지 맵 함수
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
