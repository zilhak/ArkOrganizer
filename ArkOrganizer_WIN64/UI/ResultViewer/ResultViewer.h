#pragma once

class ResultViewer : public CDialogEx
{
	DECLARE_DYNAMIC(ResultViewer)
	DECLARE_MESSAGE_MAP()

public:
	ResultViewer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ResultViewer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESULT_VIEWER };
#endif

protected:
    BOOL OnInitDialog() override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

protected:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnClickLoad();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg) override;
};
