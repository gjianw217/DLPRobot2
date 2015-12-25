/*
* @file   cserial.h
* @brief  Encapsulation serial interface in the Boost library ,
		  which is convenient to use on the Beaglebone platform
* @author GuoJianwei & gjianw217@163.com
* @note boost/asio/serial_port.hpp
*/

#ifndef DLP_DRIVERS_CSERIAL_H_
#define DLP_DRIVERS_CSERIAL_H_

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>
#ifndef DLP_WINDOW
#include <termios.h>
#include <unistd.h>
#endif
#include "iserial.h"


class CSerial:public ISerial
{
public:
	//enum{BR2400=0,BR4800,BR9600,BR19200,BR38400,BR57600,BR115200,BR_NB= -1};
	CSerial();
	~CSerial();
	virtual int Open(const char *com);
	virtual void Config(const uint8_t &baud,const uint8_t &databit,const uint8_t &parity,const uint8_t &stopbit);
	virtual int Read(uint8_t *data,const uint8_t &len);
	virtual int Write(const uint8_t *data,const uint8_t &len);
protected:
	virtual void SetBaudRate(const uint8_t &rate );
	virtual void SetDataBits(const uint8_t &data );
	virtual void SetParity(const uint8_t &parity);
	virtual void SetStopBits(const uint8_t &stop);
	virtual void SetFlowControl(const uint8_t &flow);
private:
	int m_fd;
#ifndef DLP_WINDOW
	struct termios m_uart2;
#endif // DLP_WINDOW
};

#endif // DLP_DRIVERS_CSERIAL_H_
