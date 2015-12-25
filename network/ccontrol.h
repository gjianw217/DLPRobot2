#ifndef DLP_NETWORK_CCONTROL_H_
#define DLP_NETWORK_CCONTROL_H_
#include <string>
#include <map>
#include "../dlp/dlp.h"

class CControl
{
public:
	CControl();
	~CControl();
	void SetDataMapping(PCDataMapping data_mapping);

	void Start(const int &sock,const std::string &host);
	void Close(const int &sock);
	int GetControl(const int &sock,const DLPModbusCmd &cmd);
private:
	void UpdateControl();
	int GetControlSock();
	int SetControl(const int &sock);
	std::string GetControlIP();

	void IP2Array(const std::string &ip,uint16_t *ip_array);
private:
	std::map<int,std::string> m_sock_ip_pools;
	int m_control_sock;
	PCDataMapping  m_data_mapping;
};

#endif //DLP_NETWORK_CCONTROL_H_
