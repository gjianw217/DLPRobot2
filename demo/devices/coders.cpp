#include "../../devices/encoder/crs485coder.h"
#include "../../utils/cdebug.h"
#include "../../dlp/dlp.h"
#include "string.h"
#include "../../utils/cdelay.h"

#define COM2 "/dev/ttyO2"
#define COM4 "/dev/ttyO4"

#ifndef DLP_WINDOW
struct  timeval last_tv;
struct  timeval last_tz;
struct  timeval  this_tv;
struct  timezone this_tz;
#endif // DLP_WINDOW


void TestRS485Coder(void)
{
    int times=1;
	DLPEncoderAttr attr;
	uint16_t data[10]={0};
	attr.dlp_bits=16;
	attr.dlp_id=2;
	attr.dlp_role=DLP_FOCUS;
    //attr.dlp_serial.baudrate=0;//2400
	//attr.dlp_serial.baudrate=3;//19200
	//attr.dlp_serial.baudrate=5;//57600
	attr.dlp_serial.baudrate=6;//115200

	attr.dlp_serial.databit=8;
	attr.dlp_serial.parity=0;
	attr.dlp_serial.stop=1;//1

    dlp_log(DLP_LOG_DEBUG,"TestRS485Coder");
    PCRS485Coder pcoder(new CRS485Coder(COM2));
    pcoder->Config(attr);

    dlp_log(DLP_LOG_DEBUG,"Starting....");
	do
	{
		memset(data,0,10);
		std::cout<<times++<<std::endl;
		pcoder->GetData(data);//
		printf("%x,%x,%x,%x,%x\n",data[0],data[1],data[2],data[3],data[4]);
		//coder.PollID(data);
		#ifndef DLP_WINDOW
//        gettimeofday(&this_tv,&this_tz);
//        printf("tv_interval:%d sec and :%d us\n",this_tv.tv_sec-last_tv.tv_sec,this_tv.tv_usec-last_tv.tv_usec);
//        last_tv=this_tv;
        #endif // DLP_WINDOW
		delays(5);

	} while (1);
}
