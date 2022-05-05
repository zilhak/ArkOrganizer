
// ArkOrganizer_WIN64Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ArkOrganizer_WIN64.h"
#include "ArkOrganizer_WIN64Dlg.h"
#include "afxdialogex.h"

#include "VideoSummarize/VideoSummarizeRunner.h"
#include <OneFileBringer/OneFileBringer.h>
#include <ResultManager/ResultManager.h>

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
	ON_BN_CLICKED(BUTTON_FILEBRINGER, &CArkOrganizerWIN64Dlg::OnFileBring)
	ON_BN_CLICKED(BUTTON_OUTPUTVIEW, &CArkOrganizerWIN64Dlg::OnViewOutput)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT1, &CArkOrganizerWIN64Dlg::OnEnChangeEdit1)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(BUTTON_PATH_UNDO, &CArkOrganizerWIN64Dlg::OnBnClickedPathUndo)
	ON_EN_CHANGE(PATH_EDIT, &CArkOrganizerWIN64Dlg::OnEnChangeEdit)
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
	std::wstring wstr(inserted_path);

	VideoSummarizerRunner runner;
	runner.SetInputHomeDirPath(wstr);
	runner.SetOutputHomeDirPath(L"F:\\test");
	runner.Run();
}

void CArkOrganizerWIN64Dlg::OnFileBring()
{
	CString inserted_path;
	GetDlgItemTextW(PATH_EDIT, inserted_path);
	std::wstring wstr(inserted_path);
	std::filesystem::path home_path(wstr);

	OneFileBringer::BringOneFile(home_path);
}

void CArkOrganizerWIN64Dlg::OnViewOutput()
{
	CString output_dir;
	GetDlgItemTextW(OUTPUT_PATH_EDIT, output_dir);
	std::wstring wstr(output_dir);
	std::filesystem::path home_path(wstr);
	
	ResultManager::viewResult(home_path);
}


void CArkOrganizerWIN64Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 600;
	lpMMI->ptMinTrackSize.y = 800;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CArkOrganizerWIN64Dlg::OnBnClickedPathUndo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CArkOrganizerWIN64Dlg::OnEnChangeEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
