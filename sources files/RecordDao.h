#pragma once
#include "TableEntity.h"
#include "RecordEntity.h"
#include "FileHelper.h"
#include <vector>
 
class CRecordDao
{
public:
	CRecordDao();
	~CRecordDao();
	bool insert(CTableEntity &te, CRecordEntity &re);
	bool Read(CFile &file, CTableEntity &te, CRecordEntity &re);
	int SelectAll(CTableEntity &te, std::vector<CRecordEntity>&data);
};

