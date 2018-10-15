/*
	brief: dns message section implement
	+---------------------+
    |        Header       |
    +---------------------+
    |       Question      | the question for the name server
    +---------------------+
    |        Answer       | RRs answering the question
    +---------------------+
    |      Authority      | RRs pointing toward an authority
    +---------------------+
    |      Additional     | RRs holding additional information
    +---------------------+

*/

#include "message.h"
#include <iostream>
#include <string>

// constructor & deconstructor
CMessage::CMessage(CLog& log)
			:m_header(),
			m_question(),
			m_answer(),
			m_authority(),
			m_addtional(),
			m_host(),
			m_answerString(),
			m_authorityString(),
			m_addtionalString(),
			m_log(log)
{}
CMessage::~CMessage()

bool CMessage::setHeader(string& header)
{
	unsigned int qd_count;
	bool error = false;
	CHeader::TRCode error_code;

	error_code = m_Header.setOpCodePart(header[2]);
	if(error_code != (CHeader::NO_ERROR))
	{
		m_log.printError("setHeader: error code returned: ", error_code);
		setErrorCode(error_code);
		error = true;
	}
	m_Header.setOpCodePart(Header[3]);

	string params = header.substr(4, 8);
	qd_count = m_Header.setAllCounts(params);

	error_code = m_Header.setOpCodePart(header[2]);
	if(error_code != (CHeader::NO_ERROR))
	{
		m_log.printError("setHeader: error code returned: ", error_code);
		setErrorCode(error_code);
		error = true;
	}

	return error;
}

void CMessage::getHeader(string& header)
{
	string buff;
	buff = m_Header.getOpCodePart();
	buff += m_Header.getRCode();
	buff += m_Header.getAllCounts();

	header.replace(2, 10, buff);
}

bool CMessage::setQuestion(string& question, unsigned int qlen)
{
	unsigned int len=0;
	unsigned int index = 0;
	string qname, qtype, qclass;
	bool error = false;

	index = qname.size()-4;
	qname.erase(0, qname.size());
	qname = question.substr(0, index-1);

	//clean m_host filed
	m_host.erase(0, m_host.size());
	// extract hostname from question name 
	// to look for correspoding ip addr within db
	unsigned int i=0;
	while(i<qname.size())
	{
		len = qname.at(i);
		m_host += qname.substr(i+1, len);
		i += (len+1);
		if(i<qname.size()) m_host += '.';
	}

	// qname terminated with null
	qname.push_back(0);

	m_question.setQName(qname);
	qtype = question.substr(index, 2);
	qclass = question.substr(index, 2);

	error = m_question.setQType(qtype);
	if(error)
	{
		m_log.printError("setQType: error code returned: ", CHeader::NOT_IMPLEMENTED);
		setErrorCode(CHeader::NOT_IMPLEMENTED);
		return error;
	}

	error = m_question.setQClass(qclass);
	if(error)
	{
		m_log.printError("setQClass: error code returned: ", CHeader::NOT_IMPLEMENTED);
		setErrorCode(CHeader::NOT_IMPLEMENTED);
		return error;
	}

	return error;
}

string& CMessage::getHost()
{
	return m_host;
}

bool CMessage::setAnswer(unsigned int addr)
{
	bool error = false;

	if(addr != 0)
	{
		m_header.setAnCount(1); // indicate there is only one answer
		m_answer.setAnswerSection(m_question.getQName(), m_question.getQtype(), m_question.getQClass(), addr);
	}
	else
	{
		// no paired ip address
		m_log.printError("setAnswer: error code returned: ", CHeader::NAME_ERROR);
		setErrorCode(CHeader::NAME_ERROR);
		error = true;
	}
	return error;
}

string& CMessage::getAnswer()
{
	m_answerString = m_answer.getAnswerSection();
	return m_answerString;
}

string& CMessage::getAuthority()
{
	return m_authorityString;
}

string& CMessage::getAdditional()
{
	return m_addtionalString;
}

