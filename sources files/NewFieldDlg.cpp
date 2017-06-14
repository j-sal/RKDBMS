// NewFieldDlg.cpp : implementation file 
//

#include "stdafx.h"
#include "RKDBMS.h"
#include "NewFieldDlg.h"
#include "afxdialogex.h"


// CNewFieldDlg dialog

IMPLEMENT_DYNAMIC(CNewFieldDlg, CDialogEx)

CNewFieldDlg::CNewFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewFieldDlg::IDD, pParent)
	, m_nFieldName(_T(""))
	, m_nFieldDefaultValue(_T(""))
	, m_nPK(FALSE)
	, m_nNotNull(FALSE)
{

}

CNewFieldDlg::~CNewFieldDlg()
{
}

void CNewFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FIELD_NAME, m_nFieldName);
	DDV_MaxChars(pDX, m_nFieldName, 128);
	DDX_Control(pDX, IDC_DATA_TYPE_LIST, m_nDataTypeLst);
	DDX_Text(pDX, IDC_FIELD_DEFAULT_VALUE, m_nFieldDefaultValue);
	DDX_Check(pDX, IDC_NOT_NULL, m_nNotNull);
	DDX_Check(pDX, IDC_PRIMARY_KEY, m_nPK);
}


BEGIN_MESSAGE_MAP(CNewFieldDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewFieldDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNewFieldDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_PRIMARY_KEY, &CNewFieldDlg::OnBnClickedPrimaryKey)
END_MESSAGE_MAP()


// CNewFieldDlg message handlers

CFieldEntity* CNewFieldDlg::getField()
{
	return m_nFieldEntity;
}

int CNewFieldDlg::getIntegrities()
{
	if (m_nPK)
	{
		return 0;
	}
	else if (m_nNotNull)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void CNewFieldDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_nDataTypeLst.GetWindowTextW(m_nDataType);
	UpdateData();
	if (getFieldName().IsEmpty())
	{
		AfxMessageBox(_T("Field name cannot be empty, enter a name!"));
	}
	else
	{
		m_nFieldEntity = new CFieldEntity();
		m_nFieldEntity->setFieldName(m_nFieldName);
		m_nFieldEntity->setFieldType(m_nDataType);
		m_nFieldEntity->setDefaultValue(m_nFieldDefaultValue);
		m_nFieldEntity->setFieldIntegrities(getIntegrities());
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}
}


void CNewFieldDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CNewFieldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowTextW(_T("New Field"));

	CString dataTypes[] = {L"BOOLEAN",L"DOUBLE",L"DATETIME",L"INTEGER",L"VARCHAR"};

	for (int  i = 0; i < sizeof(dataTypes)/sizeof(CString) ; i++)
	{
		m_nDataTypeLst.AddString(dataTypes[i]);
	}
	m_nDataTypeLst.SetCurSel(4);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CNewFieldDlg::OnBnClickedPrimaryKey()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton(IDC_NOT_NULL, BST_CHECKED);
}
