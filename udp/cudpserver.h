#ifndef DLP_UDP_CUDPSERVER_H_
#define DLP_UDP_CUDPSERVER_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
using boost::asio::ip::udp;

class CUDPServer
{
public:
	CUDPServer(const uint16_t &port);
	~CUDPServer();
	void Init();
	virtual int SendTo(const char *data,const std::size_t &len);
	virtual int RecvFrom(char *data,const std::size_t &len);
private:
	boost::asio::io_service m_ios;
	boost::asio::ip::udp::socket *m_sock;
	boost::asio::ip::udp::endpoint m_ep;
	boost::system::error_code m_error;
};
#endif //DLP_UDP_CUDPSERVER_H_



