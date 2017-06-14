// CreateDatabaseDlg.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "CreateDatabaseDlg.h"
#include "afxdialogex.h"
#include "AppException.h"



// CCreateDatabaseDlg dialog

IMPLEMENT_DYNAMIC(CCreateDatabaseDlg, CDialogEx)

CCreateDatabaseDlg::CCreateDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCreateDatabaseDlg::IDD, pParent)
	, m_nDatabaseName(_T(""))
{

}

CCreateDatabaseDlg::~CCreateDatabaseDlg()
{
}

void CCreateDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nDatabaseName);
}


BEGIN_MESSAGE_MAP(CCreateDatabaseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCreateDatabaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCreateDatabaseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCreateDatabaseDlg message handlers


void CCreateDatabaseDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (getDatabaseName().IsEmpty())
	{
		AfxMessageBox(_T("Database name cannot be empty, add a name!"));
	}
	else
	{
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}
	
}


void CCreateDatabaseDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CCreateDatabaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowTextW(_T("Create Database"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
