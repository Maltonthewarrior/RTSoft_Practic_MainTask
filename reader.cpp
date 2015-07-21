#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
//#include <algorithm>
//#include "print.h"

using namespace std;


class reader
{
private:
	#define FILENAME "ip.txt"
	vector<string> list;
public:
	void write_ip();
	char read_ip();
	vector<string> get_ip();
};

char reader::read_ip()
{
	
	ifstream in_stream;
	string line;

	in_stream.open(FILENAME);
	while(!in_stream.eof())
	{
    	in_stream >> line;
    	 list.push_back(line);
	}

	in_stream.close();

	for(int i = 0; i < list.size()-1; i++)
        //cout << list[i] << "\n";
    return 0;	
}

vector<string> reader::get_ip()
{
	return list;
}
/*int main ()
 {
 	reader r;
 	r.read_ip();
 	//sleep(10);

}*/

