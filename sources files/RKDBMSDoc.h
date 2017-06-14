
// RKDBMSDoc.h : interface of the CRKDBMSDoc class
//

 
#pragma once

class CRKDBMSView;
class CDBView;
class CTableView;
class CAppException;
class CDBEntity;
class CTableEntity;
#include "DBLogic.h"
#include "TableLogic.h"
#include "AppException.h"
#include "OpenDatabaseDlg.h"
#include "CreateDatabaseDlg.h"
#include "NewTableDlg.h"
#include "TableEntity.h"
#include "FieldEntity.h"
#include "RecordEntity.h"
#include "RecordLogic.h"
#include <vector>



class CRKDBMSDoc : public CDocument
{
protected: // create from serialization only
	CRKDBMSDoc();
	DECLARE_DYNCREATE(CRKDBMSDoc)

// Attributes
public:
	CRKDBMSView* displayView;
	CDBView* dbTreeView;
	CTableView* tableView;
	CString m_pRootDir;//program's root directory
	CString m_strError;
	CString m_nDatabaseName;
	CString m_nTableName;
	CDBEntity *m_dbEntity;//CDBEntity object
	CTableEntity *m_ntbEntity;
	TableArray *m_nTbArray;
	std::vector<CTableEntity> tbArray;////CTableEntity object array
	std::vector<CRecordEntity> recArray;
	
private:
	
// Operations
public:
	CString getError();
	void setError(CString);
	void CreateDatabase();
	void GetDatabase();
	CTableEntity* CreateTable(CString);
	CFieldEntity* AddField(CFieldEntity&);
	void setEditTable(CString);
	void LoadTables();
	void InsertRecord(CRecordEntity&);
	void LoadRecord();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CRKDBMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
