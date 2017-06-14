
// MainFrm.cpp : implementation of the CMainFrame class 
//

#include "stdafx.h"
#include "RKDBMS.h"

#include "RKDBMSDoc.h"
#include "NewTableDlg.h"
#include "NewFieldDlg.h"
#include "InsertRecordDLG.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(IDM_NEW_TABLE, &CMainFrame::OnNewTable)
	ON_COMMAND(IDM_ADD_FIELD, &CMainFrame::OnAddField)
	ON_COMMAND(IDM_MODIFY_TABLE, &CMainFrame::OnModifyTable)
	ON_COMMAND(IDM_ADD_RECORD, &CMainFrame::OnAddRecord)
	ON_COMMAND(IDM_QUERY_RECORDS, &CMainFrame::OnOpenTable)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetTitle(L"Database Management System");
	switchView(DEFAULT);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	//calculate client size 
	CRect cr;
	GetClientRect(&cr);

	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
	
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDBView), CSize(200, cr.Height()), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	
	defaultView = m_wndSplitter.AddView(0, 1, RUNTIME_CLASS(CRKDBMSView), cr.Width() - 200, cr.Height(), pContext);
	tableView = m_wndSplitter.AddView(0, 1, RUNTIME_CLASS(CTableView), cr.Width() - 200, cr.Height(), pContext);
	recordsView = m_wndSplitter.AddView(0, 1, RUNTIME_CLASS(CRecordsView), cr.Width() - 200, cr.Height(), pContext);

	return TRUE;

}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnNewTable()
{
	// TODO: Add your command handler code here
	NewTableDlg newTbDlg;
	newTbDlg.DoModal();

	if (newTbDlg.getTableName().GetLength()!=0)
	{
		CRKDBMSDoc *m_pDocument = (CRKDBMSDoc*)GetActiveDocument();
		CTableEntity *pTable = m_pDocument->CreateTable(newTbDlg.getTableName());
		CString strError = m_pDocument->getError();
		if (strError.GetLength() != 0)
		{
			AfxMessageBox(strError);
			m_pDocument->setError(_T(""));
		}
		else
		{
			CObject *object = (CObject*)pTable;
			m_pDocument->UpdateAllViews(NULL, UPDATE_CREATE_TABLE, object);
			switchView(TABLE);
		}
	}
}

void CMainFrame::OnAddField()
{
	// TODO: Add your command handler code here
	CNewFieldDlg newFieldDlg;
	newFieldDlg.DoModal();
	if (newFieldDlg.getFieldName().GetLength() != 0)
	{

		CRKDBMSDoc *m_pDocument = (CRKDBMSDoc*)GetActiveDocument();
		CFieldEntity* field = new CFieldEntity(*newFieldDlg.getField());
		CFieldEntity *pField = m_pDocument->AddField(*field);
		
		CObject *object = (CObject*)pField;
		m_pDocument->UpdateAllViews(NULL, UPDATE_ADD_FIELD, object);
	}


}

void CMainFrame::switchView(int nViewType)
{
	
	switch (nViewType)
	{
	case DEFAULT:
		m_wndSplitter.ShowView(defaultView);
		break;
	case TABLE:
		m_wndSplitter.ShowView(tableView);
		break;
	case RECORDS:
		m_wndSplitter.ShowView(recordsView);
	}
	
}


void CMainFrame::OnModifyTable()
{
	// TODO: Add your command handler code here
	CRKDBMSDoc *m_pDocument = (CRKDBMSDoc*)GetActiveDocument();
	CTableEntity* tbEntity = m_pDocument->m_ntbEntity;
	CObject *object = (CObject*)tbEntity;
	switchView(TABLE);
	m_pDocument->UpdateAllViews(NULL, UPDATE_EDIT_TABLE, object);

}


void CMainFrame::OnAddRecord()
{
	CRKDBMSDoc *m_pDocument = (CRKDBMSDoc*)GetActiveDocument();
	CTableEntity* tbEntity = m_pDocument->m_ntbEntity;
	CInsertRecordDLG dlg;
	dlg.SetTable(tbEntity);
	dlg.DoModal();
	CRecordEntity recordEntity = (dlg.GetRecord());
	m_pDocument->InsertRecord(recordEntity);
	switchView(RECORDS);
	CObject *object = (CObject*)&recordEntity;
	m_pDocument->UpdateAllViews(NULL, UPDATE_INSERT_RECORD, object);

	
}


void CMainFrame::OnOpenTable()
{
	// TODO: Add your command handler code here
	CRKDBMSDoc *m_pDocument = (CRKDBMSDoc*)GetActiveDocument();
	CTableEntity* tbEntity = m_pDocument->m_ntbEntity;
	if (tbEntity!=NULL)
	{
		m_pDocument->LoadRecord();
		switchView(RECORDS);
		CObject *object = (CObject*)tbEntity;
		m_pDocument->UpdateAllViews(NULL, UPDATE_OPEN_TABLE, object);
	}
}


