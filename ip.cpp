#include "ip.h"

host::host(){hp = 3;}

host::host(char *_ip, int _port)
{
	hp = 3;
	strcpy(ip, _ip);
	port = _port;
}

host::host(const host &a)
{
	strcpy(ip, a.ip);
	port = a.port;
	hp = 3;
}
