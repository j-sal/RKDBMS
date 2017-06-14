#pragma once
#include "afxcmn.h"
#include "TableEntity.h"
#include "RecordEntity.h"

// CInsertRecordDLG dialog 

class CInsertRecordDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertRecordDLG)

public:
	CInsertRecordDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInsertRecordDLG();
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;

	int nItem, nSubItem;

// Dialog Data
	enum { IDD = IDD_INSERT_RECORD};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	void SetTable(CTableEntity *pTable);
	CRecordEntity GetRecord();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CRecordEntity m_recordEntity;
	CTableEntity* insertTable;
public:
	afx_msg void OnEnKillfocusEdit1();
	CString m_editValue;
};
