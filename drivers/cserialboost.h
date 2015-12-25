/*
* @file   cserialboost.h
* @brief  Encapsulation serial interface in the Boost library ,
		  which is convenient to use on the Beaglebone platform
* @author GuoJianwei & gjianw217@163.com
* @note boost/asio/serial_port.hpp
*/

#ifndef DLP_DRIVERS_SERIAL_BOOST_H_
#define DLP_DRIVERS_SERIAL_BOOST_H_

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "iserial.h"

//typedef boost::function< void () > SerialFunc;
class CSerialBoost:public ISerial
{
public:
       //enum{BR2400=0,BR4800,BR9600,BR19200,BR38400,BR57600,BR115200,BR_NB= -1};
	   CSerialBoost();
	   ~CSerialBoost();
	   virtual int Open(const char *com);
	   virtual void Config(const uint8_t &baud,const uint8_t &databit,const uint8_t &parity,const uint8_t &stopbit);
	   virtual int Read(uint8_t *data,const uint8_t &len);
	   virtual int Write(const uint8_t *data,const uint8_t &len);
	   void Run();
	  // int AsyncRead(uint8_t *data,const uint8_t &len,const uint16_t &timeout);
	   //int AsyncWrite(const uint8_t *data,const uint8_t &len,const uint16_t &timeout);
protected:
    virtual void SetRate(const uint8_t &rate );
	virtual void SetDataBits(const uint8_t &data );
	virtual void SetParity(const uint8_t &parity);
	virtual void SetStopBits(const uint8_t &stop);
	virtual void SetFlowControl(const uint8_t &flow);
private:
	boost::asio::io_service m_ios;
	boost::asio::serial_port *m_sp;
	boost::system::error_code m_ec;
	//void HandleARead(uint8_t *data,boost::system::error_code ec,std::size_t bytes_transferred);
	//void HandleAWrite(const uint8_t *data,boost::system::error_code ec,std::size_t bytes_transferred);

};


#endif // DLP_DRIVERS_SERIAL_BOOST_H_
