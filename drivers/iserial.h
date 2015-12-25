/*
* @file   iserial.h
* @brief  define the serial interface
* @author GuoJianwei & gjianw217@163.com
* @note
*/

#ifndef DLP_DRIVERS_ISERIAL_H_
#define DLP_DRIVERS_ISERIAL_H_
#include <stdint.h>
#include "../dlp/dlp.h"
class ISerial
{
public:

	ISerial();
	~ISerial();
	virtual int Open(const char *com)=0;
	virtual void Config(const uint8_t &baud,const uint8_t &databit,const uint8_t &parity,const uint8_t &stopbit)=0;
	virtual int Read(uint8_t *data,const uint8_t &len)=0;
	virtual int Write(const uint8_t *data,const uint8_t &len)=0;
protected:
    virtual void SetBaudRate(const uint8_t &rate )=0;
	virtual void SetDataBits(const uint8_t &data )=0;
	virtual void SetParity(const uint8_t &parity)=0;
	virtual void SetStopBits(const uint8_t &stop)=0;
	virtual void SetFlowControl(const uint8_t &flow)=0;


private:

};

#endif // DLP_DRIVERS_ISERIAL_H_
