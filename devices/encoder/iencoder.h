#ifndef DLP_DEVICES_ENCODER_IENCODER_H_
#define DLP_DEVICES_ENCODER_IENCODER_H_
#include "../../dlp/dlp.h"
#include "csensorcounter.h"


class IEncoder
{
public:
	IEncoder();
	~IEncoder();

	virtual void Config(const DLPEncoderAttr &attr)=0;
	virtual int GetData(uint16_t *data)=0;
	virtual int PollID(uint16_t *ID)=0;
	virtual int SetBaudrate(const uint16_t &high_rate,const uint16_t &low_rate)=0;
	virtual int SetID(const uint16_t &id)=0;

	void CounterInit(const bool get_value);      //complete the initialization of encoder counter
	float GetCoderAngle();   //returns the current angle of encoder
protected:
	DLPEncoderAttr m_attr;
	PCSensorCounter m_pcounter;
	float m_angle;             //save the encoder turning Angle to position the motor
};
#endif  //DLP_DEVICES_ENCODER_IENCODER_H_
