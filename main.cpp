#include <pthread.h>
#include <time.h>
#include <functional>
#include <algorithm>
#include "reader.h"
#include "socket.h"

vector<host> list;
int g_port;
udp_socket my_sock;

using namespace std;

class func
{
	public:
		char ip[16];
		int port;
		func(char *_ip, int _port)
		{
			strcpy(ip, _ip);
			port = _port;
		}
		bool operator()(const host& a)
		{
			return !strcmp(a.ip, ip) && a.port==port?true:false;
		}
};

void msg_handler(const char * msg_in)
{
	char msg_out[1024];
	const char *pos_in = msg_in;
	char ip[] = "127.0.0.1";
	int port;
	char cmd[64];
	int count = 0;
	sprintf(msg_out, "%d", g_port);
	if(sscanf(pos_in, "%d", &port) !=1 )
		return ;
	printf("%s:%d\n", ip, port);
	while((pos_in = strchr(pos_in+1, '\n')) && sscanf(pos_in, "%s", cmd) == 1)
	{
		printf("cmd:%s\n", cmd);
		if(!strcmp(cmd, "echo_request"))
		{
			count++;
			sprintf(strchr(msg_out, '\0'), "\necho_answer");
			continue;		
		}
		if(!strcmp(cmd, "echo_answer"))
		{
			func my_func(ip, port);
			vector<host>::iterator it = find_if(list.begin(), list.end(), my_func);
			//vector<host>::iterator it = find_if(list.begin(), list.end(), 
			//[ip, port](const host& a)->bool
			//{
			//	return !strcmp(a.ip, ip) && a.port==port?true:false;
			//});
			if(it == list.end())
			{
				printf("error - unknown ip and port %s:%d\n", ip, port);
				continue;
			}
			if(it->hp<0)
				printf("%s:%d - reacheble\n", ip, port);
			it->hp = 3;
			continue;		
		}
		//if(....){}
		//...
		printf("error unknown comand %s\n", cmd);
	}
	if(count == 0)
		return ;
	my_sock.puts(msg_out, sizeof(msg_out), port, ip);	
}

void * f_thrd_ping(void * t)
{
	reader rd;
	rd.read_ip(list);
	char msg[1024];
	sprintf(msg, "%d\necho_request", g_port);
	while(true)
	{
		for(int i=0; i < list.size(); ++i)
		{
			if(g_port == list[i].port)
				continue;
			my_sock.puts(msg, sizeof(msg), list[i].port, list[i].ip);
			--list[i].hp;
			if(list[i].hp<0)
			{
				printf("%s:%d unreacheble\n",  list[i].ip,  list[i].port);
			}
			sleep(5);
		}
		sleep(60);
	}
}

int main(int argc, char * argv[])
{
	pthread_t thrd_ping;
	char msg[1024];
	g_port = argc>1?atoi(argv[1]):1755;
	my_sock.start_svr(g_port);
	pthread_create(&thrd_ping, NULL, f_thrd_ping, NULL);
	while(true)
	{
		//my_sock.puts(msg, sizeof(msg), 1755, "127.0.0.1");
		my_sock.gets(msg, sizeof(msg));
		msg_handler(msg);
	}
	my_sock.stop_svr();
	return 0;
}
