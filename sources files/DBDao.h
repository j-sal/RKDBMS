#pragma once
#include "DBEntity.h"
#include <direct.h>
#include "CharHelper.h"
 

class CDBDao
{
public:
	CDBDao();
	~CDBDao();
	
	bool IsValidFile(CString);
	bool CreateDBFile(CString);
	bool DBExist(CDBEntity);
	bool Create(CString, CDBEntity&, bool);
	bool ReadDBBlock(CString, CDBEntity&);
	bool GetDatabase(CString, CDBEntity&);
};

