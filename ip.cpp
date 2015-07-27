#include "ip.h"

host::host(){}

host::host(char *_ip, int _port)
{
	strcpy(ip, _ip);
	port = _port;
}

host::host(const host &a)
{
	strcpy(ip, a.ip);
	port = a.port;
}
