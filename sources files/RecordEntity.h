#pragma once

//#include "DataStructure.h"
 
class CRecordEntity
{
private:
	CMapStringToString m_mapdata;

public:
	CRecordEntity(const CRecordEntity &e);
	CRecordEntity();
	~CRecordEntity();
	void Put(CString strKey, CString strValue);
	void Put(CString strKey, int nValue);
	void Put(CString strKey, double dbValue);
	void Put(CString strKey, SYSTEMTIME t);
	CString Get(CString strKey);
};



