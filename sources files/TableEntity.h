#pragma once

#include "FieldEntity.h"
#include <vector>
//#include <datetimeapi.h>
 
class CTableEntity
{
private:
	CString m_strName;
	int m_nFieldNum;
	int m_nRecordNum;
	CString m_strTdfPath;
	CString m_strTrdPath;
	CString m_strTicPath;
	CString m_strTidPath;
	SYSTEMTIME m_tCrTime;
	SYSTEMTIME m_tMTime;
public:
	std::vector <CFieldEntity> fieldArray;//array of fields in a table
	CTableEntity();
	CTableEntity(CString tb_name);
	CTableEntity(TableBlock &tb);
	~CTableEntity();
	CString getTableName();
	int getFieldNum();
	int getRecordNum(); 
	CString getTdfPath(); 
	CString getTrdPath(); 
	CString getTicPath(); 
	CString getTidPath(); 
	SYSTEMTIME getTableCreationTime();
	SYSTEMTIME getTableMTime();
	void setTableName(CString tb_name);
	void setRecordNum(int rec_num);
	void setFieldNum(int field_num);
	void setTdfPath(CString tb_tdfPath);
	void setTrdPath(CString tb_trdPath);
	void setTicPath(CString tb_ticPath);
	void setTidPath(CString tb_tidPath);
	void setTableCreationTime(SYSTEMTIME tb_ctime);
	void setTableMTime(SYSTEMTIME tb_mtime);

	void AddField(CFieldEntity&);
	CFieldEntity* getField(CString);
	//FieldArray* getHeader();

	/*
	CTableEntity& operator=(const CTableEntity &te)  // assignment operator
	{
		m_strName = te.m_strName;
		//int m_nFieldNum;
		//int m_nRecordNum;
		 m_strTdfPath = te.m_strTdfPath;
		m_strTrdPath = te.m_strTrdPath;
		m_strTicPath = te.m_strTicPath;
		m_strTidPath = te.m_strTidPath;
		//SYSTEMTIME m_tCrTime;
		//SYSTEMTIME m_tMTime;
		m_arrField = te.m_arrField;//header of field array linked list
		return *this;
	}
	*/
};


