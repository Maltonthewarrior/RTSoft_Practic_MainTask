#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
//#include <thread>
#include "reader.cpp"
#include "udp_socket.cpp"
//#include "calc.cpp"
using namespace std;
class monitor
{
	private:
		int FLAG;
		vector<udp_socket> sockets;
	public:
		void initialize();
		void init_sockets(vector<string> list);
		void start();
};

void monitor::initialize()
{
	reader Reader;
	Reader.read_ip();
	init_sockets(Reader.get_ip());
	//calc Calc;
}

void monitor::init_sockets(vector<string> list)
{
	for(int i = 0; i < list.size()-1; i++)
	{
		
		udp_socket Socket;
		sockets.push_back(Socket);
		sockets[i].start_svr(1755 + i);

	}

	char msg[]="hello";
	char buf[1024];
	
	for(int i = 0; i < list.size()-1; i++)
	{	
		
		const char *ip = list[i].c_str();
		cout << ip << "\n";
		sockets[i].puts(msg, sizeof(msg), i, ip);
		sockets[i].gets(buf, sizeof(buf));
		printf("%s\n", buf);
	}
	for(int i = 0; i < list.size()-1; i++)
	{	
		sockets[i].stop_svr();
	}	
	exit(1);
	
}


int main()
{
	monitor Monitor;
	Monitor.initialize();
}






int start_calculate(int position = 0)
{
	//счет
}

