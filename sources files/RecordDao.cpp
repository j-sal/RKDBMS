#include "stdafx.h"
#include "RecordDao.h"
#include "FileHelperTemplate.h"
 
CRecordDao::CRecordDao()
{
}


CRecordDao::~CRecordDao()
{
}

bool CRecordDao::insert(CTableEntity &te, CRecordEntity &re)
{
	bool res = TRUE;
	CString filepath;
	filepath.Format(L"%s.trd", te.getTableName());
	CStdioFile file;
	if (file.Open(filepath, CFile::modeNoTruncate|CFile::modeWrite|CFile::typeBinary))
	{
		for (unsigned i = 0; i < te.fieldArray.size(); i++)
		{
			CFieldEntity* pField = &te.fieldArray.at(i);
			CString strFieldName = pField->getFieldName();
			CString strValue = re.Get(strFieldName);
			VARCHAR value;
			INTEGER intValue;
			BOOLEAN boolValue;
			DATETIME tValue;
			
			if (pField->getFieldType() == L"VARCHAR")
			{
				CCharHelper::CStringToVarchar(strValue, value);
				file.SeekToEnd();
				file.Write(&value, sizeof(VARCHAR));
			}
			else if (pField->getFieldType() == L"INTEGER")
			{
				intValue = CCharHelper::CStringToInteger(strValue);
				file.SeekToEnd();
				file.Write(&intValue, sizeof(INTEGER));
			}
			else if (pField->getFieldType() == L"BOOLEAN")
			{
				boolValue = CCharHelper::CStringToBOOL(strValue);
				file.SeekToEnd();
				file.Write(&boolValue, sizeof(BOOLEAN));
			}
			else
			{
				tValue = CCharHelper::CStringToDATETIME(strValue);
				file.SeekToEnd();
				file.Write(&tValue, sizeof(DATETIME));
			}
		}
	}
	else
	{
		res = FALSE;
	}
	file.Close();
	
	return res;
}

bool CRecordDao::Read(CFile &file, CTableEntity &te, CRecordEntity &re)
{
	bool res = FALSE;
	for (unsigned i = 0; i < te.fieldArray.size(); i++)
	{
		CFieldEntity* pField = &te.fieldArray.at(i);
		CString strFieldName = pField->getFieldName();
		CString strValue = re.Get(strFieldName);
		
		CFileHelperTemplate fileHelper;
		if (pField->getFieldType() == L"VARCHAR")
		{
			VARCHAR value;
			if (file.Read(&value, sizeof(VARCHAR)))
			{
				CString str = CCharHelper::VarcharToCString(value);
				re.Put(strFieldName, str);
				res = TRUE;
			}
			else
			{
				res = FALSE;
			}
			
		}
		else if (pField->getFieldType() == L"INTEGER")
		{
			INTEGER intValue;
			if (file.Read(&intValue, sizeof(int)))
			{
				CString str;
				str.Format(L"%d", intValue);
				re.Put(strFieldName, str);
				res = TRUE;
			}
			else
			{
				res = FALSE;
			}
			
		}
		else if (pField->getFieldType() == L"BOOLEAN")
		{
			BOOLEAN boolValue;
			if (file.Read(&boolValue, sizeof(BOOLEAN)))
			{
				CString str;
				if (boolValue)
				{
					str = "TRUE";
				}
				else
				{
					str = "FALSE";
				}
				re.Put(strFieldName, str);
				res = TRUE;
			}
			else
			{
				res = FALSE;
			}
		
		}
		else
		{
			DATETIME tValue;
			if (file.Read(&tValue, sizeof(DATETIME)))
			{
				CString str;
				str.Format(_T("%u-%u-%u"),
					tValue.wYear, tValue.wMonth, tValue.wDay);
				re.Put(strFieldName, str);
				res = TRUE;
			}
			else
			{
				res = FALSE;
			}
			
		}
	}
	return res;
}

int CRecordDao::SelectAll(CTableEntity &te, std::vector<CRecordEntity>&data)
{
	CString filepath;
	filepath.Format(L"%s.trd",te.getTableName());
	CStdioFile file;
	if (file.Open(filepath, CFile::modeRead | CFile::typeBinary))
	{

		while (true)
		{
			CRecordEntity* pRecEntity = new CRecordEntity();
			if (Read(file, te, *pRecEntity)==TRUE)
			{
				data.push_back(*pRecEntity);
			}
			else
			{
				delete pRecEntity;
				break;
			}
		}
	}
	else
	{
		throw new CAppException(_T("File Operation failed! Record information cannot be read!"));
	}
	file.Close();
	return 0;
}