#include "ccan.h"
#include <assert.h>
#include "../utils/cdebug.h"

CCAN::CCAN(const uint8_t &id)
{
	this->m_name_can="can0";
	this->m_id=id;
	Init();
}
CCAN::~CCAN()
{

}
int CCAN::CANGetData(uint16_t *data)
{
	assert(NULL!=data);
	//std::cout<<"CAN"<<std::endl;
#ifdef DLP_ARM_LINUX
    int nbytes;
    bool finished=true;
    struct can_filter rfilter[1];
    m_frame_can.can_id =0x0200|m_id;
    m_frame_can.can_dlc=2;
    m_frame_can.data[0]=0x01;
    m_frame_can.data[1]=m_id;

    nbytes=write(m_sock_can,&m_frame_can,sizeof(struct can_frame));

//    do{
        /*Set the filter*////<received_can_id> & mask == can_id & mask
        rfilter[0].can_id   =0x0100|m_id;
        rfilter[0].can_mask =CAN_SFF_MASK;
        setsockopt(m_sock_can, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
        /*ready to receive*/
    do{ //Filtering rules above failure, therefore adding manual filtering
        memset(&m_frame_can,0,sizeof(m_frame_can));
        nbytes=read(m_sock_can,&m_frame_can,sizeof(struct can_frame));
        //dlp_logs("m_frame_can.can_dlc",m_frame_can.can_dlc);
        //dlp_logs("m_frame_can.can_id",m_frame_can.can_id,true);
        if(nbytes<0)
        {
            dlp_log(DLP_LOG_ERR,"can read failed");
           // return DLP_FAILURE;
            return -1;
        }
        //Filter the send command set
        else if(8==m_frame_can.can_dlc&&rfilter[0].can_id==m_frame_can.can_id)
        {

            data[0]=m_frame_can.data[1];
            data[0]=data[0]<<8|m_frame_can.data[0];
            data[1]=0;

            finished=false;
        }

    }while(finished);

#endif // DLP_BBB
   // return DLP_SUCCESS;
	return 0;
}
int CCAN::CANPollIDs(uint16_t *ids)
{
	return 0;
}
int CCAN::CANSetBaudrate(const uint16_t &high_rate,const uint16_t &low_rate)
{
	return 0;
}
int CCAN::CANSetID(const uint16_t &id)
{
	return 0;
}

int CCAN::Init()
{

#ifdef DLP_ARM_LINUX
    this->m_sock_can=socket(PF_CAN,SOCK_RAW,CAN_RAW);

    if(this->m_sock_can<0)
    {
        return -1;
    }

    strcpy(this->m_ifr_can.ifr_name,this->m_name_can.c_str());//specify can0 equipment
    //strcpy(ifr_can_.ifr_name,"can0");//
    ioctl(this->m_sock_can,SIOCGIFINDEX,&this->m_ifr_can);
    this->m_addr_can.can_family = AF_CAN;
    this->m_addr_can.can_ifindex = this->m_ifr_can.ifr_ifindex;

    if(bind(this->m_sock_can,(struct sockaddr *) &this->m_addr_can,sizeof(this->m_addr_can))<0)  //bind the socket and can0
    {
        return -2;
    }
    //std::cout<<"socket init CanCoder::start"<<std::endl;
#endif // DLP_ARM_LINUX
    return 0;
}
