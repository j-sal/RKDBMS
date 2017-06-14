#pragma once
#include "RKDBMSDoc.h"
#include "Global.h"

// CTableView view 

class CTableView : public CListView
{
	DECLARE_DYNCREATE(CTableView)

protected:
	//CTableView();           // protected constructor used by dynamic creation
	//virtual ~CTableView();
	//CListCtrl &tableCtl;
public: 
	//modification related to view switch
	CTableView();
	virtual ~CTableView();
	CString currentTable;

	// Operations
public:
	CRKDBMSDoc* GetDocument() const;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	void resetTableView();
	void createtableHeader();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in CTableView.cpp
inline CRKDBMSDoc* CTableView::GetDocument() const
{
	return reinterpret_cast<CRKDBMSDoc*>(m_pDocument);
}
#endif
