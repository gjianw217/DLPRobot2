#include "cudpclient.h"

CUDPClient::CUDPClient(const uint16_t &port)
	:m_ep(boost::asio::ip::address_v4::broadcast(),port)
{
	m_sock=new boost::asio::ip::udp::socket(m_ios);
}
CUDPClient::~CUDPClient()
{
	if (m_sock)
	{
		delete m_sock;
		m_sock=NULL;
	}
}

void CUDPClient::Init()
{
	m_sock->open(boost::asio::ip::udp::v4(),m_error);
	if(!m_error)
	{
		m_sock->set_option(boost::asio::ip::udp::socket::reuse_address(true));
		m_sock->set_option(boost::asio::socket_base::broadcast(true));
	}
}
int CUDPClient::SendTo(const char *data,const std::size_t &len)
{
	m_sock->send_to(boost::asio::buffer(data,len),m_ep,0,m_error);
	if(m_error&&m_error!=boost::asio::error::message_size)
	{
		throw boost::system::system_error(m_error);
	}
	return 0;
}
int CUDPClient::RecvFrom(char *data,const std::size_t &len)
{

	m_sock->receive_from(boost::asio::buffer(data,len),m_ep,0,m_error);
	if(m_error&&m_error!=boost::asio::error::message_size)
	{
		throw boost::system::system_error(m_error);
	}
	std::cout<<"recv from "<<m_ep.address()<<": "<<data<<std::endl;
	return 0;

}
