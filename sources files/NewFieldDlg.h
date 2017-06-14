#pragma once
#include "afxwin.h"
#include "FieldEntity.h"
 

// CNewFieldDlg dialog

class CNewFieldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewFieldDlg)

public:
	CNewFieldDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewFieldDlg();

// Dialog Data
	enum { IDD = IDD_ADD_FIELD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_nFieldName;
	CComboBox m_nDataTypeLst;
	CString m_nDataType;
	CString m_nFieldDefaultValue;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString getFieldName() { return m_nFieldName; };
	CString getDataType() { return m_nDataType; };
	CString getFieldDefaultValue() { return m_nFieldDefaultValue; };
	BOOL getPrimaryKeyCheck() { return m_nPK; }
	BOOL getNotNullCheck() { return m_nNotNull; }
	CFieldEntity* m_nFieldEntity;
	CFieldEntity* getField();
	BOOL m_nNotNull;
	BOOL m_nPK;
	int getIntegrities();
	afx_msg void OnBnClickedPrimaryKey();
};
