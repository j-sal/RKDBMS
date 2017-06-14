 
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "Global.h"
#include "AW_CMultiViewSplitter.h"
#include "DBView.h"
#include "TableView.h"
#include "RecordsView.h"
#include "RKDBMSView.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	//CSplitterWnd m_wndSplitter;
	AW_CMultiViewSplitter	m_wndSplitter;
	int tableView, defaultView, recordsView;// ID of different views


public:

// Operations
public:


// Overrides
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnNewTable();
	afx_msg void OnAddField();
	void switchView(int);
	typedef enum {DEFAULT,TABLE,RECORDS} viewType;
	afx_msg void OnModifyTable();
	afx_msg void OnAddRecord();
	afx_msg void OnOpenTable();

};


