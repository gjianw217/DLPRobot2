#ifndef DLP_UDP_CIPSERVER_H_
#define DLP_UDP_CIPSERVER_H_
#include "cudpserver.h"
#include "../common/dlp.h"

class CIPServer:public CUDPServer
{
public:
	explicit CIPServer(const uint16_t &port);
	~CIPServer();

	DLPUdpCmd WaitCMD(DLPUdpInfo &info);  //等待命令请求
	void Reply();          //响应查询命令
	void ResetIP(DLPUdpInfo& info);       //响应重置IP命令

private:
	int ParseIP(const DLPUdpInfo& info);  //deprecated
	int CheckIP(const DLPUdpInfo& info);  //检查重置命令条件
	void ModifyIP(const DLPUdpInfo& info);//修改IP配置文件

	void GetInfo(DLPUdpInfo &info);       //从配置文件中得到udp结构体基本信息
	std::string Char2str(const unsigned char *ch ,const int len);//将char型字符串ip转成string型字符串
	void TestPrintInfo(const DLPUdpInfo &info);
private:
	PCConfig m_pconfig;
	DLPUdpInfo m_info;
};
#endif //DLP_UDP_CIPSERVER_H_
