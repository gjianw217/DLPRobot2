
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
/*       构造函数                                                       */
/************************************************************************/
CIPServer::CIPServer(const uint16_t &port):CUDPServer(port)
{
	m_pconfig=PCConfig(new CConfig());

    memset(m_info.ptz_name,'\0',10);
	GetInfo(m_info);/*<初始化命令结构体*/
}
/************************************************************************/
/*              析构函数                                                 */
/************************************************************************/
CIPServer::~CIPServer(){}
/*
* @brief  等待命令请求函数
* @param  保存接收到的数据
* @return 返回接收到的命令类型
*/
DLPUdpCmd CIPServer::WaitCMD(DLPUdpInfo &info)
{
	int ret=0;
	CUDPServer::RecvFrom((char*)&info,sizeof(DLPUdpInfo));//接收数据
	return info.cmd;//返回命令类型
}

/*
* @brief  响应查询命令函数
* @param  无
* @return 无
* @note   将本地的命令结构体数据发送出去
*/
void CIPServer::Reply()
{
    std::cout<<"CIPServer::Reply"<<std::endl;
	m_info.cmd = UDP_REPLY;
	CUDPServer::SendTo((char*)&m_info,sizeof(DLPUdpInfo));
}
/*
* @brief  响应重置IP命令函数
* @param  携带着新的重置IP信息及本终端的其他信息
* @return 无
*/
void CIPServer::ResetIP(DLPUdpInfo& info)
{

    std::cout<<"CIPServer::RestIP"<<std::endl;
    int ret;
	//检查合法性
    ret=CheckIP(info);
	//修改IP
	if (0==ret||1==ret)//0表示修改成功，1表示与本地相同，不用修改
	{
		ModifyIP(info);
		m_info.cmd=UDP_RESET_SUCCESS;
	}
	else
	{
        m_info.cmd = UDP_RESET_FAILURE;
	}
	//反馈

	CUDPServer::SendTo((char*)&m_info,sizeof(DLPUdpInfo));
	//重启
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
* @brief  私有函数，检测重置IP地址的合法性及修改配置文件的IP信息
* @param  携带着新的重置IP信息等
* @return 0,1:成功
          -1,-2:失败
*/
int CIPServer::CheckIP(const DLPUdpInfo& info)
{


    dlp_log(DLP_LOG_MSG,"CUDPServer::CheckIP");
    int ret=0;
    if (memcmp(info.ptz_mac,m_info.ptz_mac,sizeof(info.ptz_mac)) == 0)
    {
        if(memcmp(info.ptz_ip,m_info.ptz_ip,sizeof(info.ptz_ip)) == 0)//与已有的IP相同，无需要保存
        {
            ret=1;
        }
        else if(info.ptz_ip[6]==m_info.ptz_ip[6]&&
                info.ptz_ip[4]==m_info.ptz_ip[4]&&
                info.ptz_ip[2]==m_info.ptz_ip[2])
        {
            m_pconfig->SetValue("sys","mip0",info.ptz_port);     //保存新的IP地址和端口
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
* @brief  私有函数，修改网络启动配置文件的IP信息
* @param  携带着新的重置IP信息等
* @return 无
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
		fread(tmp, fileLen, sizeof(char), fp);/*<读取原网络启动文件的信息*/
		fclose(fp);

		std::string strfile(tmp);             /*<将原网络启动文件的信息生成字符串*/

		std::cout<< "BeforefileContent:" << strfile << std::endl;
		/*生成启动文件命令字符串*/
		std::string cip="ifconfig eth0 ";
		std::string cro="route add default gw ";
        std::string strip=Char2str(info.ptz_ip,8);
		cip.append(strip);
		cro.append(strip,0,strip.rfind('.')+1);
		cro.append("1");
		/*匹配替换修改*/
		boost::smatch res;
		boost::regex reg1("ifconfig eth0 ([0-9]+).([0-9]+).([0-9]+).([0-9]+)");
		boost::regex reg2("route add default gw ([0-9]+).([0-9]+).([0-9]+).([0-9]+)");
		if(boost::regex_search(strfile,res,reg1))
		{
			if(strcmp(res[0].str().c_str(),cip.c_str()) != 0)
			{
				std::string s = boost::regex_replace(strfile, reg1, cip);
				s = boost::regex_replace(s, reg2, cro);       /*<修改网络启动文件的IP信息*/

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
/*    从配置文件中得到udp结构体基本信息                                 */
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
/*      将char型字符串ip转成string型字符串                              */
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
