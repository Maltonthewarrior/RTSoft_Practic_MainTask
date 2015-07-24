#ifndef SOCK
#define SOCK

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
	void start(int index);
private:
	int sock_svr;
	int sock_clt;
	struct sockaddr_in addr;
	int bytes_read;
};

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
}

void udp_socket::stop_svr()
{
	close(sock_svr);
}

int udp_socket::gets(char *buf, int size)
{
	bytes_read = recvfrom(sock_svr, buf, size, 0, NULL, NULL);    

	if (bytes_read <= 0)
	{	
	perror(NULL);
    close(sock_svr);
    exit(1);
	}
	
	buf[bytes_read] = '\0';
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
}



/*int main()
{
	udp_socket my_sock;
	char msg[]="hello";
	char buf[1024];
	my_sock.start_svr(1755);
	my_sock.puts(msg, sizeof(msg), 1755, "127.0.0.1");
	my_sock.gets(buf, sizeof(buf));
	printf("%s\n", buf);
	my_sock.stop_svr();
	return 0;
}*/
#endif