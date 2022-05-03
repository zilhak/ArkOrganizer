
// ArkOrganizer_WIN64Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ArkOrganizer_WIN64.h"
#include "ArkOrganizer_WIN64Dlg.h"
#include "afxdialogex.h"

#include "VideoSummarizeRunner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CArkOrganizerWIN64Dlg::CArkOrganizerWIN64Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARKORGANIZER_WIN64_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArkOrganizerWIN64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CArkOrganizerWIN64Dlg, CDialogEx)
	ON_BN_CLICKED(BUTTON_VIDEOSUMMARIZER, &CArkOrganizerWIN64Dlg::OnVideoSummarize)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT1, &CArkOrganizerWIN64Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

BOOL CArkOrganizerWIN64Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void CArkOrganizerWIN64Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CArkOrganizerWIN64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CArkOrganizerWIN64Dlg::OnVideoSummarize()
{
	CString inserted_path;
	GetDlgItemTextW(PATH_EDIT, inserted_path);
	CT2CA ansiString(inserted_path);
	std::string str(ansiString);

	VideoSummarizerRunner runner;
	runner.SetInputHomeDirPath(str);
	runner.Run();
}

