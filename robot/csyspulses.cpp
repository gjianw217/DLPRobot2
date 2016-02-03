#include "csyspulses.h"
#include <string.h>
#include "../drivers/cpru.h"
#include "../drivers/cpwm.h"
#include "../utils/cdebug.h"
/*Run the equipment of pulse*/
CSysPulses::CSysPulses()
{
    m_ppru=PCPRU(new CPRU("pru1"));
    m_ppwm=PCPWM(new CPWM("P8_45.11"));
    memset(m_pulses,0,8);
}

CSysPulses::~CSysPulses()
{

}
/*pos
1 pan
3 tilt
5 focus
6 zoom
*/
uint32_t CSysPulses::ReadPulse(const uint8_t &pos)
{
    return m_pulses[pos];
}

void     CSysPulses::WritePulse(const uint8_t &pos,const uint32_t &value)
{
    //m_motor_counter[pos] = value;
    m_pulses[pos]=value;

}

void     CSysPulses::ReadPulseGroup(uint32_t *des,const uint8_t &len)
{
    if((len>=0)&&(len<=8)&&(des!=NULL))
    {
        int i;
        for(i=0;i<len;i++)
        {
            des[i]=m_pulses[i];
        }

    }
}

void  CSysPulses::WritePulseGroup(const uint32_t *src,const uint8_t &len)
{
    dlp_log(DLP_LOG_DEBUG,"CSysPulses::WritePulseGroup");
    if((len>=0)&&(len<=8)&&(src!=NULL))
    {

        for(int i=0;i<len;i++)
        {
            m_pulses[i]=src[i];
            #ifdef DLP_DEBUG
             std::cout<<"[msg]  CSysPulses::WritePulseGroup Cmd Group "<<m_pulses[i]<<std::endl;
            #endif // DLP_DEBUG

            //std::cout<<src[i]<<std::endl;

        }
    }

}


void CSysPulses::RunPulseGroups()
{
    dlp_log(DLP_LOG_DEBUG," CSysPulses::RunPulseGroups()");
    uint32_t my_period=1000000000/m_pulses[3];
    m_ppwm->SetDuty(my_period/2);
    m_ppwm->SetPeriod(my_period);
    std::cout<<"Setting New Period: "<<my_period<<std::endl;
    m_ppru->Run(m_pulses);
}
