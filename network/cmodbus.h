/*
* @file   头文件
* @brief  重新封装Modbus协议中结构体：modbus_mapping_t
* @author GuoJianwei & gjianw217@163.com
*/
#ifndef DLP_NETWORK_CMODBUS_H_
#define DLP_NETWORK_CMODBUS_H_
#include <stdint.h>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include "modbus/modbus.h"
#include "modbus/modbus-tcp.h"
#include "../dlp/dlp.h"
class CModbus
{
public:
	CModbus(PCDataMapping datamapping,const char *ip_address="127.0.0.1", const int &port=1502);
	//   CModbus(modbus_mapping_t *pmb,const char *ip_address="192.168.0.217", const int port=1502);
	virtual ~CModbus();

	virtual int Receive(uint8_t *req);
	virtual int Reply(const uint8_t *req,const int &req_length);

	virtual int ListenNum(const int &nb_connection);
	virtual int Accept(int *socket);
	virtual int SetSocket(const int &socket);
	virtual int SetSlave(const int &slave);
	virtual void Show(const int &device=0,const int &tab=0);

	PCDataMapping GetDataMapping();
private:
	modbus_t *m_pctx;
	modbus_mapping_t *m_pmb;
	PCDataMapping m_pdatamapping;
private:

	void Array2IP(const uint16_t *ip_array,char *ip);
};

#endif//DLP_NETWORK_CMODBUS_H_


