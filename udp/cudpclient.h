#ifndef DLP_UDP_CUDPCLIENT_H_
#define DLP_UDP_CUDPCLIENT_H_

#include <iostream>
#include <boost/asio.hpp>

class CUDPClient
{
public:
	CUDPClient(const uint16_t &port);
	~CUDPClient();
	void Init();
	int SendTo(const char *data,const std::size_t &len);
	int RecvFrom(char *data,const std::size_t &len);
private:
	boost::asio::io_service m_ios;
	boost::asio::ip::udp::socket *m_sock;
	boost::asio::ip::udp::endpoint m_ep;
	boost::system::error_code m_error;
};
#endif //DLP_UDP_CUDPCLIENT_H_
