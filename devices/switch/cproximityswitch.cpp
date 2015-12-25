#include "cproximityswitch.h"
#include "../../drivers/cgpio.h"
CProximitySwitch::CProximitySwitch()
{
    m_pgpio=PCGPIO(new CGPIO());
}
CProximitySwitch::~CProximitySwitch()
{

}
void CProximitySwitch::Config(const uint16_t &pin)
{
	std::string strpin;	char charpin[7]={0};          /*< 该字符数组的大小至少为6，否则sprintf函数会报错                 */
	sprintf(charpin,"%d",pin);    /*< 原因是uint16_t最大为65535即5位数，再加一位字符串标识位，刚好6位*/

	strpin=charpin;
	m_pgpio->SetPort(strpin,PININ);
}
bool CProximitySwitch::IsProximity()
{
	bool ret=false;
	if(m_pgpio->GetValue()==1)
	{
		ret=true;
	}

	return ret;
}
