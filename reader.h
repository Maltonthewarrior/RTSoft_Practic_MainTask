#include <iostream>
#include <fstream>
#include <vector>
#include "ip.h"

using namespace std;


class reader
{
private:
	const char* FILENAME;
public:
	reader();
	void read_ip(vector<host>& list);
};


