#include "stdafx.h"
#include "TableDao.h"
#include "CharHelper.h"

 
CTableDao::CTableDao()
{
}


CTableDao::~CTableDao()
{
}

bool CTableDao::TbExist(const CString filePath, CTableEntity te)
{
	bool res = FALSE;
	CStdioFile file;
	CFileException fileException;
	if (file.Open(filePath, CFile::modeRead | CFile::typeBinary),&fileException)
	{
		TableBlock *tbInfo = NULL;
		tbInfo = (TableBlock*)malloc(sizeof(TableBlock));
		while (file.Read(tbInfo, sizeof(TableBlock)))
		{
			CString str = L"";
			str = CCharHelper::VarcharToCString(tbInfo->name);

			if (str == te.getTableName())
			{
				res = TRUE;
				throw new CAppException(_T("table already exists!"));
				break;
			}
		}
	}
	else
	{
		CString strErrorMsg;
		strErrorMsg.Format(_T("Can't open file %s , error : %u"), filePath, fileException.m_cause);
		throw new CAppException(strErrorMsg);
	}
	file.Close();

	return res;
}


bool CTableDao::IsValidFile(const CString filePath)
{
	bool res;
	CStdioFile file;

	if (file.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		res = TRUE;
	}
	else
	{
		res = FALSE;
		return res;
	}

	file.Close();

	return res;
}

bool CTableDao::CreateTbFile(const CString fileName)
{
	bool res;
	CStdioFile file;

	if (file.Open(fileName, CFile::modeCreate | CFile::typeBinary))
	{
		res = TRUE;
	}
	else
	{
		res = FALSE;
	}

	file.Close();

	return res;
}

bool CTableDao::Create(const CString filepath, CTableEntity &te)
{
	
		return CFileHelper::WriteFile(filepath, te);

}

bool CTableDao::AddField(const CString filepath, CFieldEntity &fe)
{

	return CFileHelper::WriteFile(filepath, fe);

}


bool CTableDao::GetFields(const CString filePath, CTableEntity& te)
{
	
	bool res = FALSE;
	CStdioFile file;

	if (!(res = IsValidFile(filePath)))
	{
		AfxMessageBox(L"Table with no fields, Add some fields!");
		return res;
	}

	if (file.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		FieldBlock *fbInfo = NULL;
		int index = 0;
		fbInfo = (FieldBlock*)malloc(sizeof(FieldBlock));
		while (file.Read(fbInfo, sizeof(FieldBlock)))
		{
			index++;
			CFieldEntity fEntity(*fbInfo);
			te.fieldArray.push_back(fEntity);
			file.Seek(sizeof(FieldBlock)*index, CFile::begin);
			res = TRUE;
		}

	}
	else
	{
		throw new CAppException(_T("File Operation failed! Fields information cannot be read!"));
	}
	file.Close();

	return res;
}



int CTableDao::GetTables(const CString filePath, std::vector<CTableEntity>& tbArray)
{
	CStdioFile file;
	int index = 0;
	if (!IsValidFile(filePath))
	{
		AfxMessageBox(L"The selected database has no tables, Add some tables!");
		return 0;
	} 
	if (file.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		TableBlock *tbInfo = NULL;
		tbInfo = (TableBlock*)malloc(sizeof(TableBlock));
		while (file.Read(tbInfo, sizeof(TableBlock)))
		{
			CTableEntity tbEntity(*tbInfo);
			tbArray.push_back(tbEntity);
			int res = GetFields(tbEntity.getTdfPath(), tbArray.at(index));
			++index;
			file.Seek(sizeof(TableBlock)*index, CFile::begin);
		}

	}
	else
	{
		throw new CAppException(_T("File Operation failed! Tables information cannot be read!"));
	}
	file.Close();
	return index;
}