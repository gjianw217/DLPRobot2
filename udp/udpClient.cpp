#include <iostream>
#include "cudpclient.h"

int main()
{
    std::cout<<"Udp Client Start"<<std::endl;	uint16_t times=0;	//char data[21]={'1','9','2','.','1','6','8','.','0','0','2','.','2','1','7',':','1','0','0','3','\0'};////3*4+4+4=20	char data[]="128.10.3.13:22344";	CUDPClient myclient(9955);	myclient.Init();	while(1)	{		myclient.SendTo(data,sizeof(data));		std::cout<<times++<<"Send Data:"<<data<<std::endl;		sleep(10);	}	return 0;

}
