/*
* @file   ͷ�ļ�
* @brief  ��װBeaglebone���������Ʒ��
* @author GuoJianwei & gjianw217@163.com
*/

#ifndef DLP_DRIVERS_GPIO_H_
#define DLP_DRIVERS_GPIO_H_
#include <cstdio>
#include <cstdlib>
#include <string>
#include "../dlp/dlp.h"

#define GPIO_DIR "/sys/class/gpio/gpio"

class CGPIO
{
public:
	CGPIO();
	~CGPIO();
	void SetPort(const std::string &pin,const uint8_t &direction);
	void SetValue(const uint8_t &value);
	uint8_t GetValue();
private:
	FILE *fp;
	std::string m_pin;
	std::string m_direction_path;
	std::string m_value_path;
};


#endif //DLP_DRIVERS_GPIO_H_


