#include <pthread.h>
#include <time.h>
#include "reader.h"
#include "socket.h"

vector<host> list;
int g_port;

void * f_thrd_ping(void * t)
{
	reader rd;
	rd.read_ip(list);
	char msg[1024];
	sprintf(msg, "echo %d", g_port);
	for(int i=0; i < list.size(); ++i)
	{
		printf("%s %d", list[i].ip, list[i].port);
	}
}

int main(int argc, char * argv[])
{
	printf("hello");
	udp_socket my_sock;
	pthread_t thrd_ping;
	//char msg[]="hello";
	char buf[1024];
	g_port = argc>1?atoi(argv[1]):1755;
	my_sock.start_svr(g_port);
	pthread_create(&thrd_ping, NULL, f_thrd_ping, NULL);
	while(true)
	{
		//my_sock.puts(msg, sizeof(msg), 1755, "127.0.0.1");
		my_sock.gets(buf, sizeof(buf));
		printf("%s\n", buf);
	}
	my_sock.stop_svr();
	return 0;
}
