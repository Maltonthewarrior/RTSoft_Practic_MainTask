#include "ip.h"

host::host(){hp = 3; is_active = 0;}

host::host(char *_ip, int _port)
{
	hp = 3;
	is_active = 0;
	strcpy(ip, _ip);
	port = _port;
}

host::host(const host &a)
{
	strcpy(ip, a.ip);
	port = a.port;
	is_active = a.is_active;
	hp = a.hp;
}
