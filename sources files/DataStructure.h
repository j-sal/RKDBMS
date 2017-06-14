#pragma once

//#include <datetimeapi.h>
 
typedef int INTEGER;
typedef bool BOOLE;
typedef double DOUBLE;
typedef char VARCHAR[256];
typedef SYSTEMTIME DATETIME;


struct DatabaseBlock
{
	BOOLE type;
	VARCHAR name;
	VARCHAR filepath;
	DATETIME crTime;
};

struct TableBlock
{
	VARCHAR name;
	INTEGER record_num;
	INTEGER field_num;
	VARCHAR tdf;
	VARCHAR trd;
	DATETIME crTime;
	DATETIME mTime;
};

struct FieldBlock
{
	//INTEGER order;
	VARCHAR name;
	//INTEGER type;
	VARCHAR type;
	VARCHAR defaultValue;
	INTEGER param;
	INTEGER integrities;
	DATETIME crTime;
	DATETIME mTime;
};


class CDataStructure
{
public:

	CDataStructure()
	{
	}

	~CDataStructure()
	{
	}
};






