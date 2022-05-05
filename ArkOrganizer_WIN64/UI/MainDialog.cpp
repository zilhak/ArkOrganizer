﻿
// ArkOrganizer_WIN64Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ArkOrganizer_WIN64.h"
#include "MainDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MainDialog::MainDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARKORGANIZER_WIN64_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void MainDialog::AllocForm()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect panel_rect;

	GetDlgItem(IDC_FILEVIEWER_RECT)->GetWindowRect(&panel_rect);
	ScreenToClient(&panel_rect);

	file_viewer_ = new AoFileViewer();
	file_viewer_->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, panel_rect, this, IDD_FILEVIEWER, &context);
	file_viewer_->OnInitialUpdate();
	file_viewer_->ShowWindow(SW_SHOW);
}

BEGIN_MESSAGE_MAP(MainDialog, CDialogEx)
	ON_BN_CLICKED(BUTTON_VIDEOSUMMARIZER, &MainDialog::OnVideoSummarize)
	ON_BN_CLICKED(BUTTON_FILEBRINGER, &MainDialog::OnFileBring)
	ON_BN_CLICKED(BUTTON_OUTPUTVIEW, &MainDialog::OnViewOutput)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT1, &MainDialog::OnEnChangeEdit1)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(BUTTON_PATH_UNDO, &MainDialog::OnBnClickedPathUndo)
	ON_EN_CHANGE(PATH_EDIT, &MainDialog::OnEnChangeEdit)
END_MESSAGE_MAP()

BOOL MainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	AllocForm();

	return TRUE;
}

void MainDialog::OnPaint()
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

void MainDialog::OnSize(UINT nType, int cx, int cy)
{
	if (file_viewer_) {
        CRect client;
        GetDlgItem(IDC_FILEVIEWER_RECT)->GetWindowRect(&client);
        ScreenToClient(&client);
		file_viewer_->MoveWindow(client);
		file_viewer_->Update();
	}
}

HCURSOR MainDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void MainDialog::OnVideoSummarize()
{
	CString inserted_path;
	GetDlgItemTextW(PATH_EDIT, inserted_path);
	std::wstring wstr(inserted_path);

	VideoSummarizerRunner runner;
	runner.SetInputHomeDirPath(wstr);
	runner.SetOutputHomeDirPath(L"F:\\test");
	runner.Run();
}

void MainDialog::OnFileBring()
{
	CString inserted_path;
	GetDlgItemTextW(PATH_EDIT, inserted_path);
	std::wstring wstr(inserted_path);
	std::filesystem::path home_path(wstr);

	OneFileBringer::BringOneFile(home_path);
}

void MainDialog::OnViewOutput()
{
	CString output_dir;
	GetDlgItemTextW(OUTPUT_PATH_EDIT, output_dir);
	std::wstring wstr(output_dir);
	std::filesystem::path home_path(wstr);
	
	ResultManager::viewResult(home_path);
}


void MainDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 600;
	lpMMI->ptMinTrackSize.y = 800;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void MainDialog::OnBnClickedPathUndo()
{
}


void MainDialog::OnEnChangeEdit()
{
}