#include "stdafx.h"
#include "DBEntity.h"
#include "CharHelper.h"
 
CDBEntity::CDBEntity()
{
}


CDBEntity::~CDBEntity()
{
}

CDBEntity::CDBEntity(CString db_name)
{
	m_strName = db_name;
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	m_strFilePath.Format(_T("%s\\data\\%s\\"),currentDir, db_name);//set database path
	m_bType = 1;
	GetSystemTime(&m_tCrTime);
}

CDBEntity::CDBEntity(DatabaseBlock &db)
{
	m_strName = CCharHelper::VarcharToCString(db.name);
	m_bType = db.type;
	m_strFilePath = CCharHelper::VarcharToCString(db.filepath);
	m_tCrTime = db.crTime;
}

void CDBEntity::setDBName(CString db_name)
{
	m_strName = db_name;
	
}

void CDBEntity::setDBFilePath(CString db_filepath)
{
	m_strFilePath = db_filepath;
}

void CDBEntity::setDBCreationTime(SYSTEMTIME db_ctime)
{
	m_tCrTime = db_ctime;
}

void CDBEntity::setDBType(bool db_type)
{
	m_bType = db_type;
}

CString CDBEntity::getDBName()
{
	return m_strName;
}

CString CDBEntity::getDBFilePath()
{
	return m_strFilePath;
}

bool CDBEntity::getDBType()
{
	return m_bType;
}

SYSTEMTIME CDBEntity::getDBCreationTime()
{
	return m_tCrTime;
}