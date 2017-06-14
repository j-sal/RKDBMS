#pragma once


// CCreateDatabaseDlg dialog 

class CCreateDatabaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateDatabaseDlg)

public:
	CCreateDatabaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCreateDatabaseDlg();

// Dialog Data
	enum { IDD = IDD_CREATE_DATABASE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_nDatabaseName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString getDatabaseName() const { return m_nDatabaseName; }
};
