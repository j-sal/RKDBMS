#include "stdafx.h"
#include "RecordLogic.h"
#include "FileHelperTemplate.h"
 

CRecordLogic::CRecordLogic()
{
}


CRecordLogic::~CRecordLogic()
{
}

bool CRecordLogic::IsValidFile(const CString filePath)
{
	bool res = FALSE;
	CStdioFile file;

	if (file.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		res = TRUE;
	}
	else
	{
		return res;
	}

	file.Close();

	return res;
}

bool CRecordLogic::CreateTRDFile(const CString filePath)
{
	bool res;
	CStdioFile file;

	if (file.Open(filePath, CFile::modeCreate | CFile::typeBinary))
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


bool CRecordLogic::insert(CTableEntity &te, CRecordEntity &re)
{
	CString filepath;
	filepath.Format(L"%s.trd", te.getTableName());
	CRecordDao m_daoRecord;
	//CFileHelperTemplate fileHelper;
	bool res = TRUE;
	if (IsValidFile(filepath))
	{
		res = m_daoRecord.insert(te, re);
		/*if (fileHelper.RecordExist(filepath, te.getTableName()))
		{
			res = m_daoRecord.insert(te, re);
		}
		else
		{
			res = FALSE;
		}*/
		
	}
	else
	{
		if (CreateTRDFile(filepath))
		{
			res = m_daoRecord.insert(te, re);
		}
		else
		{
			res = FALSE;
		}
	}
	//int nRecordNum = te.getRecordNum()+1;
	//te.setRecordNum(nRecordNum);

	//CString strTableFile = 
	return res;
	
}

bool CRecordLogic::SelectAll(CTableEntity &te, std::vector<CRecordEntity> &data)
{
	CRecordDao m_daoRec;
	m_daoRec.SelectAll(te, data);
	return TRUE;
}