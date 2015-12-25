#include "../../utils/cdebug.h"
#include "../../robot/cconfig.h"
#include "../../network/cdata-mapping.h"
#include "../../robot/crobot.h"
#include "../../devices/encoder/iencoder.h"

#include "../../devices/motors/cstepmotorbypwm.h"
#include "../../devices/motors/cstepmotorbypru.h"
#include "../../utils/cdelay.h"


void TestRobotInit()
{
	dlp_log(DLP_LOG_DEBUG,"TestRobotInit");
	uint16_t data[8]={0};
	uint16_t angle=360,dir=1;
	DLPRole role;
	PIEncoder pcoder;
    PIMotor pmotor;
	PCConfig pconfig(new CConfig);
	pconfig->Init();                                             //generate the configuration data
	dlp_log(DLP_LOG_DEBUG,"CConfig");
	PCDataMapping pdatamapping(new CDataMapping(pconfig));       //generate the mapping data object
	dlp_log(DLP_LOG_DEBUG,"CDataMapping");
	PCRobot probot(new CRobot(pdatamapping));

	probot->Init();                                              //robot create the devices
    dlp_log(DLP_LOG_DEBUG,"CRobotInit");
    while(1);
//	role=DLP_FOCUS;
//    pcoder=probot->GetCoder(role);
//	if(pcoder.use_count()!=0)
//	{
//		dlp_log(DLP_LOG_DEBUG,"TestRobotInit  ");
//
//	}
//    while(1)
//    {
//        static uint32_t times=0;
//        dlp_log_value(DLP_LOG_DEBUG,"TestRobotInit DLP_FOCUS Coder times",times++);
//        pcoder->GetData(data);
//        printf("%d,%d,%d,%d,%d,%d,%d,%d\n",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
//        delays(30);
//
//    }
//    pmotor=probot->GetMotor(role);
//	if(pmotor.use_count()!=0)
//	{
//        dlp_log(DLP_LOG_DEBUG,"TestRobotInit DLP_FOCUS Motor");
//        pmotor->RunbyAngle(angle,dir);
//	}
//	else
//	{
//        dlp_log(DLP_LOG_DEBUG,"TestRobotInit DLP_FOCUS Motor Failure");
//	}
//
//    while(1)
//    {
//        dlp_log(DLP_LOG_DEBUG,"TestRobotInit DLP_FOCUS Motor");
//        pmotor->RunbyAngle(angle,dir);
//
//        delays(12);
//
//    }


//    role=DLP_PAN;
//    pcoder=probot->GetCoder(role);
//	if(pcoder.use_count()!=0)
//	{
//		dlp_log(DLP_LOG_DEBUG,"TestRobotInit DLP_PAN Coder");
//        pcoder->GetData(data);
//	}
//    pmotor=probot->GetMotor(role);
//	if(pmotor.use_count()!=0)
//	{
//        dlp_log(DLP_LOG_DEBUG,"TestRobotInit DLP_PAN Motor");
//        pmotor->RunbyAngle(angle,dir);
//	}
//
//    while(1)
//    {
//        static uint32_t times=0;
//        dlp_log_value(DLP_LOG_DEBUG,"TestRobotInit DLP_PAN Motor times",times++);
//        pmotor->RunbyAngle(angle,dir);
//
//        delays(100);
//
//    }

}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/time.h>
#include <linux/input.h>

#define  KEYDEVICE  "/dev/input/event1"
void SolvePTZUnsmoothWay1(void)
{
	dlp_log(DLP_LOG_DEBUG,"TestRobotInit");
	uint16_t data[8]={0};
	uint16_t angle=360,dir=1;
	DLPRole role;
    PIMotor pmotor;
	PCConfig pconfig(new CConfig);
	pconfig->Init();                                             //generate the configuration data
	dlp_log(DLP_LOG_DEBUG,"CConfig");
	PCDataMapping pdatamapping(new CDataMapping(pconfig));       //generate the mapping data object
	dlp_log(DLP_LOG_DEBUG,"CDataMapping");
	PCRobot probot(new CRobot(pdatamapping));
	probot->Init();                                              //robot create the devices
    dlp_log(DLP_LOG_DEBUG,"CRobotInit");

    role=DLP_PAN;
    pmotor=probot->GetMotor(role);
	if(pmotor.use_count()==0)
	{
        dlp_log(DLP_LOG_DEBUG,"TestRobotInit Not DLP_PAN Motor");
        return;
	}

    int fd=0;//
    int ret =0;
    long times=1;
    struct input_event event;
    fd_set readfd;


    fd = open(KEYDEVICE, O_RDONLY);
    if(fd<0) return ;
    while(1)
    {
        //printf("Starting %ld\n",times);
        FD_ZERO(&readfd);
        FD_SET(fd,&readfd);
        //ret=select(m_fd+1,&readfd,NULL,NULL,&timeout);
        ret=select(fd+1,&readfd,NULL,NULL,NULL);
        if(FD_ISSET(fd,&readfd))
        {
           // printf("PressKey code  Read before %ld\n",times++);
            ret=read(fd, &event, sizeof(event));
            if (ret !=  sizeof(struct input_event))
            {
                continue;
            }

            else
            {
                printf("PressKey code  is %d value is %d \n",event.code,event.value);
                pmotor->RunbyAngle(angle,dir);
            }

        }
    }
    close(fd);
}

PIMotor pmotor;
PIEncoder pcoder;
uint32_t periodN=976;
uint32_t pulseN=4;
uint16_t data[8]={0};

void mysignal_fun(int signum)
{
   // dlp_log(DLP_LOG_DEBUG,"mysignal_fun");
	if(pmotor.use_count()==0)
	{
        DLPRole role=DLP_PAN;;
        PCConfig pconfig(new CConfig);
        pconfig->Init();
        PCDataMapping pdatamapping(new CDataMapping(pconfig));
        PCRobot probot(new CRobot(pdatamapping));
        probot->Init();
        pmotor=probot->GetMotor(role);
        dlp_log(DLP_LOG_DEBUG,"pmotor.use_count()==0)");
        role=DLP_PAN;
        pcoder=probot->GetCoder(role);
	}
    pmotor->RunbyAngle(periodN,pulseN);
    pcoder->GetData(data);
    printf("%d,%d,%d,%d,%d,%d,%d,%d\n",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
}

void SolvePTZUnsmoothWay2(void)
{
    int fd;
    int flag;
    int setting;
    int period=19531;

    signal(SIGIO,mysignal_fun);
    fd = open("/dev/gpiop923",O_RDWR);

    if (fd < 0)
    {

        printf("open error\n");
        return;
    }

    /* F_SETOWN:  Set the process ID
     *  告诉内核，发给谁
     */
    fcntl(fd, F_SETOWN, getpid());

    /*  F_GETFL :Read the file status flags
     *  读出当前文件的状态
     */
    flag = fcntl(fd,F_GETFL);

    /* F_SETFL: Set the file status flags to the value specified by arg
     * int fcntl(int fd, int cmd, long arg);
     * 修改当前文件的状态，添加异步通知功能
     */
    fcntl(fd,F_SETFL,flag | FASYNC);
    dlp_log(DLP_LOG_DEBUG,"TestRobotInit");
    while(1)
    {
        /* 为了测试，主函数里，什么也不做 */
        //sleep(1000);

        std::cout<<"period:"<<period<<"(ns) pulse:"<<pulseN<<std::endl;

        std::cout<<"please input setting:<-------0::period------>"<<std::endl
                 <<"                     <-------1::pulseN------>"<<std::endl;
        std::cin>>setting;
        if(0==setting)
        {
            std::cin>>period;
            periodN=50*period/1000;
            if(periodN<0) periodN=976;
        }
        else if(1==setting)
        {
            std::cin>>pulseN;
        }
        else
        {
            std::cout<<"input error"<<std::endl;
        }

    }

}




void SolvePTZUnsmoothWay3(void)
{
	dlp_log(DLP_LOG_DEBUG,"TestRobotInit");
	uint16_t data[8]={0};
	uint16_t angle=360,dir=1;
	DLPRole role;
    PIMotor pmotor;
	PCConfig pconfig(new CConfig);
	pconfig->Init();                                             //generate the configuration data
	dlp_log(DLP_LOG_DEBUG,"CConfig");
	PCDataMapping pdatamapping(new CDataMapping(pconfig));       //generate the mapping data object
	dlp_log(DLP_LOG_DEBUG,"CDataMapping");
	PCRobot probot(new CRobot(pdatamapping));
	probot->Init();                                              //robot create the devices
    dlp_log(DLP_LOG_DEBUG,"CRobotInit");

    role=DLP_PAN;
    pmotor=probot->GetMotor(role);
	if(pmotor.use_count()==0)
	{
        dlp_log(DLP_LOG_DEBUG,"TestRobotInit Not DLP_PAN Motor");
        return;
	}

    int fd=0;//
    int ret =0;
    long times=1;
    struct input_event event;
    fd_set readfd;


    fd = open("/dev/gpiop923", O_RDONLY);
    if(fd<0) return ;
    while(1)
    {
        //printf("Starting %ld\n",times);
        FD_ZERO(&readfd);
        FD_SET(fd,&readfd);
        //ret=select(m_fd+1,&readfd,NULL,NULL,&timeout);
        ret=select(fd+1,&readfd,NULL,NULL,NULL);
        {
             if(FD_ISSET(fd,&readfd))
            {

                pmotor->RunbyAngle(angle,dir);
            }

        }

    }
    close(fd);
}
































// sudo apt-get install build-essential lzop libncurses5-dev libssl-dev

// sudo apt-get install libc6:i386    # 如果使用的是 64 位的 Ubuntu，还需要安装：

// make fireprime-linux_defconfig ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/arm-eabi-4.6/bin/arm-eabi-
// make -j8 rk3128-fireprime.img ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/arm-eabi-4.6/bin/arm-eabi-
//make modules ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/arm-eabi-4.6/bin/arm-eabi-
//mkdir modules_install
//make INSTALL_MOD_PATH=./modules_install modules_install ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/arm-eabi-4.6/bin/arm-eabi-


//make fireprime-linux_defconfig ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-
//make -j8 rk3128-fireprime.img ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-
//make modules ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-
//mkdir modules_install
//make INSTALL_MOD_PATH=./modules_install modules_install ARCH=arm CROSS_COMPILE=/home/dlp/develop/toolchain/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-
