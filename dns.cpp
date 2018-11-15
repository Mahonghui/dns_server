/*
	brief: dns section implement
*/

#include "dns.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

// constructor & deconstructor
CDns::CDns(const char* filename)
	:m_socket(0),
	m_clientaddr(),
	m_error(false),
	m_log(filename),
	m_db()
	{}

CDns::~CDns(){}

void CDns::openCommunication()
{
	struct sockaddr_in server_address;
	int length;

	// create a socket
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_socket < 0)
	{
		cerr<<"Fail to open socket"<<endl;
		exit(0);
	}

	// turn on reuse of socket
	int op = 1;
	setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));

	// initialize address
	length = sizeof(server_address);
	memset(&server_address, 0, length);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(DNS_PORT);

	if(bind(m_socket, (struct sockaddr*)&server_address, length)<0)
	{
		cerr<<"Error binding socket"<<endl;
		exit(0);
	}


	bool error = m_db.readfile("hosts");
	if(error)
	{
		cerr<<"Error reading <hosts> file. File does not exist! "<<endl;
		exit(0);
	}

	m_log.printString("Starting Name Server ...");
}

void CDns::readMessage()
{
	socklen_t len = sizeof(struct sockaddr_in);
	int n;
	int buff[1024];

	// receive message
	n = recvfrom(m_socket, (void*)buff, 1024, 0, (struct sockaddr*)&m_clientaddr,&len);
	if(n<0)
	{
		cerr<<"Error receiving from "<<m_socket<<" socket"<<endl;
		exit(0);
	}
	string received_msg((const char*)&buff, n);
	parseMessage(received_msg, (unsigned int) n);
}

void CDns::parseMessage(string& msg, unsigned int n)
{
	m_message = new CMessage(m_log);
	m_error = false;

	ostringstream s;
	s<<DNS_PORT;
	m_log.printString("Message receive from port: "+ s.str() + ". ");//s.str returns C-style string
	m_log.printString("message: ");
	m_log.printFormattedString(msg);

	string header(msg, 0, HEADER_SIZE);
	m_error = m_message->setHeader(header);
	if(m_error)
	{
		m_log.printString("Error parsing message");

		buildMessage(msg);
		return;
	}
	hostLookup(msg);

} 

void CDns::hostLookup(string& msg)
{
	struct in_addr addr;
	unsigned long saddr;
	string hostname;

	hostname = m_message->getHost();
	addr.s_addr = m_db.getAddress((const char*)hostname.c_str());
	saddr = htonl(addr.s_addr);

	m_error = m_message->setAnswer(saddr);
	if(m_error)
	{
		m_log.printString("hostlookup: no ip found");
	}

	buildMessage(msg);
}

void CDns::buildMessage(string& msg)
{
	m_message->getHeader(msg);

	if(!m_error)
	{
		msg += m_message->getAnswer();
		msg += m_message->getAuthority();
		msg += m_message->getAdditional();	
	}
	sendMessage(msg);
}

void CDns::sendMessage(string& msg)
{
	int r;
	socklen_t len = sizeof(struct sockaddr_in);

	r = sendto(m_socket, msg.c_str(), msg.size(), 0, (struct sockaddr*)&m_clientaddr, len);
	if(r<0)
	{
		cerr<<"Error sending to "<<m_socket<<" socket."<<endl;
		exit(0);
	}
	
}
