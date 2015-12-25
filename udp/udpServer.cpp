#include <iostream>#include "cipserver.h"int main(){	std::cout<<"Udp Server Start"<<std::endl;

	DLPUdpCmd cmd;
	DLPUdpInfo info;
	CIPServer myserver(8080);
	myserver.Init();

	while(1) //一直等待
	{
		std::cout<<"Waiting cmd...."<<std::endl;
		cmd=myserver.WaitCMD(info);
		switch(cmd)
		{
		case UDP_SEARCH:
			myserver.Reply();
			break;
		case UDP_RESET:
			myserver.ResetIP(info);
			break;
		default:std::cout<<"Not UDP Command"<<std::endl;
		}
	}	return 0;}