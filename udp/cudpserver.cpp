#include "cudpserver.h"

CUDPServer::CUDPServer(const uint16_t &port)
	:m_ep(boost::asio::ip::udp::v4(),port)
{
	m_sock=new boost::asio::ip::udp::socket(m_ios,m_ep);
}
CUDPServer::~CUDPServer()
{
	if (m_sock)
	{
		delete m_sock;
		m_sock=NULL;
	}
}
void CUDPServer::Init()
{

}
int CUDPServer::SendTo(const char *data,const std::size_t &len)
{
	m_sock->send_to(boost::asio::buffer(data,len),m_ep,0,m_error);
	//if(m_error&&m_error!=boost::asio::error::message_size)
	//{
	//	throw boost::system::system_error(m_error);
	//}
	return 0;
}
int CUDPServer::RecvFrom(char *data,const std::size_t &len)
{


	size_t nLen = m_sock->receive_from(boost::asio::buffer(data,len),m_ep,0,m_error);
	//if(m_error&&m_error!=boost::asio::error::message_size)
	//{
	//	throw boost::system::system_error(m_error);
	//}
	//std::cout<<"recv from "<<m_ep.address()<<": "<<data<<std::endl;
	return nLen;
}