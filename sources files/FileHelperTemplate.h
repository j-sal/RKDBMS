#pragma once 
class CFileHelperTemplate
{
public:

	CFileHelperTemplate()
	{
	}

	~CFileHelperTemplate()
	{
	}

	template <typename T>
	bool WriteFile(CString filepath, CString fieldName, T value)
	{
		CStdioFile file;
		if (file.Open(filepath, CFile::modeWrite | CFile::typeBinary))
		{
			file.SeekToEnd();
			//file.WriteString(fieldName);
			file.Write(&value, sizeof(T));
			file.Flush();
			return TRUE;
		}
		else
		{
			throw new CAppException(_T("File Operation failed! Record cannot be saved!"));
			return FALSE;
		}
		file.Close();
	}

	/*template <typename T>
	bool RecordExist(const CString filePath, CString fieldName)
	{
		bool res = FALSE;
		CStdioFile file;
		CFileException fileException;
		CString str = L"";
		if (file.Open(filePath, CFile::modeRead | CFile::typeBinary), &fileException)
		{
			int index = 0;
			while (file.ReadString(str))
			{
				
				if (str == fieldName)
				{
					res = TRUE;
					throw new CAppException(_T("Record already exits, select modify record menu to alter!"));
					break;
				}
				file.Seek(sizeof(T)*index, CFile::current);
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
	}*/

};

