#include "stdafx.h"
#include "FieldEntity.h"

 
CFieldEntity::CFieldEntity()
{
	GetSystemTime(&m_tCrTime);
	GetSystemTime(&m_tMTime);
}


CFieldEntity::~CFieldEntity()
{
}

CFieldEntity::CFieldEntity(CString f_name, CString f_type, int f_integrities)
{
	m_strName = f_name;
	m_nType = f_type;
	//m_nParam = f_param;
	m_nIntegrities = f_integrities;
	GetSystemTime(&m_tCrTime);
	GetSystemTime(&m_tMTime);
}

CFieldEntity::CFieldEntity(const CFieldEntity &fe)
{
	m_strName = fe.m_strName;
	m_nType = fe.m_nType;
	m_nParam = fe.m_nParam;
	m_nIntegrities = fe.m_nIntegrities;
	m_tMTime = fe.m_tMTime;
	m_tCrTime = fe.m_tCrTime;
	defaultValue = fe.defaultValue;
}

CFieldEntity::CFieldEntity(FieldBlock &fb)
{
	m_strName = CCharHelper::VarcharToCString(fb.name);
	m_nType = CCharHelper::VarcharToCString(fb.type);
	defaultValue = CCharHelper::VarcharToCString(fb.defaultValue);
	m_nIntegrities = fb.integrities;
	m_tCrTime = fb.crTime;
}

void CFieldEntity::setFieldName(CString f_name)
{
	m_strName = f_name;
}

void CFieldEntity::setFieldParam(int f_param)
{
	m_nParam = f_param;
}

void CFieldEntity::setDefaultValue(CString default)
{
	defaultValue = default;
}

void CFieldEntity::setFieldMTime(SYSTEMTIME f_mtime)
{
	m_tMTime = f_mtime;
}

void CFieldEntity::setFieldCreationTime(SYSTEMTIME f_crtime)
{
	m_tCrTime = f_crtime;
}

void CFieldEntity::setFieldType(CString f_type)
{
	m_nType = f_type;
}

void CFieldEntity::setFieldIntegrities(int f_integrities)
{
	m_nIntegrities = f_integrities;
}

CString CFieldEntity::getFieldName()
{
	return m_strName;
}

int CFieldEntity::getFieldParam()
{
	return m_nParam;
}

CString CFieldEntity::getFieldType()
{
	return m_nType;
}

CString CFieldEntity::getDefaultValue()
{
	return defaultValue;
}

int CFieldEntity::getFieldIntegrities()
{
	return m_nIntegrities;
}

SYSTEMTIME CFieldEntity::getFieldMTime()
{
	return m_tMTime;
}

SYSTEMTIME CFieldEntity::getFieldCreationTime()
{
	return m_tCrTime;
}