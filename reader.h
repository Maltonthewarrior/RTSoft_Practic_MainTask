#ifndef READER
#define READER


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class reader
{
private:
	const string FILENAME = "ip.txt";
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
}




vector<string> reader::get_ip()
{
	return list;
}


#endif