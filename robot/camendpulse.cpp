#include "camendpulse.h"

#include <string.h>

CAmendPulse::CAmendPulse()
{
    memset(m_counter,0,4);

}

CAmendPulse::~CAmendPulse()
{


}
/**
*
* return 0 NO amend
         1 need to amend
**/
int CAmendPulse::IsAmend(const DLPMotorPulse &type,const float &coder_angle)
{

    if(DLP_PULSE_NO<type&&DLP_PULSE_MAX>type)
    {

        uint16_t real_value=Angle2Pulses(type,coder_angle);
        uint16_t theory_value=Frames2Pulses(type);
        int16_t difference_value=GetAmendError(real_value,theory_value);;

        if(difference_value>5)
        {
            GetAmendTime(type,difference_value);
            GetAmendAngle(type,difference_value);
        }

        m_counter[type]=0;
        return 1;

    }
    //if not amend ,and continuing
    m_counter[type]++;
    return 0;
}



/**
*
*
*/
uint32_t CAmendPulse::Angle2Pulses(const DLPMotorPulse &type,const float &coder_angle)
{
    uint32_t pulses=0;

    if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
    {
        pulses=static_cast<uint32_t>(coder_angle/m_amend_attr[type].coder_unit_angle*m_amend_attr[type].coder_unit_pulse);
    }

    return pulses;
}



/**
*
*
*/
uint32_t CAmendPulse::Frames2Pulses(const DLPMotorPulse &type)
{
    uint32_t pulses=0;
    if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
    {
        for(int i=1;i<m_counter[type];i++)//notes i==1 start
        {
            pulses+=m_dev_pulses[type][i];
        }

    }

    return pulses;
}


/**
*
*
*/
int32_t CAmendPulse::GetAmendError(const uint32_t &theory_pulses,const uint32_t &real_pulses)
{
     return theory_pulses-real_pulses;
}


/**
*
*
*/
void CAmendPulse::GetAmendTime(const DLPMotorPulse &type,const int16_t &amend_error)
{
    uint32_t sum_time=0,amend_time;//////////////////////////////////////////////////////////
    if(DLP_PULSE_PAN==type)
    {
        amend_time=sum_time-m_counter[DLP_PULSE_PAN]*20;
        m_amend_time[DLP_PULSE_PAN][0]=amend_time&&0x00FF;
        m_amend_time[DLP_PULSE_PAN][1]=amend_time&&0xFF00;

    }

}


/**
*
*
*/
void CAmendPulse::GetAmendAngle(const DLPMotorPulse &type,const int16_t &amend_error)
{
    uint32_t sum_angle=0,amend_angle;//////////////////////////////////////////////////////////
    if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
    {
        amend_angle=sum_angle-m_counter[type]*20;
        m_amend_angle[type][0]=amend_angle&&0x00FF;
        m_amend_angle[type][1]=amend_angle&&0xFF00;

    }

}
////////////////////////////////////////////////////////////////////////////


/**
*
*
*/
void CAmendPulse::AmendParameter(const DLPMotorPulse &type,uint16_t *pcoder_data)
{
    if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
    {
        pcoder_data[0]=m_amend_angle[type][0];
        pcoder_data[1]=m_amend_angle[type][1];
        pcoder_data[2]=m_amend_time[type][0];
        pcoder_data[3]=m_amend_time[type][1];
    }


}


/**
*
*
*/
void CAmendPulse::SetMotrAttr(const DLPMotorPulse &type,const AmendAttr &attr)
{

}
