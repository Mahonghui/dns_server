/*
	breif: answer section implement
	for simple query, there is no need to fill
	authority and additional segments. leave them for future improvment.
*/

#include "answer.h"
#include <iostream>

// constructor and deconstructor
CAnswer::CAnswer():m_RR(){}
CAnswer::~CAnswer(){}

void CAnswer::setAnswerSection(string& name, string& type, string& Class, unsigned int addr)
{
	string addr_str;
	m_RR.setName(name);
	m_RR.setType(type);
	m_RR.setClass(Class);

	// set fixed value
	m_RR.setTTL(0);
	m_RR.setRdLength(4);
	// transform to str, interim byte
	addr_str = (addr>>24) & 0xff;
	addr_str += (addr >> 16) & 0xff;
	addr_str += (addr >> 8) & 0xff;
	addr_str += addr & 0xff;

	m_RR.setRData(addr_str);
}

string& CAnswer::getAnswerSection()
{
	// format answer returned to upper level
	m_RRString.erase(0, m_RRString.size());
	m_RRString = m_RR.getName();
	m_RRString += m_RR.getType();
	m_RRString += m_RR.getClass();
	m_RRString += m_RR.getTTL();
	m_RRString += m_RR.getRdLength();
	m_RRString += m_RR.getRData();

	return m_RRString;
}



// TRIVAL INIT WORK
CAuthority::CAuthority():m_Name(){}
CAuthority::~CAuthority(){}

CAdditional::CAdditional():m_Name(){}
CAdditional::~CAdditional(){}
