#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sstream>

#include "cpwm.h"

CPWM::CPWM()
{

}

CPWM::CPWM(const std::string pin_name_slot,uint32_t period,uint32_t duty)
{
	// std::string pinInterfacePath = PWM::GetOCPPath() + PWM::GetFullNameOfFileInDirectory(PWM::GetOCPPath(), pin_name_slot) + "/";
	m_path="/sys/devices/ocp.2/pwm_test_"+pin_name_slot;
	SetPath();

}

CPWM::~CPWM()
{


}


int8_t CPWM::SetPath()
{
	int8_t ret=0;
#ifdef DLP_ARM_LINUX

	ret=access(m_path.c_str(), W_OK);
	if(0!=ret)
	{
		std::cout<<"Can't use that path:"<<m_path<<std::endl;
	}
	else
	{
		m_dutypath = m_path + "/duty";
		m_periodpath = m_path + "/period";
		m_polaritypath = m_path + "/polarity";
		m_runpath = m_path+ "/run";
	}

#endif //DLP_ARM_LINUX
	return ret;

}

int8_t CPWM::SetRun(const uint32_t &running)
{
	int32_t fd;
	int8_t ret=0;

#ifdef DLP_ARM_LINUX

	fd = open(m_runpath.c_str(), O_WRONLY);
	if (-1 == fd)
	{
		std::cout<<"can't open the path in the SetRun:"<<m_runpath<<std::endl;

	}
	//ret = write(fd, u322string(running).c_str(),strlen(u322string(running).c_str()));
	ret = write(fd, u322string(running).c_str(),1);
	if (-1 == ret)
	{
		std::cout<<"can't set run with "<<":"<<running<<std::endl;
	}
	ret=close(fd);
#endif //DLP_ARM_LINUX
	return ret;


}

int8_t CPWM::SetPeriod(const uint32_t &period_value)
{

	int fd;
	int ret=0;

#ifdef DLP_ARM_LINUX

	fd = open(m_periodpath.c_str(), O_WRONLY);
	if (-1 == fd)
	{
		std::cout<<"can't open the path in the SetPeriod:"<<m_periodpath<<std::endl;
	}
	ret = write(fd,u322string(period_value).c_str(), u322string(period_value).length());
	if (-1 == ret)
	{
		std::cout<<"can't set period with "<<":"<<period_value<<std::endl;
	}
	ret=close(fd);
#endif //DLP_ARM_LINUX
	return ret;

}

int8_t CPWM::SetDuty(const uint32_t &duty_value)
{
	int32_t fd;
	int32_t ret=0;
#ifdef DLP_ARM_LINUX

	fd = open(m_dutypath.c_str(), O_WRONLY);
	if (-1 == fd)
	{
		std::cout<<"can't open the path in the SetDuty:"<<m_dutypath<<std::endl;
	}

	ret = write(fd,u322string(duty_value).c_str(), u322string(duty_value).length());
	if (-1 == ret)
	{
		std::cout<<"can't set duty with"<<":"<<duty_value<<std::endl;
	}
	ret=close(fd);
#endif //DLP_ARM_LINUX
	return ret;
}

int8_t CPWM::SetPolarity(const uint32_t &polarity)
{
	int32_t fd;
	int8_t ret=0;
#ifdef DLP_ARM_LINUX

	fd = open(m_polaritypath.c_str(), O_WRONLY);
	if (-1 == fd)
	{
		std::cout<<"can't open the path in the SetPolarity:"<<m_periodpath<<std::endl;
	}

	ret = write(fd, u322string(polarity).c_str(), u322string(polarity).length());
	if (-1 == ret)
	{
		std::cout<<"can't set polarity with "<<":"<<polarity<<std::endl;
	}
	ret=close(fd);
#endif //DLP_ARM_LINUX
	return ret;

}

std::string CPWM::u322string(const uint32_t &u32)
{
	std::stringstream ss;
	ss << u32;
	return ss.str();
}
