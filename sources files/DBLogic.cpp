#include "stdafx.h"
#include "DBLogic.h"

 
CDBLogic::CDBLogic()
{
}


CDBLogic::~CDBLogic()
{
}

bool CDBLogic::CreateDatabase(CDBEntity db)
{
	
	CDBDao dbDao;
	bool createRes = TRUE;

	if (dbDao.IsValidFile(_T("ruanko.db")))
	{
		if (!dbDao.DBExist(db))
		{
			return dbDao.Create(db.getDBName(), db, createRes);
		}
		else
		{
			return FALSE;
		}
		
	}
	else
	{
		if (dbDao.CreateDBFile(_T("ruanko.db")))
		{
			return dbDao.Create(db.getDBName(), db, createRes);
		}
		else
		{
			return FALSE;
		}
	}

}


bool CDBLogic::GetDatabase(CString db_name, CDBEntity& db)
{
	CDBDao dbDao;
	return  dbDao.GetDatabase(db_name, db);
}