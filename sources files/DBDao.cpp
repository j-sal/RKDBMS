#include "stdafx.h"
#include "DBDao.h"
#include "AppException.h"
#include "FileHelper.h"
#include <direct.h>
 

CDBDao::CDBDao()
{
}


CDBDao::~CDBDao()
{
}


bool CDBDao::DBExist(CDBEntity db)
{
	bool res = FALSE;
	CStdioFile file;

	if (file.Open(_T("ruanko.db"), CFile::modeRead | CFile::typeBinary))
	{
		DatabaseBlock *dbInfo = NULL;
		dbInfo = (DatabaseBlock*)malloc(sizeof(DatabaseBlock));
		while (file.Read(dbInfo, sizeof(DatabaseBlock)))
		{
			CString str = L"";
			str = CCharHelper::VarcharToCString(dbInfo->name);

			if (str == db.getDBName())
			{
				res = TRUE;
				throw new CAppException(_T("Database already exist!"));
				break;
			}
		}

	}
	else
	{
		throw new CAppException(_T("A file Operation failed!"));
	}
	file.Close();

	return res;
}

bool CDBDao::ReadDBBlock(CString db_name, CDBEntity& db)
{
	bool res = FALSE;
	CStdioFile file;

	if (file.Open(_T("ruanko.db"), CFile::modeRead | CFile::typeBinary))
	{
		DatabaseBlock *dbInfo = NULL;
		dbInfo = (DatabaseBlock*)malloc(sizeof(DatabaseBlock));
		while (file.Read(dbInfo, sizeof(DatabaseBlock)))
		{
			CString str = L"";
			str = CCharHelper::VarcharToCString(dbInfo->name);

			if (str == db_name)
			{
				res = TRUE;
				break;
			}
		}

		CDBEntity dbEntity(*dbInfo);
		db.setDBName(dbEntity.getDBName());
		db.setDBFilePath(dbEntity.getDBFilePath());
		db.setDBType(dbEntity.getDBType());
		

	}
	else
	{
		throw new CAppException(_T("File Operation failed! Database information cannot be read!"));
	}
	file.Close();

	return res;
}



bool CDBDao::GetDatabase(CString db_name, CDBEntity& db)
{
	bool res = ReadDBBlock(db_name, db);
	if (res)
	{
		CFileHelper::MoveToDBDirectory(L"data");
		int i = _wchdir(db.getDBFilePath());
	}
	return res;
}


bool CDBDao::IsValidFile(CString filePath)
{
	bool res;
	CStdioFile file;

	if (file.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		res = TRUE;
	}
	else
	{
		res = FALSE;
		return res;
	}

	file.Close();

	return res;
}

bool CDBDao::CreateDBFile(CString fileName)
{
	bool res;
	CStdioFile file;

	if (file.Open(fileName, CFile::modeCreate | CFile::typeBinary))
	{
		res = TRUE;
	}
	else
	{
		res = FALSE;
	}

	file.Close();

	return res;
}

bool CDBDao::Create(CString db_name, CDBEntity &db, bool bAppend)
{

	bAppend = CFileHelper::WriteFile(_T("ruanko.db"), db);

	CFileHelper::MoveToDBDirectory(L"data");
	CFileHelper::MoveToDBDirectory(db_name);

	CString filePath;
	filePath.Format(_T("%s.inf"), db_name);

	IsValidFile(filePath);
	CreateDBFile(filePath);
	bAppend = CFileHelper::WriteFile(filePath, db);
	
	return bAppend;

}