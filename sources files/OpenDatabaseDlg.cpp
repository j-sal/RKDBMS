// OpenDatabaseDlg.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "DataStructure.h"
#include "CharHelper.h"
#include "OpenDatabaseDlg.h"
#include "afxdialogex.h"
#include "AppException.h"


// COpenDatabaseDlg dialog

IMPLEMENT_DYNAMIC(COpenDatabaseDlg, CDialogEx)

COpenDatabaseDlg::COpenDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenDatabaseDlg::IDD, pParent)
{

}

COpenDatabaseDlg::~COpenDatabaseDlg()
{
}

void COpenDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATABASE_NAME_LIST, m_nDatabaseNameLst);
}


BEGIN_MESSAGE_MAP(COpenDatabaseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &COpenDatabaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COpenDatabaseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// COpenDatabaseDlg message handlers

BOOL COpenDatabaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowTextW(_T("Open Database"));

	CStdioFile file;
	CFileException dbFileException;
	m_nDatabaseNameLst.ResetContent();

	if (file.Open(_T("ruanko.db"), CFile::modeRead | CFile::typeBinary), &dbFileException)
	{

		DatabaseBlock *dbInfo = NULL;
		dbInfo = (DatabaseBlock*)malloc(sizeof(DatabaseBlock));
		int index = 0;
		while (file.Read(dbInfo, sizeof(DatabaseBlock)))
		{
			index++;
			CString str = L"";
			str = CCharHelper::VarcharToCString(dbInfo->name);
			m_nDatabaseNameLst.AddString(str);
			file.Seek(sizeof(DatabaseBlock)*index,CFile::begin);
		}

	}
	else
	{
		throw new CAppException(_T("System database file failed to open"));
	}
	file.Close();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

CString COpenDatabaseDlg::getDatabaseName()
{
	return m_nDatabaseName;
}


void COpenDatabaseDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	m_nDatabaseNameLst.GetWindowTextW(m_nDatabaseName);

	if (getDatabaseName().IsEmpty())
	{
		AfxMessageBox(_T("Database name cannot be empty, select a name!"));
	}

	else
	{
		//UpdateData(FALSE);
		CDialogEx::OnOK();
	}
}


void COpenDatabaseDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
