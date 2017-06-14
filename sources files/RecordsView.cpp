// RecordsView.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "RecordsView.h"
#include "Global.h"


// CRecordsView

IMPLEMENT_DYNCREATE(CRecordsView, CListView)

CRecordsView::CRecordsView()
{

}

CRecordsView::~CRecordsView()
{
}

BEGIN_MESSAGE_MAP(CRecordsView, CListView)
END_MESSAGE_MAP()


// CRecordsView diagnostics

#ifdef _DEBUG
void CRecordsView::AssertValid() const
{
	CListView::AssertValid();
}

CRKDBMSDoc* CRecordsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRKDBMSDoc)));
	return (CRKDBMSDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CRecordsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG

void CRecordsView::SetTable(CTableEntity *pTable)
{
	displayTable = pTable;
}


// CRecordsView message handlers


void CRecordsView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CListCtrl &listCtl = GetListCtrl();
	
	listCtl.ModifyStyle(NULL, LVS_REPORT);
	listCtl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

}


void CRecordsView::resetRecordsView()
{
	CListCtrl &ctlLView = GetListCtrl();
	ctlLView.DeleteAllItems();
	while (ctlLView.DeleteColumn(0))
		;

	UpdateWindow();

}

void CRecordsView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	CListCtrl &listCtl = GetListCtrl();
	CRect cr;
	GetClientRect(&cr);

	/*if (currentTable != GetDocument()->m_nTableName)
	{
		currentTable = GetDocument()->m_nTableName;
		resetRecordsView();
	}*/

	switch (lHint)
	{
	case UPDATE_INSERT_RECORD:
	{
		resetRecordsView();
		CTableEntity *pTable = GetDocument()->m_ntbEntity;
		for (unsigned i = 0; i < pTable->fieldArray.size(); i++)
		{
			//	//int nItem;

			listCtl.InsertColumn(i, pTable->fieldArray.at(i).getFieldName(), LVCFMT_LEFT, cr.Width() / pTable->fieldArray.size());
			//

		}
		CRecordEntity* pRec = (CRecordEntity*)pHint;

		int nItem;
		for (unsigned i = 0; i < pTable->fieldArray.size(); i++)
		{
			if (i == 0)
			{
				nItem = listCtl.InsertItem(0, pRec->Get(pTable->fieldArray.at(i).getFieldName()));
			}
			else
			{
				listCtl.SetItemText(nItem, i, pRec->Get(pTable->fieldArray.at(i).getFieldName()));
			}
			
		}
		/*while (listCtl.DeleteColumn(0))
			;

		UpdateWindow();*/

								 //resetRecordsView();
								/**/


	}
		break;
	case UPDATE_OPEN_TABLE:
	{
							  resetRecordsView();
		CTableEntity *pTable = (CTableEntity*)pHint;
		for (unsigned i = 0; i < pTable->fieldArray.size(); i++)
		{
			//	//int nItem;

			listCtl.InsertColumn(i, pTable->fieldArray.at(i).getFieldName(), LVCFMT_LEFT, cr.Width() / pTable->fieldArray.size());
								 	
		}
		//resetRecordsView();
		for (unsigned index = 0; index < GetDocument()->recArray.size(); index++)
		{
			int nItem;
			for (unsigned i = 0; i < pTable->fieldArray.size(); i++)
			{
				if (i==0)
				{
					nItem = listCtl.InsertItem(0, GetDocument()->recArray.at(index).Get(pTable->fieldArray.at(i).getFieldName()));
				}
				else
				{
					listCtl.SetItemText(nItem, i, GetDocument()->recArray.at(index).Get(pTable->fieldArray.at(i).getFieldName()));
				}
				
			}
			
		}

	}
	}
}

