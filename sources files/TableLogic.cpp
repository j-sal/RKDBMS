#include "stdafx.h"
#include "TableLogic.h"
 

CTableLogic::CTableLogic()
{
}


CTableLogic::~CTableLogic()
{
}

bool CTableLogic::CreateTable(CString db_name, CTableEntity &te)
{
	CTableDao *newTable = new CTableDao() ;

	CString filepath;
	filepath.Format(_T("%s.tb"), db_name);
	if (newTable->IsValidFile(filepath))
	{
		if (!newTable->TbExist(filepath,te))
		{
			return newTable->Create(filepath, te);
		}
		else
		{
			return FALSE;
		}
		
	}
	else
	{
		if (newTable->CreateTbFile(filepath))
		{
			return newTable->Create(filepath, te);
		}
		else
		{
			return FALSE;
		}
	}
	
}

bool CTableLogic::AddField(const CString db_name, CTableEntity &te, CFieldEntity &fe)
{
	CTableDao *newTable = new CTableDao();
	bool res = TRUE;
	
	CString filepath;
	filepath.Format(_T("%s.tdf"), te.getTableName());
	if (newTable->IsValidFile(filepath))
	{
		res = newTable->AddField(filepath, fe);
	}
	else
	{
		if (newTable->CreateTbFile(filepath))
		{
			res = newTable->AddField(filepath, fe);
		}
		else
		{
			res = FALSE;
		}
	}
	return res;
}


int CTableLogic::GetTables(CString db_name, std::vector<CTableEntity>& tbArray)
{
	CTableDao tableDao;
	CString filepath;
	filepath.Format(_T("%s.tb"), db_name);
	int n_count = tableDao.GetTables(filepath, tbArray);
	
	return n_count;
}