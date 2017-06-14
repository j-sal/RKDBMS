#include "stdafx.h"
#include "FileHelper.h"
#include "CharHelper.h"


CFileHelper::CFileHelper()
{
}


CFileHelper::~CFileHelper()
{
}

bool CFileHelper::WriteFile(CString filepath, CDBEntity &db)
{
	CStdioFile file;
	DatabaseBlock dbEntry;


	CCharHelper::CStringToVarchar(db.getDBName(),dbEntry.name);
	CCharHelper::CStringToVarchar(db.getDBFilePath(), dbEntry.filepath);
	dbEntry.type = db.getDBType();
	dbEntry.crTime = db.getDBCreationTime();


	if (file.Open(filepath, CFile::modeWrite | CFile::typeBinary))
	{
		file.SeekToEnd();
		file.Write(&dbEntry,sizeof(DatabaseBlock));
		file.Flush();
		return TRUE;
	}
	else
	{
		throw new CAppException(_T("File Operation failed! Database information cannot be saved!"));
		return FALSE;
	}
	file.Close();

}

void CFileHelper::MoveToDBDirectory(CString dirname)
{
	int dirStatus = _wmkdir(dirname);
	int status = _wchdir(dirname);
}



bool CFileHelper::WriteFile(CString filepath, CTableEntity &te)
{
	CStdioFile file;
	TableBlock tbEntry;

	CCharHelper::CStringToVarchar(te.getTableName(), tbEntry.name);
	CCharHelper::CStringToVarchar(te.getTdfPath(), tbEntry.tdf);
	CCharHelper::CStringToVarchar(te.getTrdPath(), tbEntry.trd);
	tbEntry.field_num = te.getFieldNum();
	//tbEntry.record_num = te.getRecordNum();
	tbEntry.crTime = te.getTableCreationTime();
	tbEntry.mTime = te.getTableMTime();

	if (file.Open(filepath, CFile::modeWrite | CFile::typeBinary))
	{
		file.SeekToEnd();
		file.Write(&tbEntry, sizeof(TableBlock));
		file.Flush();
		return TRUE;
	}
	else
	{
		throw new CAppException(_T("File Operation failed! Table information cannot be saved!"));
		return FALSE;
	}
	file.Close();

}

bool CFileHelper::WriteFile(CString filepath, CFieldEntity &fe)
{
	CStdioFile file;
	FieldBlock fbEntry;

	CCharHelper::CStringToVarchar(fe.getFieldName(), fbEntry.name);
	CCharHelper::CStringToVarchar(fe.getFieldType(), fbEntry.type);
	CCharHelper::CStringToVarchar(fe.getDefaultValue(), fbEntry.defaultValue);
	//fbEntry.type = fe.getFieldType();
	//fbEntry.param = fe.getFieldParam();
	fbEntry.integrities = fe.getFieldIntegrities();
	fbEntry.mTime = fe.getFieldMTime();
	fbEntry.crTime = fe.getFieldCreationTime();

	if (file.Open(filepath, CFile::modeWrite | CFile::typeBinary))
	{
		file.SeekToEnd();
		file.Write(&fbEntry, sizeof(FieldBlock));
		file.Flush();
		return TRUE;
	}
	else
	{
		throw new CAppException(_T("File Operation failed! Field information cannot be saved!"));
		return FALSE;
	}
	file.Close();

}

