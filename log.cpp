/*
	brief: dns log section implement
*/

#include "log.h"
#include <iostream>
#include <iomanip>

// Constructor & Deconstructor
CLog::CLog(const char* logFile):m_Fs(logFile, ios::out|ios::binary){}
CLog::~CLog(){}

void CLog::printString(string outString)
{
	m_Fs<<outString<<endl;
}

void CLog::printFormattedString(string& outString)
{
	// stack overflow
	char s[3];

	for(unsigned int i = 0; i<outString.size(); i++)
	{
		sprintf(s, "%.2x", (unsigned char)outString[i]);
		m_Fs<<"["<<hex<<s<<"]";
	}
	m_Fs<<dec<<" - "<<outString.size() << " bytes"<<endl;
}

void CLog::printError(string outString, CHeader::TRCode error_code)
{
	string error;

	switch(error_code)
	{
		case CHeader::SERVER_FAILURE:
			error = "SERVER FAILURE";
			break;
		case CHeader::FORMAT_ERROR:
			error = "FORMAT ERROR";
			break;
		case CHeader::REFUSED:
			error = "REFUSED";
			break;
		case CHeader::NOT_IMPLEMENTED:
			error = "NOT IMPLEMENTED";
			break;
		case CHeader::NAME_ERROR:
			error = "NAME ERROR";
			break;
		default:
			error = "NO ERROR";
			break;
	}
	m_Fs<<outString<<error<<endl;
}