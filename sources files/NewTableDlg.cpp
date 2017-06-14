// NewTableDlg.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "NewTableDlg.h"
#include "afxdialogex.h"
#include "AppException.h"


// NewTableDlg dialog

IMPLEMENT_DYNAMIC(NewTableDlg, CDialogEx)

NewTableDlg::NewTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewTableDlg::IDD, pParent)
	, m_nTableName(_T(""))
{

}

NewTableDlg::~NewTableDlg()
{
}

void NewTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nTableName);
}


BEGIN_MESSAGE_MAP(NewTableDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewTableDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &NewTableDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// NewTableDlg message handlers

BOOL NewTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowTextW(_T("Create Table"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void NewTableDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (getTableName().IsEmpty())
	{
		AfxMessageBox(_T("Table name cannot be empty, add a name!"));
	}
	else
	{
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}
}


void NewTableDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
