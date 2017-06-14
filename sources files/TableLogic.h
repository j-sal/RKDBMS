#pragma once
#include "TableDao.h"
class CTableLogic
{
public:
	CTableLogic();
	~CTableLogic();
	static bool CreateTable(CString, CTableEntity&);
	static bool AddField(const CString, CTableEntity&, CFieldEntity&);
	static int GetTables(CString, std::vector<CTableEntity>&);
};

 