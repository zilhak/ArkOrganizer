#pragma once

class AoFileViewer : public CFormView
{
	DECLARE_DYNCREATE(AoFileViewer)
protected:
	DECLARE_MESSAGE_MAP()
public:
	AoFileViewer();
	virtual ~AoFileViewer();

public:
	void Update();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEVIEWER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
    afx_msg virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, 
                        const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

protected:
	afx_msg virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnDraw(CDC * dc) override;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

};


