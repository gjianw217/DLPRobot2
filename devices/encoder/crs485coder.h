#ifndef DLP_DEVICES_ENCODER_CRS485CODER_H_
#define DLP_DEVICES_ENCODER_CRS485CODER_H_

#include "iencoder.h"
class CRS485Coder:public IEncoder
{
public:
	 CRS485Coder();
	 explicit CRS485Coder(std::string dev_name);
	 explicit CRS485Coder(PCSerial pserial);
	~ CRS485Coder();

	virtual void Config(const DLPEncoderAttr &attr);
	virtual int GetData(uint16_t *data);
	virtual int PollID(uint16_t *ID);
	virtual int SetBaudrate(const uint16_t &high_rate,const uint16_t &low_rate);
	virtual int SetID(const uint16_t &id);
protected:
	uint16_t GetCRC(uint8_t *cmd,uint8_t cmd_len);
private:
    PCGPIO   m_preadwrite;
	PCSerial m_pserial;
	std::string m_dev_name;
};

#endif //DLP_DEVICES_ENCODER_CRS485CODER_H_
