#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


class udp_socket
{
public:
	void start_svr(int port);
	void stop_svr();
	int gets(char *buf, int size);
	void puts(const char *buf, int size, int port, const char *ip);
private:
	int sock_svr;
	int sock_clt;
	struct sockaddr_in addr;
	int bytes_read;
};




