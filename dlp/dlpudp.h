/*
* @file   头文件
* @brief  自定义与UDP通信相关的枚举，结构体
* @author GuoJianwei & gjianw217@163.com
*/
#ifndef DLP_COMMON_DLPUDP_H_
#define DLP_COMMON_DLPUDP_H_

typedef enum {
	UDP_SEARCH=1,
	UDP_REPLY=2,
	UDP_RESET=3,
	UDP_RESET_SUCCESS=4,
	UDP_RESET_FAILURE=5,
	UDP_NO=-1,

}DLPUdpCmd;


typedef struct
{
	//.unsigned char ptz_mac[6];//xx-xx-xx-xx-xx-xx
	//unsigned char ptz_ip[4]; //xxx.xxx.xxx.xxx
	unsigned char ptz_mac[12];//xx-xx-xx-xx-xx-xx\0  0-ff
    unsigned char ptz_ip[8]; //xxx.xxx.xxx.xxx\0     0-255
	unsigned int ptz_port;
	unsigned char	ptz_id;
	char ptz_name[10];
	DLPUdpCmd cmd;
}DLPUdpInfo;

#endif // DLP_COMMON_DLPUDP_H_


