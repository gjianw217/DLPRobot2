#include "iencoder.h"
#include <cmath>
IEncoder::IEncoder()
{
	m_angle=0.0;
	m_pcounter=PCSensorCounter(new CSensorCounter());
}

IEncoder::~IEncoder()
{

}

void IEncoder::CounterInit(const bool get_value)//Must after the configuration parameters, and then call this function
{
std::cout<<"IEncoder::CounterInit()"<<std::endl;
	uint16_t temp[5]={0};
	uint32_t maxvalue=pow(2.0,m_attr.dlp_bits)-1;
	//std::cout<<maxvalue<<std::endl;
	this->m_pcounter->SetMaxCounter(maxvalue);//////
	if(get_value)
	{
        GetData(temp);
        this->m_pcounter->SetCounter(temp[0]);
        this->m_pcounter->ResetZero();
	}

}

float IEncoder::GetCoderAngle()
{
	return m_angle;
}
