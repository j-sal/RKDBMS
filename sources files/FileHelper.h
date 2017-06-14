#pragma once

#include "DBEntity.h"
#include "TableEntity.h"
#include "DataStructure.h"
#include "AppException.h"
#include <direct.h>


class CFileHelper
{
public:
	CFileHelper();
	~CFileHelper();

	static bool WriteFile(CString, CDBEntity&);
	static bool WriteFile(CString, CTableEntity&);
	static bool WriteFile(CString, CFieldEntity&);
	static void ReadFile(CString, CDBEntity);
	static void MoveToDBDirectory(CString);
	template <typename T>
	static bool WriteFile(CString, CString, T);
	
};

