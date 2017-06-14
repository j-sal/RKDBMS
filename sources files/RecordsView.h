#pragma once

 
// CRecordsView view
#include "RKDBMSDoc.h"

class CRecordsView : public CListView
{
	DECLARE_DYNCREATE(CRecordsView)

protected:
	//CRecordsView();           // protected constructor used by dynamic creation
	//virtual ~CRecordsView();
	// Attributes
public:
	CTableEntity* displayTable;
	CString currentTable;
	// Operations
public:
	CRecordsView();
	virtual ~CRecordsView();
	CRKDBMSDoc* GetDocument() const;
	void SetTable(CTableEntity *pTable);
	void resetRecordsView();

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
};
#ifndef _DEBUG  // debug version in CRecordsView.cpp
inline CRKDBMSDoc* CRcordsView::GetDocument() const
{
	return reinterpret_cast<CRKDBMSDoc*>(m_pDocument);
}
#endif
