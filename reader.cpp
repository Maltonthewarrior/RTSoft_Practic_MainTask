#include "reader.h"

reader::reader():FILENAME("ip.txt")
{
}

void reader::read_ip(vector<host>& list)
{
	
	ifstream in_stream;
	char ip[16];
	int port;
	in_stream.open(this->FILENAME);
	while(!in_stream.eof())
	{
    		in_stream >> ip >> port;
		host cur(ip, port);
    	 	list.push_back(cur);
	}
	in_stream.close();
}

