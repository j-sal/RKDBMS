#include "stdafx.h"
#include "AppException.h"


CAppException::CAppException()
{
	m_strError = _T("");
	m_nCode = 0;
}

CAppException::CAppException(CString strError)
{
	m_strError = strError;
	m_nCode = 0;
}


CAppException::~CAppException()
{
}

CString CAppException::getErrorMessage()
{
	return m_strError;
}
