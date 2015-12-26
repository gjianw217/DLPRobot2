#include "cserialboost.h"
#include <cerrno>
#include <iostream>
#include <boost/asio/serial_port.hpp>
#include <boost/bind.hpp>

CSerialBoost::CSerialBoost()
{
	m_sp=new boost::asio::serial_port(m_ios);
}


CSerialBoost::~CSerialBoost()
{
	if(m_sp)
	{
		delete m_sp;
		m_sp=NULL;
	}
}


int CSerialBoost::Open(const char *com)
{
	if (com!=NULL)
	{
		m_sp->open(com,m_ec);
	}

	if(0!=m_ec.value())//permission_denied
	{
		std::cout<<"m_sp->open(com,m_ec)"<<m_ec.message()<<":"<<m_ec.value()<<std::endl;
		m_sp=NULL;
	}
	
	return 0;
}

void CSerialBoost::Config(const uint8_t &baudrate,const uint8_t &databit,const uint8_t &parity,const uint8_t &stopbit)
{

	if(m_sp==NULL) return ;

	SetRate(baudrate);
	SetDataBits(databit);
	SetParity(parity);
	SetStopBits(stopbit);
	SetFlowControl(0);

}

int CSerialBoost::Read(uint8_t *data,const uint8_t &len)
{
	if(NULL==m_sp) return -1;

	return m_sp->read_some(boost::asio::buffer(data,len),m_ec);
}

int CSerialBoost::Write(const uint8_t *data,const uint8_t &len)
{
	if(NULL==m_sp) return -1;

	return m_sp->write_some(boost::asio::buffer(data,len),m_ec);;

}

void CSerialBoost::Run()
{
	m_ios.run();
}

/************************************************************************
*                               *
************************************************************************/
void CSerialBoost::SetRate(const uint8_t &rate)
{
    if(NULL==m_sp) return ;
	switch(rate)
	{
	case BR2400:m_sp->set_option(boost::asio::serial_port::baud_rate(2400));break;
	case BR4800:m_sp->set_option(boost::asio::serial_port::baud_rate(4800));break;
	case BR9600:m_sp->set_option(boost::asio::serial_port::baud_rate(9600));break;
	case BR19200:m_sp->set_option(boost::asio::serial_port::baud_rate(19200));break;
	case BR57600:m_sp->set_option(boost::asio::serial_port::baud_rate(57600));break;
	default:
	case BR115200:m_sp->set_option(boost::asio::serial_port::baud_rate(115200));break;

	}
}
void CSerialBoost::SetDataBits(const uint8_t &data )
{
    if(NULL==m_sp) return ;
	m_sp->set_option(boost::asio::serial_port::character_size(data));
}

void CSerialBoost::SetParity(const uint8_t &parity)
{
    if(NULL==m_sp) return ;
	switch(parity)
	{
	default:
	case 0:m_sp->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));break;
	case 1:m_sp->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::odd));break;
	case 2:m_sp->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::even));break;

	}

}

void CSerialBoost::SetStopBits(const uint8_t &stop)
{
    if(NULL==m_sp) return ;
	switch(stop)
	{
	default:
	case 0:m_sp->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));break;
	case 1:m_sp->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::onepointfive));break;
	case 2:m_sp->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::two ));break;
	}
}

void CSerialBoost::SetFlowControl(const uint8_t &flow)
{
    if(NULL==m_sp) return ;
	enum flowcontroltype {none,software,hardware};
	switch(flow)
	{
	default:
	case 0:m_sp->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));break;
	case 1:m_sp->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::software));break;
	case 2:m_sp->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::hardware));break;
	}
}

/***********************************************************************************
************************************************************************************
************************************************************************************/
//int CSerialBoost::AsyncRead(uint8_t *data,const uint8_t &len,const uint16_t &timeout)
//{
//	boost::asio::deadline_timer timer(m_ios);
//	m_sp->async_read_some(boost::asio::buffer(data,len),
//		boost::bind(&CSerialBoost::HandleARead,this,data,_1, _2));
//	timer.expires_from_now(boost::posix_time::millisec(timeout));
//	timer.async_wait(boost::bind(&boost::asio::serial_port::cancel, boost::ref(m_sp)));
//	return 0;
//}
//
//
//int CSerialBoost::AsyncWrite(const uint8_t *data,const uint8_t &len,const uint16_t &timeout)
//{
//	boost::asio::deadline_timer timer(m_ios);
//	m_sp->async_write_some(boost::asio::buffer(data,len),
//		boost::bind(&CSerialBoost::HandleAWrite,this,data,_1, _2));
//	timer.expires_from_now(boost::posix_time::millisec(timeout));
//	timer.async_wait(boost::bind(&boost::asio::serial_port::cancel, boost::ref(m_sp)));
//	return 0;
//}
//
//void CSerialBoost::HandleARead(uint8_t *data,boost::system::error_code ec,std::size_t bytes_transferred)
//{
//	std::cout<<"HandleARead:"<<std::endl;
//	//std::cout.write(data, bytes_transferred);
//
//
//}
//void CSerialBoost::HandleAWrite(const uint8_t *data,boost::system::error_code ec,std::size_t bytes_transferred)
//{
//	std::cout<<"HandleAWrite:"<<std::endl;
//	//std::cout.write(data, bytes_transferred);
//}












