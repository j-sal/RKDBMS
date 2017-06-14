#pragma once

#include "DataStructure.h"
#include "CharHelper.h"
 
class CFieldEntity
{
private:
	CString m_strName;
	//int m_nType;
	CString m_nType;
	int m_nParam;
	SYSTEMTIME m_tMTime;
	SYSTEMTIME m_tCrTime;
	int m_nIntegrities;
	CString defaultValue;
public:
	CFieldEntity(const CFieldEntity &fe);
	CFieldEntity(CString, CString, int);
	CFieldEntity(FieldBlock &fb);
	CFieldEntity();
	~CFieldEntity();
	CString getFieldName();
	CString getFieldType();
	CString getDefaultValue();
	int getFieldParam();
	int getFieldIntegrities();
	SYSTEMTIME getFieldMTime();
	SYSTEMTIME getFieldCreationTime();
	void setFieldName(CString f_name);
	void setFieldType(CString f_type);
	void setDefaultValue(CString);
	void setFieldMTime(SYSTEMTIME f_mtime);
	void setFieldCreationTime(SYSTEMTIME f_crtime);
	void setFieldParam(int f_param);
	void setFieldIntegrities(int f_integrity);
	
	/*
	CFieldEntity& operator=(const CFieldEntity &fe)  // assignment operator
	{
		m_strName = fe.m_strName;
		m_nType = fe.m_nType;
		m_nParam = fe.m_nParam;
		m_nIntegrities = fe.m_nIntegrities;
		m_tMTime = fe.m_tMTime;
		defaultValue = fe.defaultValue; 
		return *this;
	}
	*/
};



