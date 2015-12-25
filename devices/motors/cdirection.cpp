#include "cdirection.h"
#include <sstream>
#include "../../utils/cdebug.h"

CDirection::CDirection()
{
	m_pgpio=PCGPIO(new CGPIO());
	m_value=0;
}

CDirection::~CDirection(){}

void CDirection::Config(const uint16_t &pin,const uint16_t &direction)
{
	//dlp_logs("[debug] CDirection::Config pin",pin);
	dlp_log(DLP_LOG_DEBUG,"CDirection::Config");
	if(pin>128||pin<1)
	{
        dlp_log_value(DLP_LOG_ERR,"CDirection::Config1:PIN:",pin);
        return;
	}

	std::string strpin;
	std::stringstream ss;
    ss<<pin;
    strpin= ss.str();
	m_pgpio->SetPort(static_cast<const std::string>(strpin),PINOUT);
	m_pgpio->SetValue(direction);
}
void CDirection::SetDirValue(const uint16_t &value)
{
	//dlp_log(DLP_LOG_DEBUG,"CDirection::SetDirValue ",value);
	m_value=value;
	m_pgpio->SetValue(m_value);
}
uint16_t CDirection::GetDirValue()
{
    return m_value;
}



