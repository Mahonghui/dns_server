/*
	brief: dns database
*/



#ifndef _DNSDB_H
#define _DNSDB_H

#include <cstring>
#include <map>
using namespace std;
/*
	class CDnsDB reads a files that contains pairs of hostname-ip entries.
	if not specified via command line parameter, it will use default.
	this class returns corresponding ip address when receving look-up queries, 
	returning default value 0 if not found.
*/

class CDnsDB
{
public:
	CDnsDB();
	~CDnsDB();
	
	// read file that stores hostname-ip entries
	// if not specified, default to file hosts
	bool readfile(const char* file);

	// according to hostname, find ip address in long format 
	// compatible to s_addr field in inet structure.
	// if not found, return 0
	unsigned long int getAddress(const char* hostname);

private:
	// comparision method
	class less_string
	{
	public:
		bool operator()(const char* s1, const char* s2) const
		{
			return strcmp(s1, s2)<0;
		}
	};
	// parse line within file
	void parseLine(char* line);

	std::map<const char*, unsigned long int, less_string> m_db;
};
#endif