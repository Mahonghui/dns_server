/*
	brief: dns question section
	only consider one question
*/

#ifndef _QUESTION_H
#define _QUESTION_H

#include "rr.h"
#include <string>

class CQuestion
{
public:
	CQuestion();
	~CQuestion();
	
	void setQName(string& name);
	sring& getQName();

	bool setQType(string& type);
	string& getQType();

	bool setQClass(string& Class);
	string& getQClass();

private:
	string m_QName;
	string m_QType;
	string m_QClass;
};
#endif