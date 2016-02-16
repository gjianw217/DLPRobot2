#include "cdevpulses.h"
#include <string.h>
#include "../utils/cdebug.h"

CDevPulses::CDevPulses()
{
    memset(m_dev_pulses, 0, sizeof(m_dev_pulses));
    m_counter=0;
}

CDevPulses::~CDevPulses()
{

}
int CDevPulses::ReadDevPulse(const DLPMotorPulse &type,const uint8_t &pos)
{
    if(check_para(type,pos))
        return m_dev_pulses[type][pos];
    else
        return -1;

}

void     CDevPulses::WriteDevPulse(const DLPMotorPulse &type,const uint8_t &pos,const uint32_t &value)
{
   if(check_para(type,pos))
   {
        m_dev_pulses[type][pos]=value;
   }
}

void     CDevPulses::ReadDevPulsesCurve(const DLPMotorPulse &type,const uint8_t &len,uint32_t *des)
{
    dlp_log(DLP_LOG_DEBUG," CDevPulses::ReadDevPulsesCurve");
    if(check_para(type,len))
    {
        int i,j;
        for(i=0;i<len;i++)
        {
            des[i]=m_dev_pulses[type][i];

        }

    }
}

void     CDevPulses::WriteDevPulsesCurve(const DLPMotorPulse &type,const uint8_t &len,const uint32_t *src)
{
    dlp_log(DLP_LOG_DEBUG," CDevPulses::WriteDevPulsesCurve");

    if(check_para(type,len))
    {
        int i,j;
        for(i=0;i<len;i++)
        {
            m_dev_pulses[type][i]=src[i];
            #ifdef DLP_DEBUG
            std::cout<<"CDevPulses::ReadDevPulsesCurve"<<m_dev_pulses[type][i]<<std::endl;
            #endif // DLP_DEBUG
//            std::cout<<"CDevPulses::WriteDevPulsesCurve"<<m_dev_pulses[type][i]<<std::endl;

        }
    }
}

/**
*
*
*/
void CDevPulses::ReadPulseGroup(uint32_t *des)
{
    dlp_log(DLP_LOG_DEBUG,"CDevPulses::ReadPulseGroup");
    if(des!=NULL)
    {
        if(m_dev_pulses[DLP_PULSE_PAN][m_counter]>0)//PanDevPulses=0
        {
            des[2]=1;
            des[3]=m_dev_pulses[DLP_PULSE_PAN][m_counter];
        }
        if(m_dev_pulses[DLP_PULSE_TILT][m_counter]>0)//TiltDevPulses=1
        {
            des[0]=1;
            des[1]=m_dev_pulses[DLP_PULSE_TILT][m_counter];
        }
        if(m_dev_pulses[DLP_PULSE_ZOOM][m_counter]>0) //FocusDevPulses=2
        {
            des[4]=1;
            des[5]=m_dev_pulses[DLP_PULSE_ZOOM][m_counter];
        }
        if(m_dev_pulses[DLP_PULSE_FOCUS][m_counter]>0) //ZoomDevPulses=3
        {
            des[6]=1;
            des[7]=m_dev_pulses[DLP_PULSE_FOCUS][m_counter];
        }

         m_counter++;
    }
    else
    {
        dlp_log(DLP_LOG_ERR,"CDevPulses::ReadPulseGroup ERROR ......");
    }

}

int      CDevPulses::check_para(const DLPMotorPulse &type,const uint8_t pos_or_len)
{
    if((type>DLP_PULSE_NO)&&(type<DLP_PULSE_MAX)&&(pos_or_len>1)&&(pos_or_len<DLP_MAX_PULSES))
     {
        return 1;
     }
    else
    {
        #ifdef DLP_DEBUG
        std::cout<<"check_para: "<<type<<":"<<pos_or_len<<std::endl;
        printf(" check_para %d,len %d\n",type,pos_or_len);
        #endif // DLP_DEBUG
        return 0;
    }



}

void CDevPulses::ResetCounter()
{
    m_counter=0;

}
