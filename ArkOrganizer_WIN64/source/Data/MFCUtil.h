#pragma once

class MFCUtil {
public:
    static std::wstring GetDlgText(CWnd const * parent, int dlg_id)
    {
        CString text;
        parent->GetDlgItemTextW(dlg_id, text);
        return std::wstring(text);
    }
};
