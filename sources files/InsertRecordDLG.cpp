// InsertRecordDLG.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "InsertRecordDLG.h"
#include "afxdialogex.h"


// CInsertRecordDLG dialog

IMPLEMENT_DYNAMIC(CInsertRecordDLG, CDialogEx)

CInsertRecordDLG::CInsertRecordDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsertRecordDLG::IDD, pParent)
	, m_editValue(_T(""))
{

}

CInsertRecordDLG::~CInsertRecordDLG()
{
}

void CInsertRecordDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_editValue);
}


BEGIN_MESSAGE_MAP(CInsertRecordDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInsertRecordDLG::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInsertRecordDLG::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CInsertRecordDLG::OnNMClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CInsertRecordDLG::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// CInsertRecordDLG message handlers


 


void CInsertRecordDLG::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CInsertRecordDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect cr;
	GetClientRect(&cr);
	m_list.ModifyStyle(NULL, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, _T("Field Name"), LVCFMT_LEFT, cr.Width() / 3);
	m_list.InsertColumn(1, _T("Field Type"), LVCFMT_LEFT, cr.Width() / 3);
	m_list.InsertColumn(2, _T("Value"), LVCFMT_LEFT, cr.Width()/3 );

	// Call the set Table

	SetTable(insertTable);

	for (unsigned i = 0; i < insertTable->fieldArray.size(); i++)
	{
		int nItem;

		nItem = m_list.InsertItem(0, insertTable->fieldArray.at(i).getFieldName());
		m_list.SetItemText(nItem, 1, insertTable->fieldArray.at(i).getFieldType());
	}

	// TODO:  Add extra initialization here

	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInsertRecordDLG::SetTable(CTableEntity *pTable)
{
	insertTable = pTable;
}


void CInsertRecordDLG::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	Invalidate();
	HWND hWnd1 = ::GetDlgItem(m_hWnd, IDC_LIST1);
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE)pNMHDR;
	RECT rect;
	//get the row number
	nItem = temp->iItem;
	//get the column number
	nSubItem = temp->iSubItem;
	if (nSubItem == 0 || nSubItem == 1 || nSubItem == -1 || nItem == -1)
		return;
	//Retrieve the text of the selected subItem from the list
	CString str = GetItemText(hWnd1, nItem, nSubItem);

	RECT rect1, rect2;
	// this macro is used to retrieve the Rectanle of the selected SubItem
	ListView_GetSubItemRect(hWnd1, temp->iItem, temp->iSubItem, LVIR_BOUNDS, &rect);
	//Get the Rectange of the listControl
	::GetWindowRect(temp->hdr.hwndFrom, &rect1);
	//Get the Rectange of the Dialog
	::GetWindowRect(m_hWnd, &rect2);

	int x = rect1.left - rect2.left;
	int y = rect1.top - rect2.top;

	if (nItem != -1)
		::SetWindowPos(::GetDlgItem(m_hWnd, IDC_EDIT1), HWND_TOP, rect.left + x, rect.top + 14 , rect.right - rect.left - 7, rect.bottom - rect.top , NULL);
	::ShowWindow(::GetDlgItem(m_hWnd, IDC_EDIT1), SW_SHOW);
	::SetFocus(::GetDlgItem(m_hWnd, IDC_EDIT1));
	//Draw a Rectangle around the SubItem
	::Rectangle(::GetDC(temp->hdr.hwndFrom), rect.left, rect.top - 1, rect.right, rect.bottom);
	//Set the listItem text in the EditBox
	::SetWindowText(::GetDlgItem(m_hWnd, IDC_EDIT1), str);
	*pResult = 0;

}

CString CInsertRecordDLG::GetItemText(HWND hWnd, int nItem, int nSubItem) const
{
	LVITEM lvi;
	memset(&lvi, 0, sizeof(LVITEM));
	lvi.iSubItem = nSubItem;
	CString str;
	int nLen = 128;
	int nRes;
	do
	{
		nLen *= 2;
		lvi.cchTextMax = nLen;
		lvi.pszText = str.GetBufferSetLength(nLen);
		nRes = (int)::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)nItem,
			(LPARAM)&lvi);
	} while (nRes == nLen - 1);
	str.ReleaseBuffer();
	return str;
}


void CInsertRecordDLG::OnEnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int row = m_list.GetSelectionMark();
	m_list.SetItemText(row, 2, m_editValue);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);

}

void CInsertRecordDLG::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	for (unsigned i = 0; i < insertTable->fieldArray.size(); i++)
	{
		m_recordEntity.Put(m_list.GetItemText(i, 0),m_list.GetItemText(i,2));
	}
	UpdateData(FALSE);
	CDialogEx::OnOK();
	
}

CRecordEntity CInsertRecordDLG::GetRecord()
{
	return m_recordEntity;
}