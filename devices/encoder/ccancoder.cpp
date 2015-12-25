#include "ccancoder.h"
#include "../../drivers/ccan.h"
CCANCoder::CCANCoder(const uint8_t &id):IEncoder()
{
	m_pcan=PCCAN(new CCAN(id));
}

CCANCoder::CCANCoder(PCCAN pccan)
{
	m_pcan=pccan;
}
CCANCoder::~CCANCoder()
{

}

void CCANCoder::Config(const DLPEncoderAttr &attr)
{
	m_attr=attr;
}

int CCANCoder::GetData(uint16_t *data)
{
	int ret=m_pcan->CANGetData(data);
	this->m_pcounter->SetCounter(data[0]);
	std::cout<<"CCANCoder::GetData:"<<data[0]<<":";
	m_angle=this->m_pcounter->GetAngle();          /*Save the encoder turned Angle*/
	//std::cout<<m_angle<<":";
	//m_angle=m_angle*m_attr.dlp_gear[1]/m_attr.dlp_gear[0];
	//std::cout<<m_angle<<":"<<std::endl;
	return ret;
}

int CCANCoder::PollID(uint16_t *id)
{
	return m_pcan->CANPollIDs(id);
}

int CCANCoder::SetBaudrate(const uint16_t &high_rate,const uint16_t &low_rate)
{
	return m_pcan->CANSetBaudrate(high_rate,low_rate);
}

int CCANCoder::SetID(const uint16_t &id)
{
	return m_pcan->CANSetID(id);
}
