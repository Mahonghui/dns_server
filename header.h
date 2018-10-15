using namespace std;


/*
	brief: dns header definition

	 The header section format is the following one:
*
*      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                      ID                       |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    QDCOUNT                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    ANCOUNT                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    NSCOUNT                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    ARCOUNT                    |

*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
#ifndef _HEADER_H
#define _HEADER_H

#include <string>

class CHeader
{
public:
	CHeader();
	~CHeader();

	enum TRCode
	{
		NO_ERROR,
		FORMAT_ERROR,
		SERVER_FAILURE,
		NAME_ERROR,
		NOT_IMPLEMENTED,
		REFUSED
	};

	TRCode setOpCodePart(unsigned char c);
	unsigned char getOpCodePart();

	void setRCode(unsigned char c);
	unsigned char getRCode();

	TRCode setAllCounts(string& buffer);
	string& getAllCounts();

	void setAnCount(unsigned int ancount);

private:
	unsigned char m_OpCodePart; // 0-standard query; 1-inverse query; 2-server status query
	TRCode m_RCode; // TRCode, [1, 5] range maps to TRCode enum structure;
	unsigned int m_QdCount; // entries in Question part
	unsigned int m_AnCount; // resource resource in Answer part
	unsigned int m_NsCount; // name server resource in authority part
	unsigned int m_ArCount; // resource record in Addtional part
	string m_AllCounts;

};
#endif

