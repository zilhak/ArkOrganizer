#pragma once
#include <vector>

class ResultManager;

class ResultViewer : public CDialogEx
{
	DECLARE_DYNAMIC(ResultViewer)
	DECLARE_MESSAGE_MAP()

public:
	ResultViewer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ResultViewer();

protected:
    BOOL OnInitDialog() override;

public:
	void RunCaching();
	void ShowImage();
	void NextImage();
	void PrevImage();
	void MoveVideo(int command_index);

private:
	std::vector<std::wstring> image_list_;
	std::vector<CBitmap*> caching_image_list_;
	ResultManager* result_manager_ = nullptr;
	CStatic image_panel_;
	CButton matching_icon_;
	size_t image_index_ = 0;
	bool use_image_cache_ = true;
	int caching_range_ = 20;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESULT_VIEWER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

protected:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnClickLoad();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg) override;
};
