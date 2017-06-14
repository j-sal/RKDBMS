#pragma once
#include "RecordDao.h"
 
class CRecordLogic
{
public:
	CRecordLogic();
	~CRecordLogic();
	bool IsValidFile(CString);
	bool CreateTRDFile(CString);
	bool insert(CTableEntity &te, CRecordEntity &re);
	bool SelectAll(CTableEntity &te, std::vector<CRecordEntity> &data);
};

