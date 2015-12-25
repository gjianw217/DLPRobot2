#include "../network/cdata-mapping.h"
#include "ccontrol.h"
#include "../utils/cdebug.h"

CControl::CControl()
{
	m_control_sock=0;
	m_sock_ip_pools[m_control_sock]="127.0.0.1";
}
CControl::~CControl()
{
	if (0!=m_control_sock)
	{
		m_control_sock=0;
		UpdateControl();
	}
}

void CControl::SetDataMapping(PCDataMapping data_mapping)
{
	m_data_mapping=data_mapping;
}

void CControl::Start(const int &sock,const std::string &newip)
{
	this->m_sock_ip_pools[sock]=newip;
}
void CControl::Close(const int &sock)
{
	if (sock==m_control_sock)
	{
		m_control_sock=0;
		UpdateControl();
	}
	m_sock_ip_pools.erase(sock);
}

int CControl::GetControl(const int &sock,const DLPModbusCmd &cmd)
{
	int ret=1;
	//如果管理控制权
	std::cout<<"CControl::GetControl"<<std::endl;

	if ((cmd.dev_type|cmd.dev_func)==0)
	{
		if (cmd.cmd_data[0]==1)
		{
			SetControl(sock);
		}
		else
		{
			std::cout<<"Cancel Cmd Right"<<std::endl;
			m_control_sock=0;
			UpdateControl();
		}

	}
	//如果判断控制权
	else
	{
		ret=(0==m_control_sock?0:1);
		//ret=CheckControl(sock);
	}
	return ret;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int CControl::SetControl(const int &sock)
{
	int ret=1;
	//std::cout<<"CControl::SetControl:"<<sock<<":"<<m_control_sock<<std::endl;
	/*获取控制权*/
	if(0==this->m_control_sock)
	{
		this->m_control_sock=sock;
		/*应该保存到modbus_mapping结构体中*/
		UpdateControl();
		dlp_log(DLP_LOG_MSG,"success");
	}
	/*如果已经获取控制权*/
	else if(sock==m_control_sock)
	{
		dlp_log(DLP_LOG_MSG,"has right");
	}
	/*如果已被他人控制*/
	else
	{
		ret=0;
		dlp_log(DLP_LOG_MSG,"failure");
	}
	return ret;
}
void CControl::UpdateControl()
{
	uint16_t ip_array[5]={0};

	IP2Array(GetControlIP(),ip_array);
	ip_array[4]=GetControlSock();

	m_data_mapping->SetInputRegisters(ip_array,SYSTEM|S_GET_CONTROL_IP,5);
}
int CControl::GetControlSock()
{
	return m_control_sock;
}
std::string CControl::GetControlIP()
{
	return m_sock_ip_pools[m_control_sock];
}

void CControl::IP2Array(const std::string &ip,uint16_t *ip_array)
{

	std::string flag(".");
	std::string::size_type position=0;
	int i=1,j=0;
	int pos[4]={0};
	int len[4]={0};

	while((position=ip.find_first_of(flag,position))!=std::string::npos)
	{
		pos[i]  =position+1;
		len[j++]=position++-pos[i++-1];
	}

	len[3]=ip.length()-pos[3];

	for (i=0,j=3;i<4;i++,j--)
	{
		ip_array[j]=atoi(ip.substr(pos[i],len[i]).c_str());
		std::cout<<std::dec<<ip_array[j]<<flag;
	}
	std::cout<<std::endl;

}





