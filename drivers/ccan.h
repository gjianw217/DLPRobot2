
/*
* @file   ccan.h
* @brief  Encapsulation Beaglebone CAN protocol interfaces
* @author GuoJianwei & gjianw217@163.com
* @see        https://www.kernel.org/doc/Documentation/networking/can.txt
*/
#ifndef DLP_DRIVERS_CCAN_H_
#define DLP_DRIVERS_CCAN_H_

#include <fcntl.h>
#include <string>
#include <cstring>  //strcpy
#include "../dlp/dlp.h"

class CCAN
{
public:
	explicit CCAN(const uint8_t &id);
	~CCAN();
	int CANGetData(uint16_t *data);
	int CANPollIDs(uint16_t *ids);
	int CANSetBaudrate(const uint16_t &high_rate,const uint16_t &low_rate);
	int CANSetID(const uint16_t &id);
private:
	int Init();
protected:
#ifndef DLP_WINDOW
	struct sockaddr_can m_addr_can;
	struct ifreq        m_ifr_can;
	struct can_frame    m_frame_can;
#endif // DLP_WINDOW
	uint8_t             m_id;
	int                 m_sock_can;
	std::string         m_name_can; /*<define the CAN interface name like as can0*/
};
#endif //DLP_DRIVERS_CCAN_H_
