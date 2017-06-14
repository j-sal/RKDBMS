#pragma once
#include "TableEntity.h"
#include "FileHelper.h"
#include <vector>
 
struct TableArray //store tables in one database
{
	CTableEntity* te;
	TableArray* nextTable;
};

class CTableDao
{
public:
	CTableDao();
	~CTableDao();

	bool IsValidFile(const CString filePath);
	bool CreateTbFile(const CString filename);
	bool TbExist(const CString, CTableEntity);
	bool Create(const CString filePath, CTableEntity &te);
	bool AddField(const CString filePath, CFieldEntity &fe);
	bool GetFields(const CString, CTableEntity&);
	int GetTables(const CString, std::vector<CTableEntity>&);
};

