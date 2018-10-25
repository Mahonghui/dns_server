/*
	brief: resource records implement
*/

#include "rr.h"
#include <iostream>

// Constructor
CResourceRecord::CResourceRecord():m_Name(), m_Class(), m_Type(), 
									m_TTL(),m_RdLength(), m_RData()
{}
// Deconstructor
CResourceRecord::~CResourceRecord()
{}

void CResourceRecord::setName(string& name)
{
	m_Name.erase(0, m_Name.size());
	m_Name = name;
}

string& CResourceRecord::getName()
{
	return m_Name;
}

void CResourceRecord::setType(string& type)
{
	m_Type = type;
}

string& CResourceRecord::getType()
{
	return m_Type;
}

void CResourceRecord::setClass(string& Class)
{
	m_Class = Class;
}

string& CResourceRecord::getClass()
{
	return m_Class;
}

void CResourceRecord::setTTL(unsigned int ttl)
{
	m_TTL = (ttl >> 24) & 0xff;
	m_TTL += (ttl>>16) & 0xff;
	m_TTL += (ttl>>8) & 0xff;
	m_TTL += ttl & 0xff;
}

string& CResourceRecord::getTTL()
{
	return m_TTL;
}

void CResourceRecord::setRdLength(unsigned int length)
{
	m_RdLength = (length >> 8) & 0xff;
	m_RdLength += length & 0xff;
}

string& CResourceRecord::getRdLength()
{
	return m_RdLength;
}

void CResourceRecord::setRData(string& data)
{
	m_RData = data;
}

string& CResourceRecord::getRData()
{
	return m_RData;
}
