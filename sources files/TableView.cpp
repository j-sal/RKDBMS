// TableView.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "TableView.h"


// CTableView

IMPLEMENT_DYNCREATE(CTableView, CListView)

CTableView::CTableView()
{
	 
}

CTableView::~CTableView()
{
}

BEGIN_MESSAGE_MAP(CTableView, CListView)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CTableView::OnNMRClick)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CTableView diagnostics

#ifdef _DEBUG
void CTableView::AssertValid() const
{
	CListView::AssertValid();
}

CRKDBMSDoc* CTableView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRKDBMSDoc)));
	return (CRKDBMSDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CTableView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTableView message handlers


void CTableView::OnInitialUpdate()
{
	// TODO: Add your specialized code here and/or call the base class
	createtableHeader();
	CListView::OnInitialUpdate();
}

void CTableView::createtableHeader()
{
	CListCtrl &tableCtl = GetListCtrl();
	CRect cr;
	GetClientRect(&cr);
	tableCtl.ModifyStyle(NULL, LVS_REPORT);
	tableCtl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	tableCtl.InsertColumn(0, _T("Column"), LVCFMT_LEFT, cr.Width() / 5);
	tableCtl.InsertColumn(1, _T("Data Type"), LVCFMT_LEFT, cr.Width() / 5);
	tableCtl.InsertColumn(2, _T("Not Null"), LVCFMT_LEFT, cr.Width() / 5);
	tableCtl.InsertColumn(3, _T("Primary Key"), LVCFMT_LEFT, cr.Width() / 5);
	tableCtl.InsertColumn(4, _T("Default Value"), LVCFMT_LEFT, cr.Width() / 5);
}

void CTableView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{

	// TODO: Add your specialized code here and/or call the base class
	
	CListCtrl &tableCtl = GetListCtrl();
	
	if (currentTable != GetDocument()->m_nTableName)
	{
		currentTable = GetDocument()->m_nTableName;
		resetTableView();
	}
	
	switch (lHint)
	{
		case UPDATE_ADD_FIELD:
		{
			CFieldEntity *pField = (CFieldEntity*)pHint;

			int nItem;

			nItem = tableCtl.InsertItem(0, pField->getFieldName());
			tableCtl.SetItemText(nItem, 1, pField->getFieldType());

			if (pField->getFieldIntegrities() == 0)
			{
				tableCtl.SetItemText(nItem, 2, L"Required");
				tableCtl.SetItemText(nItem, 3, L"Primary Key");
			}
			else if (pField->getFieldIntegrities() == 1)
			{
				tableCtl.SetItemText(nItem, 2, L"Required");
			}
			tableCtl.SetItemText(nItem, 4, pField->getDefaultValue());
		}
			break;
		case UPDATE_EDIT_TABLE:
		{
			resetTableView();
			CTableEntity *pTable = (CTableEntity*)pHint;
			for (unsigned i = 0; i < pTable->fieldArray.size(); i++)
			{
				int nItem;

				nItem = tableCtl.InsertItem(0, pTable->fieldArray.at(i).getFieldName());
				tableCtl.SetItemText(nItem, 1, pTable->fieldArray.at(i).getFieldType());

				if (pTable->fieldArray.at(i).getFieldIntegrities() == 0)
				{
					tableCtl.SetItemText(nItem, 2, L"Required");
					tableCtl.SetItemText(nItem, 3, L"Primary Key");
				}
				else if (pTable->fieldArray.at(i).getFieldIntegrities() == 1)
				{
					tableCtl.SetItemText(nItem, 2, L"Required");
				}
				tableCtl.SetItemText(nItem, 4, pTable->fieldArray.at(i).getDefaultValue());
			}

		}
			break;
	default:
		break;
	}
	
}


void CTableView::resetTableView()
{
	CListCtrl &ctlLView = GetListCtrl();
	ctlLView.DeleteAllItems();
	while (ctlLView.DeleteColumn(0))
			;

	UpdateWindow();

	createtableHeader();
	UpdateWindow();
	
}


void CTableView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	CPoint pt;

	::GetCursorPos(&pt);

	CMenu* menu_bar = AfxGetMainWnd()->GetMenu();
	CMenu* field_menu = menu_bar->GetSubMenu(3);
	ASSERT(field_menu);

	field_menu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, AfxGetApp()->GetMainWnd());

	*pResult = 0;


}


int CTableView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	

	return 0;
}


