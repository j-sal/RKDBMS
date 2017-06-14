#include "stdafx.h"
#include "RecordEntity.h"


 
CRecordEntity::CRecordEntity()
{
}


CRecordEntity::~CRecordEntity()
{
}

CRecordEntity::CRecordEntity(const CRecordEntity &e)
{
	//m_mapdata = e.m_mapdata;
	POSITION pos = e.m_mapdata.GetStartPosition();
	CString strFieldName, strValue;
	while (pos)
	{
		e.m_mapdata.GetNextAssoc(pos, strFieldName, strValue);
		m_mapdata.SetAt(strFieldName, strValue);
	}
}

void CRecordEntity::Put(CString strFieldName, CString strValue)
{
	m_mapdata.SetAt(strFieldName, strValue);
}

void CRecordEntity::Put(CString strKey, int nValue)
{
	CString nValTemp;
	nValTemp.Format(L"%d", nValue);
	m_mapdata.SetAt(strKey, nValTemp);
}

void CRecordEntity::Put(CString strKey, double dbValue)
{
	CString nValTemp;
	nValTemp.Format(L"%f", dbValue);
	m_mapdata.SetAt(strKey, nValTemp);

}

void CRecordEntity::Put(CString strKey, SYSTEMTIME t)
{
	//%u %u:%u:%u:%u
	/*t.wDayOfWeek,
		t.wHour, t.wMinute, t.wSecond,
		t.wMilliseconds*/
	CString nValTemp;
	nValTemp.Format(_T("%u-%u-%u"),
		t.wYear, t.wMonth, t.wDay);
}

CString CRecordEntity::Get(CString strKey)
{
	CString strFieldName = strKey, strVal;
	m_mapdata.Lookup(strFieldName, strVal);
	return strVal;
}

//CRecordEntity(CRecordEntity &e);
