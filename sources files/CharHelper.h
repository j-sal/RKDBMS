#pragma once
#include "DataStructure.h"
class CCharHelper
{
public:
	CCharHelper();
	~CCharHelper();
	static CString VarcharToCString(VARCHAR);
	static void CStringToVarchar(CString, VARCHAR);
	static DATETIME CStringToDATETIME(CString);
	static int CStringToInteger(CString);
	static DOUBLE CStringToDouble(CString);
	static BOOL CStringToBOOL(CString);
};

