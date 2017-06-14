#pragma once

#include "RKDBMSDoc.h"
#include "Global.h"

// CDBView view 

class CDBView : public CTreeView
{
	DECLARE_DYNCREATE(CDBView)

protected:
	CDBView();           // protected constructor used by dynamic creation
	virtual ~CDBView();

// Attributes
public:
	HTREEITEM hDBNode;
	HTREEITEM hTable;
	CImageList m_dbImglist;
	//int index;

// Operations
public:
	CRKDBMSDoc* GetDocument() const;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();


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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void CreateDatabaseTree(CString db_name);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCreateDatabase();
	afx_msg void OnOpenDatabase();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in CDBView.cpp
inline CRKDBMSDoc* CDBView::GetDocument() const
{
	return reinterpret_cast<CRKDBMSDoc*>(m_pDocument);
}
#endif 

