#pragma once
 
//#include "DBEntity.h"
#include "DBDao.h"

class CDBLogic
{
public:
	CDBLogic();
	~CDBLogic();

	static bool CreateDatabase(CDBEntity);
	static bool GetDatabase(CString, CDBEntity&);
};

