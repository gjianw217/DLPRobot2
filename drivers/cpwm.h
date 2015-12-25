/*
* @file   cpwm.h
* @brief  Encapsulation Beaglebone PWM module interface
* @author GuoJianwei & gjianw217@163.com
*/

#ifndef DLP_DRIVERS_CPWM_H_
#define DLP_DRIVERS_CPWM_H_
#include "../dlp/dlp.h"
#include <string>

class CPWM
{
public:
	CPWM();
	CPWM(const std::string pin_name,uint32_t period=1000000000,uint32_t duty=500000000);
	~CPWM();

	int8_t SetRun(const uint32_t &running);
	int8_t SetPeriod(const uint32_t &period_value);
	int8_t SetDuty(const uint32_t &duty_value);
	int8_t SetPolarity(const uint32_t &polarity);
private:

	int8_t SetPath();
	std::string u322string(const uint32_t &u32);

	std::string m_path;
	std::string m_dutypath;
	std::string m_periodpath;
	std::string m_polaritypath;
	std::string m_runpath ;
};

#endif // DLP_DRIVERS_CPWM_H_
