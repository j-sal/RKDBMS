#pragma once
#include "afxwin.h"
 


// COpenDatabaseDlg dialog

class COpenDatabaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COpenDatabaseDlg)

public:
	COpenDatabaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COpenDatabaseDlg();

// Dialog Data
	enum { IDD = IDD_OPEN_DATABASE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_nDatabaseNameLst;
	CString getDatabaseName();
	CString m_nDatabaseName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
