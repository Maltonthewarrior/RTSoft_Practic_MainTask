#include "socket.h"

void udp_socket::start_svr(int port)
{
	sock_svr = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_svr < 0) {
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//htonl(INADDR_ANY);
	if(bind(sock_svr, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		exit(1);
	}
	//printf("start!\n");
}

void udp_socket::stop_svr()
{
	//printf("stop\n");
	close(sock_svr);
}

int udp_socket::gets(char *buf, int size)
{
	bytes_read = recvfrom(sock_svr, buf, size, 0, NULL, NULL);
	buf[bytes_read] = '\0';
	//printf("get!\n");
	return bytes_read;
}

void udp_socket::puts(const char *buf, int size, int port, const char *ip)
{
	sock_clt = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_clt < 0) {
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	sendto(sock_clt, buf, size, 0, (struct sockaddr *)&addr, sizeof(addr));
	close(sock_clt);
	//printf("put!\n");
}
