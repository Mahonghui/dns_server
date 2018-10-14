/*
	brief: dns header implement
*/

#include "header.h"
#include <iostream>


// Constructor
CHeader::CHeader(): m_OpCodePart(0),m_RCode(NO_ERROR), 
					m_QdCount(0), m_AnCount(0),m_NsCount(0), 
					m_ArCount(0), m_AllCounts()
{
}

// Deconstructor

CHeader:~CHeader()
{

}

CHeader::TRCode CHeader::setOpCodePart(unsigned char c)
{
	unsigned int qr;
	unsigned int op_code;
	unsigned int tc;

	m_OpCodePart = c;

	qr = (c>>7)& 0x01; // extract QR bit
	op_code = (c>>3 & 0x0f); //extract Opcode bits
	tc = (c>>1) & 0x01;

	if(qr == 1)return FORMAT_ERROR;
	else
		qr = 0x01;

	// only receive standard query
	if(tc != 0)return NOT_IMPLEMENTED;

	return NO_ERROR;
}

unsigned char CHeader::getOpCodePart()
{
	// set qr=1
	m_OpCodePart = ((1<<7) + m_OpCodePart);
	return m_OpCodePart;
}

void CHeader::setRCode(unsigned char c)
{
	m_RCode = (TRCode)c;
}

unsigned char CHeader::getRCode()
{
	return (char)m_RCode;
}

CHeader::TRCode setAllCounts(string& buff)
{
	m_AllCounts = buff;

	m_QdCount = (buff[0]<<8) + buff[1];

	if(m_QdCount == 0)
		return FORMAT_ERROR;
	if(m_QdCount > 1)
		return NOT_IMPLEMENTED;

	return NO_ERROR;
}

string& CHeader::getAllCounts()
{
	m_NsCount = 0;
	m_ArCount = 0;

	m_AllCounts[2] = (m_AnCount>>8) & 0xff;
	m_AllCounts[3] = m_AnCount & 0xff;
	m_AllCounts[4] = (m_NsCount>>8) & 0xff;
	m_AllCounts[5] = m_NsCount & 0xff;
	m_AllCounts[6] = (m_ArCount>>8) & 0xff;
	m_AllCounts[7] = m_ArCount & 0xff;

	return m_AllCounts;
}

void CHeader::setAnCount(unsigned int anCount)
{
	m_AnCount = anCount;
}

}

