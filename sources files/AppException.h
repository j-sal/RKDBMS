#pragma once
class CAppException
{
private:
	CString m_strError;		//Exception message
	int m_nCode;			//Exception code
public:
	CAppException();
	CAppException(CString strError);
	~CAppException();
	CString getErrorMessage();
};

