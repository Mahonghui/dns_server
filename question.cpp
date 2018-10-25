/*
	brief: dns question section implement

*/

#include "question.h"
#include <iostream>

// constructor & deconstructor
CQuestion::CQuestion():m_QName(),m_QType(), m_QClass(){}
CQuestion::~CQuestion(){}

void CQuestion::setQName(string& name)
{
	m_QName.erase(0, m_QName.size());
	m_QName = name;
}

string& CQuestion::getQName()
{
	return m_QName;
}

bool CQuestion::setQType(string& type)
{
	unsigned int value;
	bool error = false;

	m_QType.erase(0, m_QType.size());
	m_QType = type;

	value = (type[0]<<8) + type[1];
	switch((CResourceRecord::TQType)value)
	{
		case(CResourceRecord::A):
		case(CResourceRecord::ALL):
		// valid 
		break;

		default:
		// not implemented
		error = true;
		break;
	}
	return error;
}

string& CQuestion::getQType()
{
	return m_QType;
}

bool CQuestion::setQClass(string& Class)
{
	unsigned int value;
	bool error = false;
	m_QClass.erase(0, m_QClass.size());
	m_QClass = Class;

	value = (Class[0]<<8) + Class[1];
	// accept A || ANY
	error = ((CResourceRecord::TQClass)value == CResourceRecord::CH);
	return error;
}

string& CQuestion::getQClass()
{
	return m_QClass;
}
