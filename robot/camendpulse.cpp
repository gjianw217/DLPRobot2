#include "camendpulse.h"
#include "../utils/cconverter.h"
#include <string.h>
#include <cmath>

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

    if(DLP_PULSE_NO<type&&type<DLP_PULSE_MAX)
    {

        uint16_t real_value=Angle2Pulses(type,coder_angle);
        uint16_t theory_value=Frames2Pulses(type);
        int16_t difference_value=GetAmendError(real_value,theory_value);;
        printf("real %d,theory %d,diff %d\n",real_value,theory_value,difference_value);

        if(difference_value>5)
        {
            GetAmendTime(type,difference_value);
            GetAmendAngle(type,difference_value);
            m_counter[type]=0;
            return 1;
        }



    }
    //if not amend ,and continuing
    m_counter[type]++;//
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
    uint32_t sum_time,amend_time;
    if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)

    {
        amend_time=static_cast<uint32_t>(sum_time*1000)-m_counter[type]*20; //unit==ms
        m_amend_time[type][0]=amend_time%1000;
        m_amend_time[type][1]=amend_time/1000;

    }

}


/**
*
*
*/
void CAmendPulse::GetAmendAngle(const DLPMotorPulse &type,const int16_t &amend_error)
{
    uint32_t sum_angle;//////////////////////////////////////////////////////////
    float amend_angle;

    if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
    {
        amend_angle=m_init_angle[type]+amend_error*m_amend_attr[type].coder_gear_rate/m_amend_attr[type].motor_gear_rate;
        m_amend_angle[type][1]=static_cast<uint16_t>(amend_angle);
        m_amend_angle[type][0]=(amend_angle-m_amend_angle[type][1])*1000;//0.001 degree

    }

}
////////////////////////////////////////////////////////////////////////////


/**
*
*
*/
void CAmendPulse::GetAmendParameter(const DLPMotorPulse &type,uint16_t *pcoder_data)
{
    if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
    {
        pcoder_data[0]=m_amend_angle[type][0];
        pcoder_data[1]=m_amend_angle[type][1];
        pcoder_data[2]=m_amend_time[type][0];
        pcoder_data[3]=m_amend_time[type][1];
    }


}

void CAmendPulse::SetAmendParameter(const DLPMotorPulse &type,uint16_t *time_angle)
{
     if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
    {
        m_init_angle[type]=static_cast<float>(time_angle[1]/time_angle[0]);
        m_init_time[type] =static_cast<float>(time_angle[3]/time_angle[2]);;
    }


}

/**
*
*
*/

void CAmendPulse::SetAmendAttr(const DLPMotorPulse &type,const DLPMotorAttr &mattr,const DLPEncoderAttr &eattr)
{
     if(type>DLP_PULSE_NO&&type<DLP_PULSE_MAX)
     {

        m_amend_attr[type].coder_gear_rate=eattr.dlp_gear[1]/eattr.dlp_gear[0];;
        m_amend_attr[type].coder_unit_angle=360/(pow(2,eattr.dlp_bits)-1);
        m_amend_attr[type].coder_unit_pulse=16;
        m_amend_attr[type].motor_gear_rate=mattr.dlp_algorithm.g.gear[1]/mattr.dlp_algorithm.g.gear[0];
        m_amend_attr[type].motor_speed=mattr.dlp_algorithm.g.max_speed;
        m_amend_attr[type].step_angle=division2angle(ratio2division(mattr.dlp_algorithm.g.division));

     }
}
