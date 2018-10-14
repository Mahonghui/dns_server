/*
	brief： dns answer section
	typically, there should be more than one RRs
	in an answer to one query, but for the time being
	we assume only one answer section responses to a query
*/

#ifndef _ANSWER_H
#define _ANSWER_H

#include "rr.h"

class CAnswer
{
public:
	CAnswer();
	~CAnswer();
	// this method fills most necessary fields. since we often query inet address, so length is fixed to 4
	void setAnswerSection(string& name, string& type, string& Class, unsigned int addr);
	string& getAnswerSection();

private:
	CResourceRecord m_RR; // only one RR currently.
	string m_RRString; // string to be returned to upper level
};


class CAuthority
{
public:
	CAuthority();
	~CAuthority();
private:
	string m_Name;
};

class CAdditional
{
public:
	CAdditional();
	~CAdditional();
private:
	m_Name;
	
};
#endif