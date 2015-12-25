#ifndef DLP_DEVICES_ENCODER_CCANCODER_H_
#define DLP_DEVICES_ENCODER_CCANCODER_H_

#include "iencoder.h"
class CCANCoder:public IEncoder
{
public:
	explicit CCANCoder(const uint8_t &id);
	explicit CCANCoder(PCCAN pccan);
	~CCANCoder();

	virtual void Config(const DLPEncoderAttr &attr);
	virtual int GetData(uint16_t *data);
	virtual int PollID(uint16_t *ID);
	virtual int SetBaudrate(const uint16_t &high_rate,const uint16_t &low_rate);
	virtual int SetID(const uint16_t &id);
protected:
private:
	PCCAN m_pcan;
};

#endif //DLP_DEVICES_ENCODER_CCANCODER_H_