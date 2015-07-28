#include <string.h>

class host
{
public:
	char ip[16];
	int port;
	int hp;
	host(char *_ip, int _port);
	host(const host &a);	
	host();
};


