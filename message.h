/*
	brief: dns message section
	combine components as final message

	message format can be divided into 5 sections, 
	some of which can be empty.
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
    last two segments remained for future improvement.
*/
using namespace std;

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "header.h"
#include "question.h"
#include "answer.h"
#include "log.h"

class CMessage
{
public:
	CMessage(CLog& log);
	~CMessage();

	bool setHeader(string& header);
	void getHeader(string& header);

	bool setQuestion(string& question, unsigned int len);


	// return hostname
	string& getHost();

	// set answer seciton with address found
	bool setAnswer(long unsigned addr);

	string& getAnswer();

	string& getAuthority();

	string& getAdditional();


private:
	void setErrorCode(unsigned char code);

	CHeader		m_header;
	CQuestion	m_question;
	CAnswer		m_answer;
	CAuthority	m_authority;
	CAdditional	m_addtional;

	string		host;
	string		m_answerString;
	string 		m_authorityString;
	string 		m_addtionalString;
	CLog&		m_log;	
};
#endif

