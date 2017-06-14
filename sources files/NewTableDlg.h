#pragma once

 
// NewTableDlg dialog

class NewTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewTableDlg)

public:
	NewTableDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~NewTableDlg();

// Dialog Data
	enum { IDD = IDD_NEW_TABLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_nTableName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString getTableName() const { return m_nTableName; }
};
