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
	std::string strpin;	char charpin[7]={0};          /*< ���ַ�����Ĵ�С����Ϊ6������sprintf�����ᱨ��                 */
	sprintf(charpin,"%d",pin);    /*< ԭ����uint16_t���Ϊ65535��5λ�����ټ�һλ�ַ�����ʶλ���պ�6λ*/

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
