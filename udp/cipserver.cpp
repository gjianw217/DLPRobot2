
#include "cipserver.h"
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <sstream>
#include "boost/regex.hpp"
#include "../serialization/cconfig.h"

/************************************************************************/
/*       ���캯��                                                       */
/************************************************************************/
CIPServer::CIPServer(const uint16_t &port):CUDPServer(port)
{
	m_pconfig=PCConfig(new CConfig());

    memset(m_info.ptz_name,'\0',10);
	GetInfo(m_info);/*<��ʼ������ṹ��*/
}
/************************************************************************/
/*              ��������                                                 */
/************************************************************************/
CIPServer::~CIPServer(){}
/*
* @brief  �ȴ�����������
* @param  ������յ�������
* @return ���ؽ��յ�����������
*/
DLPUdpCmd CIPServer::WaitCMD(DLPUdpInfo &info)
{
	int ret=0;
	CUDPServer::RecvFrom((char*)&info,sizeof(DLPUdpInfo));//��������
	return info.cmd;//������������
}

/*
* @brief  ��Ӧ��ѯ�����
* @param  ��
* @return ��
* @note   �����ص�����ṹ�����ݷ��ͳ�ȥ
*/
void CIPServer::Reply()
{
    std::cout<<"CIPServer::Reply"<<std::endl;
	m_info.cmd = UDP_REPLY;
	CUDPServer::SendTo((char*)&m_info,sizeof(DLPUdpInfo));
}
/*
* @brief  ��Ӧ����IP�����
* @param  Я�����µ�����IP��Ϣ�����ն˵�������Ϣ
* @return ��
*/
void CIPServer::ResetIP(DLPUdpInfo& info)
{

    std::cout<<"CIPServer::RestIP"<<std::endl;
    int ret;
	//���Ϸ���
    ret=CheckIP(info);
	//�޸�IP
	if (0==ret||1==ret)//0��ʾ�޸ĳɹ���1��ʾ�뱾����ͬ�������޸�
	{
		ModifyIP(info);
		m_info.cmd=UDP_RESET_SUCCESS;
	}
	else
	{
        m_info.cmd = UDP_RESET_FAILURE;
	}
	//����

	CUDPServer::SendTo((char*)&m_info,sizeof(DLPUdpInfo));
	//����
#ifdef DLP_ARM_LINUX
    if(UDP_RESET_SUCCESS==m_info.cmd)
    {
        system("/sbin/reboot");
    }
#endif // DLP_ARM_LINUX

}

/**
* deprecated
*/
int CIPServer::ParseIP(const DLPUdpInfo& info)
{

	dlp_log(DLP_LOG_MSG,"CUDPServer::ParseIP");
	char ipp[]="235.10.3.13:2345";
	//std::string ip=(char *)info.ptz_ip;
	uint8_t ip_array[10];
	int ret=0;
	std::string ip_parrten = "(25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])"
		"."
		"(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
		"."
		"(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
		"."
		"(25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])"
		":"
		"([1-9]{1}[0-9]{0,4})";
	boost::regex ip_regex(ip_parrten);
	boost::cmatch what;
	if (boost::regex_match(ipp, what, ip_regex))
	//if (boost::regex_match((char *)info.ptz_ip, what, ip_regex))
	{
		for(int i = 1; i < what.size(); i++)
		{
			std::cout<<"segment\t"<<what[i].str()<<std::endl;
			ip_array[i-1]=atoi(what[i].str().c_str());
		}
	}
	else
	{
		std::cout<<"Parse IP error"<<std::endl;
		ret=-1;
	}
	return ret;
}


/**
* @brief  ˽�к������������IP��ַ�ĺϷ��Լ��޸������ļ���IP��Ϣ
* @param  Я�����µ�����IP��Ϣ��
* @return 0,1:�ɹ�
          -1,-2:ʧ��
*/
int CIPServer::CheckIP(const DLPUdpInfo& info)
{


    dlp_log(DLP_LOG_MSG,"CUDPServer::CheckIP");
    int ret=0;
    if (memcmp(info.ptz_mac,m_info.ptz_mac,sizeof(info.ptz_mac)) == 0)
    {
        if(memcmp(info.ptz_ip,m_info.ptz_ip,sizeof(info.ptz_ip)) == 0)//�����е�IP��ͬ������Ҫ����
        {
            ret=1;
        }
        else if(info.ptz_ip[6]==m_info.ptz_ip[6]&&
                info.ptz_ip[4]==m_info.ptz_ip[4]&&
                info.ptz_ip[2]==m_info.ptz_ip[2])
        {
            m_pconfig->SetValue("sys","mip0",info.ptz_port);     //�����µ�IP��ַ�Ͷ˿�
            m_pconfig->SetValue("sys","mip1",info.ptz_ip[0]);
            m_pconfig->SetValue("sys","mip2",info.ptz_ip[2]);
            m_pconfig->SetValue("sys","mip3",info.ptz_ip[4]);
            m_pconfig->SetValue("sys","mip4",info.ptz_ip[6]);
            ret=0;
        }
        else
        {
            ret=-1;
        }

    }
    else
    {
        ret=-2;
    }

    return ret;
}

/**
* @brief  ˽�к������޸��������������ļ���IP��Ϣ
* @param  Я�����µ�����IP��Ϣ��
* @return ��
* @author Li'erchao
* @email  1292124225@qq.com
*/
void CIPServer::ModifyIP(const DLPUdpInfo& info)
{
	dlp_log(DLP_LOG_MSG," CIPServer::ModifyIP");

	FILE *fp = NULL;
	if ((fp = fopen("net.sh", "rb")) != NULL)
	{
		fseek(fp, 0, SEEK_END);
		int fileLen = ftell(fp);
		char *tmp = (char *) malloc(sizeof(char) * (fileLen+1));
		memset(tmp,0,sizeof(char) * (fileLen+1));
		fseek(fp, 0, SEEK_SET);
		fread(tmp, fileLen, sizeof(char), fp);/*<��ȡԭ���������ļ�����Ϣ*/
		fclose(fp);

		std::string strfile(tmp);             /*<��ԭ���������ļ�����Ϣ�����ַ���*/

		std::cout<< "BeforefileContent:" << strfile << std::endl;
		/*���������ļ������ַ���*/
		std::string cip="ifconfig eth0 ";
		std::string cro="route add default gw ";
        std::string strip=Char2str(info.ptz_ip,8);
		cip.append(strip);
		cro.append(strip,0,strip.rfind('.')+1);
		cro.append("1");
		/*ƥ���滻�޸�*/
		boost::smatch res;
		boost::regex reg1("ifconfig eth0 ([0-9]+).([0-9]+).([0-9]+).([0-9]+)");
		boost::regex reg2("route add default gw ([0-9]+).([0-9]+).([0-9]+).([0-9]+)");
		if(boost::regex_search(strfile,res,reg1))
		{
			if(strcmp(res[0].str().c_str(),cip.c_str()) != 0)
			{
				std::string s = boost::regex_replace(strfile, reg1, cip);
				s = boost::regex_replace(s, reg2, cro);       /*<�޸����������ļ���IP��Ϣ*/

				std::cout<< "AfterFileContent:" << s << std::endl;
				if ((fp = fopen("net.sh", "wb")) != NULL)
				{
					rewind(fp);
					fwrite(s.c_str(), s.size(), sizeof(char), fp);
					fclose(fp);
				}
			}
		}
		free(tmp);
	}
}

/************************************************************************/
/*    �������ļ��еõ�udp�ṹ�������Ϣ                                 */
/************************************************************************/

void CIPServer::GetInfo(DLPUdpInfo &info)
{
    //Get info from config file
	info.ptz_mac[0]=m_pconfig->GetValue("sys","mac0");
	info.ptz_mac[1]='-';
	info.ptz_mac[2]=m_pconfig->GetValue("sys","mac1");
	info.ptz_mac[3]='-';
	info.ptz_mac[4]=m_pconfig->GetValue("sys","mac2");
	info.ptz_mac[5]='-';
	info.ptz_mac[6]=m_pconfig->GetValue("sys","mac3");
	info.ptz_mac[7]='-';
	info.ptz_mac[8]=m_pconfig->GetValue("sys","mac4");
	info.ptz_mac[9]='-';;
	info.ptz_mac[10]=m_pconfig->GetValue("sys","mac5");
	info.ptz_mac[11]='\0';

	info.ptz_ip[0]=m_pconfig->GetValue("sys","mip1");;
	info.ptz_ip[1]='.';
	info.ptz_ip[2]=m_pconfig->GetValue("sys","mip2");;
	info.ptz_ip[3]='.';
	info.ptz_ip[4]=m_pconfig->GetValue("sys","mip3");;
	info.ptz_ip[5]='.';;
	info.ptz_ip[6]=m_pconfig->GetValue("sys","mip4");;
	info.ptz_ip[7]='\0';

	info.ptz_id=m_pconfig->GetValue("sys","id");;
	info.ptz_port=m_pconfig->GetValue("sys","mip0");
	strcpy(info.ptz_name,"robot");
	info.ptz_name[5]=m_pconfig->GetValue("sys","nameno")+'0';//int convert to the char
	info.ptz_name[6]='\0';

    TestPrintInfo(info);
}
/************************************************************************/
/*      ��char���ַ���ipת��string���ַ���                              */
/************************************************************************/
std::string CIPServer::Char2str(const unsigned char *ch ,const int len)
{
    dlp_log(DLP_LOG_MSG,"CIPServer::Char2str");
    std::stringstream ss;
    std::string ret="";
    int ip_value;

    if(NULL==ch|len<0|len>8)
        return ret;
    for(int i=6;i>=0;i-=2)
   // for(int i=0;i<len;i+=2)
    {
        ip_value=ch[i];
        ss<<ip_value;
        ss.put('.');
    }
    ret=ss.str();
//    ret.pop_back();//C++11
    ret.erase(ret.size()-1,1);//

	return ret;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void CIPServer::TestPrintInfo(const DLPUdpInfo &info)
{
//#ifdef DLP_DEBUG
//    std::cout<<"Local Config info:"<<std::endl;
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mac0"),m_pconfig->GetValue("sys","mac0"),m_pconfig->GetValue("sys","mac0"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mac1"),m_pconfig->GetValue("sys","mac1"),m_pconfig->GetValue("sys","mac1"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mac2"),m_pconfig->GetValue("sys","mac2"),m_pconfig->GetValue("sys","mac2"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mac3"),m_pconfig->GetValue("sys","mac3"),m_pconfig->GetValue("sys","mac3"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mac4"),m_pconfig->GetValue("sys","mac4"),m_pconfig->GetValue("sys","mac4"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mac5"),m_pconfig->GetValue("sys","mac5"),m_pconfig->GetValue("sys","mac5"));
//
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mip4"),m_pconfig->GetValue("sys","mip4"),m_pconfig->GetValue("sys","mip4"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mip3"),m_pconfig->GetValue("sys","mip3"),m_pconfig->GetValue("sys","mip3"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mip2"),m_pconfig->GetValue("sys","mip2"),m_pconfig->GetValue("sys","mip2"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mip1"),m_pconfig->GetValue("sys","mip1"),m_pconfig->GetValue("sys","mip1"));
//	printf("%d,%c,%x\n",m_pconfig->GetValue("sys","mip0"),m_pconfig->GetValue("sys","mip0"),m_pconfig->GetValue("sys","mip0"));
    dlp_log(DLP_LOG_MSG,"Trans Command info");
    printf("%d,%d,%d,%d:%d\n",info.ptz_ip[6],info.ptz_ip[4],info.ptz_ip[2],info.ptz_ip[0],info.ptz_port);
	printf("%x,%x,%x,%x,%x,%x\n",info.ptz_mac[10],info.ptz_mac[8],info.ptz_mac[6],info.ptz_mac[4],info.ptz_mac[2],info.ptz_mac[0]);
	printf("%s\n",info.ptz_name);
	printf("%d\n",info.ptz_id);
//#endif // DLP_DEBUG

}
