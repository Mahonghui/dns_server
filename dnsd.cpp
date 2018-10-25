

#include "dns.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
using namespace std;
int main(int argc, char** args)
{
	string logfile;
	if(argc == 3)
	{
		if(strcmp((char*)args[1], "-f") == 0)
		{
			string lf((char*)args[2]);
			logfile = lf;
		}
		else
		{
			cerr<<"Usage: -f <log_file>"<<endl;
			exit(0);
		}
	}
	else
		if(argc == 1)
		{
			// default log file
			string lf("/var/log/dnslog.txt");
			logfile = lf;
		}
		else
		{
			cerr<<"Usage: -f <log_file>"<<endl;
			exit(0);
		}

	CDns* dns = new CDns((char*)logfile.c_str());
	dns->openCommunication();
	while(1)
	{
		dns->readMessage();
	}
	return 0;
}
