/*
	brief: dns log info
	print log info generated by other classes to a log file
	which can be specified by a parameter, or a default option
	would be used.
*/
using namespace std;

#ifndef _LOG_H
#define _LOG_H

#include "header.h"
#include<string>
#include<fstream>

class CLog
{
public:
	CLog(char* logFile);
	~CLog();

	// print a string into logfile
	void printString(string outString);

	// print a formatted string into logfile
	void printFormattedString(string& outString);

	// print error info into logfile
	void printError(string outString, CHeader::TRCode error_code);

private:
	ofstream m_Fs; // log file object
};
#endif