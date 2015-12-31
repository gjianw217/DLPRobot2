#include "csyspulses.h"
#include <string.h>
#include "../drivers/cpru.h"

/*Run the equipment of pulse*/
CSysPulses::CSysPulses()
{
    m_ppru=PCPRU(new CPRU("pru1"));
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

void     CSysPulses::WritePulseGroup(const uint32_t *src,const uint8_t &len)
{
    if((len>=0)&&(len<=8)&&(src!=NULL))
    {
        int i;
        for(i=0;i<len;i++)
        {
            m_pulses[i]=src[i];

        }

    }

}


void CSysPulses::RunPulseGroups()
{
    m_ppru->Run(m_pulses);
}