using namespace std;

/*

	brief: dns resources record
*/

#ifndef _RR_H
#define _RR_H

#include <string>

class CResourceRecord
{
public:
	CResourceRecord();
	~CResourceRecord();
	
	void setName(string& Name);
	string& getName();

	void setType(string& Type);
	string& getType();

	void setClass(string& Class);
	string& getClass();

	void setTTL(unsigned int ttl);
	unsigned int getTTL();

	void setRdLength(unsigned int Rdlength);
	unsigned int getRdLength();

	void setRData(string& rddata);
	string& getRData();

	enum TQType
	{
		A	= 1,
		NS  = 2,
		MD  = 3,
		MF  = 4,
		CNAME = 5,
		SOA  = 6,
		MB  = 7,
		MG  = 8,
		NLL = 10，
		WKS = 11,
		PTR = 12,
		HINFO = 13,
		MINFO = 14,
		MX  = 15,
		TXT = 16,
		AXFR = 252,
		MAILB = 253,
		MAILB = 254,
		ALL  = 255
	};

	enum TQClass
	{
		IN = 1,
		CH = 3,
		ANY = 255
		
	};
private:
	string m_Name;
	string m_Type;
	string m_Class;
	string m_TTL;
	string m_RdLength;
	string m_RData;
};
#endif
