#pragma once
#include "DataStructure.h"

 
class CDBEntity
{
private:
	
	CString m_strName;
	bool m_bType;
	CString m_strFilePath;
	SYSTEMTIME m_tCrTime;


public:
	CDBEntity(DatabaseBlock &db);
	CDBEntity(CString db_name);
	CDBEntity();
	CString getDBName();
	bool getDBType();
	CString getDBFilePath();
	SYSTEMTIME getDBCreationTime();
	void setDBName(CString db_name);
	void setDBType(bool db_type);
	void setDBFilePath(CString db_filepath);
	void setDBCreationTime(SYSTEMTIME db_ctime);
	~CDBEntity();
};


