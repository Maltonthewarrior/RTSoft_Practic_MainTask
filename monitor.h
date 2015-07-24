#ifndef MONITOR
#define MONITOR

#include <pthread.h>
#include <thread> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <vector>
#include "reader.h"
#include "socket.h"

//#include <thread>
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;
using namespace std;
vector<int> status;
vector<string> list;
class monitor
{
	private:
		int FLAG;
		vector<udp_socket> sockets;

	public:
		void initialize();
		void init_sockets(vector<string> list);
		void start();
		void start_sock();
		void *sending((void *) index, (void *)ip);
		void catching(int index);
		void monitoring(int index);
};

void monitor::initialize()
{

}

void monitor::init_sockets(vector<string> list)
{
	for(int i = 0; i < list.size()-1; i++)
	{
		
		udp_socket Socket;
		sockets.push_back(Socket);
		sockets[i].start_svr(1755 + i);

	}
}



void monitor::start()
{
	initialize();

	reader Reader;
	Reader.read_ip();
	list = Reader.get_ip();
	init_sockets(list);
	pthread_t threads[(list.size()-1)*3];
	pthread_attr_t attr;

	pthread_mutex_init(&count_mutex, NULL);
	pthread_cond_init(&count_threshold_cv, NULL);


	
	for(int i = 0; i < list.size()-1; i++)
	{
		status.push_back(i);
	}



	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (int i = 0; i <= list.size()-1; i += 1)
	{	
		const char *ip = list[i].c_str();
		pthread_create(&threads[i], &attr, sending, i, ip);
	}
	for (int j = 0; j <= list.size()-1; j += 1)
	{
		pthread_create(&threads[list.size()-1+j], &attr, catching, j);
	}
	for (int k = 0; k <= list.size()-1; k += 1)
	{
		pthread_create(&threads[list.size()-1+list.size()-1+k], &attr, monitoring, k);
	}

	

	for (int i = 0; i < (list.size()-1)*3; i++)
	{
		pthread_join(threads[i], NULL);
	}
	//printf("Main(): Waited on %d threads. Done.\n", NUM_THREADS);

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&count_mutex);
	pthread_cond_destroy(&count_threshold_cv);
	pthread_exit(NULL);

}

void *monitor::sending((void *) index, (void *) *ip)
{
	char msg[]="hello";
	while(1)
	{	
	sockets[index].puts(msg, sizeof(msg), 1755+index, ip);
	sleep(1);
	}
}
void monitor::catching(int index)
{
	char buf[1024];
	while(1)
	{
	sockets[index].gets(buf, sizeof(buf));
	printf("%s\n", buf);
	pthread_mutex_lock(&count_mutex);
	status[index] = 0;
	pthread_mutex_unlock(&count_mutex);
	}
}
void monitor::monitoring(int index)
{
	status[index] = 0;
	const char *ip = list[index].c_str();
	while(1)
	{
	sleep(1);
	pthread_mutex_lock(&count_mutex);
	if (status[index] == 5)
		{
			printf("%s is inactive\n", ip);
		}
	else
		{		
			status[index]++;
			printf("%s active\n", ip);	
		}
	pthread_mutex_unlock(&count_mutex);
	
	} 

}



#endif