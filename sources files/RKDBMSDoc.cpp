
// RKDBMSDoc.cpp : implementation of the CRKDBMSDoc class
// 

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RKDBMS.h"
#endif

#include "RKDBMSDoc.h"


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRKDBMSDoc

IMPLEMENT_DYNCREATE(CRKDBMSDoc, CDocument)

BEGIN_MESSAGE_MAP(CRKDBMSDoc, CDocument)
END_MESSAGE_MAP()


// CRKDBMSDoc construction/destruction

CRKDBMSDoc::CRKDBMSDoc()
{
	// TODO: add one-time construction code here

}

CRKDBMSDoc::~CRKDBMSDoc()
{
}

BOOL CRKDBMSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle(L"no database");
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	m_pRootDir = currentDir;
	m_dbEntity = new CDBEntity(L"Ruanko");
	try
	{
		bool createDBRes = CDBLogic::CreateDatabase(*m_dbEntity);
	}
	catch (CAppException* e)
	{
		m_strError = e->getErrorMessage();
		delete e;
	}

	return TRUE;
}




// CRKDBMSDoc serialization

void CRKDBMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CRKDBMSDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CRKDBMSDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRKDBMSDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRKDBMSDoc diagnostics

#ifdef _DEBUG
void CRKDBMSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRKDBMSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRKDBMSDoc commands

CString CRKDBMSDoc::getError()
{
	return m_strError;
}

void CRKDBMSDoc::setError(CString strError)
{
	m_strError = strError;
}


void CRKDBMSDoc::CreateDatabase()
{

	m_dbEntity = new CDBEntity(m_nDatabaseName);
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);

	try
	{
		SetCurrentDirectory(m_pRootDir);
		m_dbEntity->setDBFilePath((_T("%s\\data\\%s\\"), m_pRootDir, m_dbEntity->getDBName()));
		bool createDBRes = CDBLogic::CreateDatabase(*m_dbEntity);
	}
	catch (CAppException* e)
	{
		m_strError = e->getErrorMessage();
		delete e;
		SetCurrentDirectory(currentDir);
	}

	

}

void CRKDBMSDoc::GetDatabase()
{
	
	m_dbEntity = new CDBEntity();
	//TCHAR currentDir[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, currentDir);

	try
	{
		SetCurrentDirectory(m_pRootDir);
		bool res = CDBLogic::GetDatabase(m_nDatabaseName, *m_dbEntity);
	}
	catch (CAppException* e)
	{
		m_strError = e->getErrorMessage();
		delete e;
		//SetCurrentDirectory(currentDir);
	}
	
}


CTableEntity* CRKDBMSDoc::CreateTable(CString tableName)
{
	CTableEntity* pTable = new CTableEntity(tableName);
	bool res = TRUE;
	try
	{
		res = CTableLogic::CreateTable(m_nDatabaseName, *pTable);
	}
	catch (CAppException* e)
	{
		m_strError = e->getErrorMessage();
		delete e;
	}

	if (res==TRUE)
	{

		tbArray.push_back(*pTable);
	}
	else
	{
		delete pTable;
	}


	return pTable;
}

void CRKDBMSDoc::setEditTable(CString tb_name)
{
	for (unsigned i = 0; i < tbArray.size(); i++)
	{
		if (tbArray.at(i).getTableName() == tb_name)
		{
			m_ntbEntity = &tbArray.at(i);
			break;
		}
	}
}



CFieldEntity* CRKDBMSDoc::AddField(CFieldEntity& field)
{

	bool res=TRUE;
	try
	{
		res = CTableLogic::AddField(m_nDatabaseName, *m_ntbEntity, field);
	}
	catch (CAppException* e)
	{
		m_strError = e->getErrorMessage();
		delete e;
	}

	if ( res== TRUE)
	{
		m_ntbEntity->fieldArray.push_back(field);
	}
	else
	{
		delete &field;
	}


	return &field;
}


void CRKDBMSDoc::LoadTables()
{
	
	tbArray.clear();
	CTableEntity* pTable = new CTableEntity();
	try
	{
		int i = CTableLogic::GetTables(m_nDatabaseName, tbArray);
	}
	catch (CAppException* e)
	{
		m_strError = e->getErrorMessage();
		delete e;
	}

}

void CRKDBMSDoc::InsertRecord(CRecordEntity &re)
{
	CRecordLogic m_LogicRec;
	m_LogicRec.insert(*m_ntbEntity , re);
}

void CRKDBMSDoc::LoadRecord()
{
	recArray.clear();
	CRecordLogic recLogic;
	recLogic.SelectAll(*m_ntbEntity, recArray);
}