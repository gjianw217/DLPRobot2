#ifndef DLP_UDP_CIPSERVER_H_
#define DLP_UDP_CIPSERVER_H_
#include "cudpserver.h"
#include "../common/dlp.h"

class CIPServer:public CUDPServer
{
public:
	explicit CIPServer(const uint16_t &port);
	~CIPServer();

	DLPUdpCmd WaitCMD(DLPUdpInfo &info);  //�ȴ���������
	void Reply();          //��Ӧ��ѯ����
	void ResetIP(DLPUdpInfo& info);       //��Ӧ����IP����

private:
	int ParseIP(const DLPUdpInfo& info);  //deprecated
	int CheckIP(const DLPUdpInfo& info);  //���������������
	void ModifyIP(const DLPUdpInfo& info);//�޸�IP�����ļ�

	void GetInfo(DLPUdpInfo &info);       //�������ļ��еõ�udp�ṹ�������Ϣ
	std::string Char2str(const unsigned char *ch ,const int len);//��char���ַ���ipת��string���ַ���
	void TestPrintInfo(const DLPUdpInfo &info);
private:
	PCConfig m_pconfig;
	DLPUdpInfo m_info;
};
#endif //DLP_UDP_CIPSERVER_H_
