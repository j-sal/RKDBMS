#include "stdafx.h"
#include "CharHelper.h"
#include <stdlib.h>



CCharHelper::CCharHelper()
{
}


CCharHelper::~CCharHelper()
{
}

CString CCharHelper::VarcharToCString(VARCHAR txt)
{
	CString newStr(txt);
	return newStr;
}

void CCharHelper::CStringToVarchar(CString str, VARCHAR txt)
{

	CStringA StrA(str); // use an intermediate CStringA
	char* Text = StrA.GetBuffer(256);
	// do something with Text here
	strcpy_s(txt,255, Text);
	
	StrA.ReleaseBuffer();

}

int CCharHelper::CStringToInteger(CString str)
{
	int i = _ttoi(str);
	return i;
}

DOUBLE CCharHelper::CStringToDouble(CString str)
{
	double d = _wtof(str);
	return d;
}

BOOL CCharHelper::CStringToBOOL(CString str)
{
	if (str.MakeLower() == "true" || str.MakeLower() == "t" || str == "0")
	{
		return TRUE;
	}
	else if (str.MakeLower() == "false" || str.MakeLower() == "f" || str == "1")
	{
		return FALSE;
	}
}

DATETIME CCharHelper::CStringToDATETIME(CString str)
{
		SYSTEMTIME systime;
		char* dateTimeString = new char[256];
		CStringToVarchar(str, dateTimeString);
		memset(&systime, 0, sizeof(systime));
		// Date string should be "yyyy-MM-dd hh:mm"
		sscanf_s(dateTimeString, "%u-%u-%u ",
											&systime.wYear, 
											&systime.wMonth, 
											&systime.wDay);

		/*&systime.wDayOfWeek,
			&systime.wHour,
			&systime.wMinute,
			&systime.wSecond,
			&systime.wMilliseconds*/

		//%d %d:%d : %d : %d
		return systime;
	

}
