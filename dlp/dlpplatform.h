#ifndef DLP_DLP_DLPPLATFORM_H_
#define DLP_DLP_DLPPLATFORM_H_

#include <iostream>
#include <string>

#ifdef DLP_WINDOW
//#include <windows.h>
#include <ctime>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"WS2_32.lib")
#define  close closesocket
typedef int socklen_t;
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <netinet/in.h>
#include <net/if.h> //struct ifreq
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h> //ioctl
#include <unistd.h>//close() sleep()
#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#endif // DLP_WINDOW

#ifndef DLP_WINDOW

#endif // DLP_WINDOW

#ifdef DLP_WINDOW
#define FOCUSPORT "COM19" //保证该串口存在
#define ZOOMPORT  "COM18"
#endif

#ifdef DLP_LINUX
#define FOCUSPORT "/dev/ttyS0"
#define  ZOOMPORT "/dev/ttyS1"
#endif

#ifdef DLP_ARM_LINUX
#define FOCUSPORT "/dev/ttyO2"
#define  ZOOMPORT "/dev/ttyO4"
#endif

#endif // DLP_DLP_DLPPLATFORM_H_
