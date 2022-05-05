#pragma once
#include <string>
#include <filesystem>

class CArkOrganizerWIN64Dlg : public CDialogEx
{
public:
	CArkOrganizerWIN64Dlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARKORGANIZER_WIN64_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVideoSummarize();
	afx_msg void OnFileBring();
	afx_msg void OnViewOutput();
};
