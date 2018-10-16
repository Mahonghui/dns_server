/*
  brief:  dns database implement 
*/
*/

#include "dnsDb.h"

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <cstring>

// Constructor&deconstructor
CDnsDb::CDnsDB()
  : m_db(){}

CDnsDb::~CDnsDB(){}

// Reads the config file given as parameter. 
bool CDnsDB::readfile(const char* filename) 
{
  bool error = false;

  char buff[128];
  ifstream fs(filename, ios::in | ios::binary);
  
  if (fs) {
    while(!fs.eof())
    {
      fs.getline(reinterpret_cast<char *>(&buff),128); 
      parseLine(buff);    
    }
    fs.close();
  }
  else {
    error = true;
  }
  return error;
}


/*!If the hostname is found in the database, the IP address
   in long format (compatible to the s_addr field of the 
   in_addr structure) is returned. If the address has not been
   found a 0 is returned.
 */
unsigned long int CDnsDB::getAddress(const char* name) 
{
  map<const char*,unsigned long int,less_string>::iterator it=m_db.find(name);

  if(it==m_db.end()) {

    return 0;
  } else {
    return (*it).second;
  }
}

/*! Parses a line within the file
 */
void CDnsDB::parseLine(char* buffer) 
{
  string strAux(buffer);
  unsigned char ind_beg,ind_end;
  string address,*name;
  bool found=false;
  struct in_addr inp;
  
  while(!found){
    address.erase();
    // skip all possible spaces , ind_beg points to the first element
    ind_beg=strAux.find_first_not_of(" ",ind_end);
    // from the first element, looking for the next space

    if(ind_beg==ind_end) {
      // blank line
      return;
    }
    address.append(strAux.substr(ind_beg,ind_end-ind_beg));
    if(address[0]=='#') {
      // comment line
      return;
    }
   
    if(inet_aton(address.data(),&inp)) {
      found=true;
    }
  } 

  // Now the the IP address has been found and I'm keeping the hostname
  // there is only one name for each IP address
  ind_beg=strAux.find_first_not_of(" ",ind_end+1);
  ind_end=strAux.find_first_of(" ",ind_beg);
  name=new string(strAux.substr(ind_beg,ind_end-ind_beg));
  m_db[name->c_str()]=inp.s_addr;
}
