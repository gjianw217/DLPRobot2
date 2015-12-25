/*
* @file   头文件
* @brief  重新封装Modbus协议中的数据结构体：modbus_mapping_t
* @author GuoJianwei & gjianw217@163.com
*/
#ifndef DLP_NETWORK_CDATA_MAPPING_H_
#define DLP_NETWORK_CDATA_MAPPING_H_

#include <stdint.h>
#include <cassert>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include "../robot/cconfig.h"
#include "../dlp/dlp.h"
#include "modbus/modbus.h"

class CDataMapping
{
public:
	explicit CDataMapping(PCConfig config);
	~CDataMapping();

	void Init();
	void SetCoils(const uint8_t *src,int addr, const int nb);
	void GetCoils(int addr, const int nb, uint16_t *dest);
	void SetDiscreteInputs(const uint8_t *src,int addr, const int nb);
	void GetDiscreteInputs(int addr, const int nb, uint8_t *dest);
	void SetInputRegisters(const uint16_t *src,int addr,const  int nb);
	void GetInputRegisters(int addr, const int nb, uint16_t *dest);
	void SetHoldRegisters(const uint16_t *src,int addr, const int nb);
	void GetHoldRegisters(int addr, const int nb, uint16_t *dest);

	modbus_mapping_t *GetUnit();
private:
	PCConfig m_pconfig;
	modbus_mapping_t *m_pmb_mapping;
};
#endif //DLP_NETWORK_CDATA_MAPPING_H_



