// DBView.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "DBView.h"
#include "RKDBMSView.h"
#include "CreateDatabaseDlg.h"

#include "MainFrm.h"
#include "RKDBMSDoc.h"

 
// CDBView

IMPLEMENT_DYNCREATE(CDBView, CTreeView)

CDBView::CDBView()
{

}

CDBView::~CDBView()
{
}

BEGIN_MESSAGE_MAP(CDBView, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDBView::OnTvnSelchanged)
	ON_COMMAND(IDM_CREATE_DATABASE, &CDBView::OnCreateDatabase)
	ON_COMMAND(IDM_OPEN_DATABASE, &CDBView::OnOpenDatabase)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}


// CDBMS_SRSView drawing

void CDBView::OnDraw(CDC* /*pDC*/)
{
	CRKDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

// CDBView diagnostics

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CTreeView::AssertValid();
}
CRKDBMSDoc* CDBView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRKDBMSDoc)));
	return (CRKDBMSDoc*)m_pDocument;
}


#ifndef _WIN32_WCE
void CDBView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDBView message handlers

int CDBView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CDBView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	m_dbImglist.Create(16, 16, ILC_COLOR8, 1, 4);
	m_dbImglist.Add(AfxGetApp()->LoadIcon(IDI_ICON_DB));
	
	GetTreeCtrl().SetImageList(&m_dbImglist, TVSIL_NORMAL);

	

	GetTreeCtrl().ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);//| 
	GetDocument()->dbTreeView = this;
	

	CString strError = GetDocument()->getError();
	if (strError.GetLength() != 0)
	{
		AfxMessageBox(strError);
		GetDocument()->setError(_T(""));
	}
	else
	{
		CreateDatabaseTree(GetDocument()->m_dbEntity->getDBName());
		GetDocument()->m_nDatabaseName = GetDocument()->m_dbEntity->getDBName();
		GetDocument()->SetTitle(GetDocument()->m_dbEntity->getDBName());
	}
	
}

void CDBView::CreateDatabaseTree(CString db_name)
{

	// If there is anything in the tree, remove it
	GetTreeCtrl().DeleteAllItems();

	CTreeCtrl &dbTreeCtrl = this->GetTreeCtrl();
	

	hDBNode = dbTreeCtrl.InsertItem(db_name, 0, 0);
	//dbTreeCtrl.Expand(hDBNode, TVE_EXPAND);

}





void CDBView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CRKDBMSDoc *m_pDocument = GetDocument();
	CTreeCtrl &dbTreeCtrl = this->GetTreeCtrl();
	// Find out what item is selected in the tree
	HTREEITEM selectedNode = dbTreeCtrl.GetSelectedItem();
	// Get the string of the selected node
	CString strSelected = dbTreeCtrl.GetItemText(selectedNode);
	// Just in case the selected node as a parent, get that parent
	HTREEITEM nodParentLeague = dbTreeCtrl.GetParentItem(selectedNode);
	// Find the string of the parent of the selected node, if it has a parent
	CString strParent = dbTreeCtrl.GetItemText(nodParentLeague);

	if (strParent == m_pDocument->m_nDatabaseName)
	{
		m_pDocument->m_nTableName = strSelected;
		hTable = selectedNode;
		m_pDocument->setEditTable(strSelected);
	}
	*pResult = 0;
}



void CDBView::OnCreateDatabase()
{
	CCreateDatabaseDlg createDBDlg;
	createDBDlg.DoModal();
	if (createDBDlg.getDatabaseName().GetLength() != 0)
	{
		CRKDBMSDoc *m_pDocument = GetDocument();
		m_pDocument->m_nDatabaseName = createDBDlg.getDatabaseName();
		m_pDocument->CreateDatabase();
		CString strError = m_pDocument->getError();
		if (strError.GetLength() != 0)
		{
			AfxMessageBox(strError);
			GetDocument()->setError(_T(""));
		}
		else
		{
			if (m_pDocument->m_nDatabaseName.GetLength() != 0)
			{
				CreateDatabaseTree(m_pDocument->m_nDatabaseName);
				m_pDocument->SetTitle(m_pDocument->m_nDatabaseName);
			}
		}
	}
	
}

void CDBView::OnOpenDatabase()
{
	// TODO: Add your command handler code here
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	CRKDBMSDoc *m_pDocument = GetDocument();
	SetCurrentDirectory(m_pDocument->m_pRootDir);
	COpenDatabaseDlg openDBDlg;
	openDBDlg.DoModal();

	if (openDBDlg.getDatabaseName().GetLength()!= 0)
	{
		m_pDocument = GetDocument();
		m_pDocument->m_nDatabaseName = openDBDlg.getDatabaseName();
		
		m_pDocument->GetDatabase();
		CString strError = m_pDocument->getError();
		if (strError.GetLength() != 0)
		{
			AfxMessageBox(strError);
			GetDocument()->setError(_T(""));
			SetCurrentDirectory(currentDir);
		}
		else
		{
			if (m_pDocument->m_dbEntity->getDBName().GetLength() != 0)
			{
				CreateDatabaseTree(m_pDocument->m_dbEntity->getDBName());
				m_pDocument->LoadTables();
				std::vector<CTableEntity> tables = m_pDocument->tbArray ;
				
				CObject *object = (CObject*)&tables;
				m_pDocument->UpdateAllViews(NULL, UPDATE_OPEN_DATABASE, object);
				
				CMainFrame* pFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
				pFrm->switchView(pFrm->DEFAULT);
				m_pDocument->SetTitle(GetDocument()->m_dbEntity->getDBName());
			}
		}
	}
	else
	{
		SetCurrentDirectory(currentDir);
	}
	
}


void CDBView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	//GetTreeCtrl().DeleteAllItems();
	CTreeCtrl &dbTree = this->GetTreeCtrl();
	if (pSender == NULL)
	{
		switch (lHint)
		{
		case UPDATE_CREATE_TABLE:
		{

				CTableEntity *pTable = (CTableEntity*)pHint;
				hTable = dbTree.InsertItem(pTable->getTableName(), 0, 0, hDBNode);
				dbTree.Expand(hDBNode, TVE_EXPAND);

		}
			break;

		case UPDATE_ADD_FIELD:
		{

				CFieldEntity *pField = (CFieldEntity*)pHint;
				HTREEITEM hField, hCol;
				//hCol = dbTree.InsertItem(L"Column", 2, 0, hTable);
				hField = dbTree.InsertItem(pField->getFieldName(), 0, 0, hTable);
				dbTree.Expand(hTable, TVE_EXPAND);

		}
			break;
		case UPDATE_OPEN_DATABASE:
		{

				std::vector<CTableEntity> *tb = (std::vector<CTableEntity>*)pHint;
			
				for (unsigned index = 0; index < tb->size(); index++)
				{
					hTable = dbTree.InsertItem(tb->at(index).getTableName(), 0, 0, hDBNode);
					HTREEITEM hField, hCol;
					//hCol = dbTree.InsertItem(L"Column", 0, 0, hTable);
					for (unsigned i = 0; i < tb->at(index).fieldArray.size(); i++)
					{
						hField = dbTree.InsertItem(tb->at(index).fieldArray.at(i).getFieldName(), 0, 0, hTable);
					}
					//dbTree.Expand(hCol, TVE_EXPAND);
					dbTree.Expand(hTable, TVE_EXPAND);
				}
				
				dbTree.Expand(hDBNode, TVE_EXPAND);

		}
			break;

		}

	}
}
	
