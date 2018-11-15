/*
	brief: define dns server workflow
*/

#ifndef _DNS_H
#define _DNS_H

#include "log.h"
#include "message.h"
#include "dnsDB.cpp"
using namespace std;
class CDns
{
public:
	CDns(const char* filename);
	~CDns();
	
	// open communication
	void openCommunication();

	// read message from client
	void readMessage();

	void parseMessage(string& txMessage, unsigned int mlen);

	// look up ip address in the db
	void hostLookup(string& txMessage);

	void buildMessage(string& txMessage);

	void sendMessage(string& txMessage);

private:
	static const unsigned short DNS_PORT = 53;
	static const unsigned short HEADER_SIZE = 12;

	int		m_socket;
	struct sockaddr_in m_clientaddr;
	bool		m_error;
	CMessage*	m_message;
	CLog		m_log;
	CDnsDB		m_db;
};

#endif