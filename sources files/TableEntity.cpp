#include "stdafx.h"
#include "TableEntity.h"

 
CTableEntity::CTableEntity()
{
}


CTableEntity::~CTableEntity()
{
}

CTableEntity::CTableEntity(CString tb_name)
{
	m_strName = tb_name;
	m_nFieldNum = 0;
	m_nRecordNum = 0;
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	m_strTdfPath.Format(_T("%s\\%s.tdf"), currentDir, tb_name);//set table definition file path
	m_strTrdPath.Format(_T("%s\\%s.trd"), currentDir, tb_name);//set record file path;
	m_strTicPath.Format(_T("%s\\%s.tic"), currentDir, tb_name);//set integrity description file path;
	m_strTidPath.Format(_T("%s\\%s.tid"), currentDir, tb_name);//set index description file path;
	
	GetSystemTime(&m_tCrTime);//set creation time
	GetSystemTime(&m_tMTime);//set last modification time to creation time

	fieldArray.clear();
}

CTableEntity::CTableEntity(TableBlock &tb)
{
	m_strName = CCharHelper::VarcharToCString(tb.name);
	m_strTdfPath = CCharHelper::VarcharToCString(tb.tdf);
	m_strTrdPath = CCharHelper::VarcharToCString(tb.trd);
	m_tCrTime = tb.crTime;
	m_tMTime = tb.mTime;
}

CString CTableEntity::getTableName()
{
	return m_strName;
}


int CTableEntity::getFieldNum()
{
	return m_nFieldNum;
}

int CTableEntity::getRecordNum()
{
	return m_nRecordNum;
}

CString CTableEntity::getTdfPath()
{
	return m_strTdfPath;
}
CString CTableEntity::getTrdPath()
{
	return m_strTrdPath;
}
CString CTableEntity::getTicPath()
{
	return m_strTicPath;
}
CString CTableEntity::getTidPath()
{
	return m_strTidPath;
}
SYSTEMTIME CTableEntity::getTableCreationTime()
{
	return m_tCrTime;
}
SYSTEMTIME CTableEntity::getTableMTime()
{
	return m_tMTime;
}

void CTableEntity::setTableName(CString tb_name)
{
	m_strName = tb_name;
}

void CTableEntity::setFieldNum(int field_num)
{
	m_nFieldNum = field_num;
}
void CTableEntity::setRecordNum(int rec_num)
{
	m_nRecordNum = rec_num;
}

void CTableEntity::setTdfPath(CString tb_tdfPath)
{
	m_strTdfPath = tb_tdfPath;
}
void CTableEntity::setTrdPath(CString tb_trdPath)
{
	m_strTrdPath = tb_trdPath;
}
void CTableEntity::setTicPath(CString tb_ticPath)
{
	m_strTicPath = tb_ticPath;
}
void CTableEntity::setTidPath(CString tb_tidPath)
{
	m_strTidPath = tb_tidPath;
}
void CTableEntity::setTableCreationTime(SYSTEMTIME tb_ctime)
{
	m_tCrTime = tb_ctime;
}
void CTableEntity::setTableMTime(SYSTEMTIME tb_mtime)
{
	m_tMTime = tb_mtime;
}

void CTableEntity::AddField(CFieldEntity &fe)
{
	/*
	FieldArray *temp;             //create a temporary node 
	temp = (FieldArray*)malloc(sizeof(FieldArray)); //allocate space for node 
	temp->fe = &fe;             // store data(first field)
	temp->nextField = m_arrField;  // store the address of the pointer header(second field)
	m_arrField = temp;                  // transfer the address of 'temp' to header	
	*/
	
}

