#include "cmanagepulse.h"
#include "csyspulses.h"
#include "cdevpulses.h"
#include "camendpulse.h"


CManagePulse::CManagePulse()
{
    m_psys_pulses=PCSysPulses(new CSysPulses());
    m_pdev_pulses=PCDevPulses(new CDevPulses());
    m_pamend_pulses=PCAmendPulse(new CAmendPulse());

    m_pulse[0].angle_pulse_frame_counter=0;
    m_pulse[0].cmd_convert_curve_enable=1;
    m_pulse[0].angle_pulse_frame_sum=0;

    m_pulse[1].angle_pulse_frame_counter=0;
    m_pulse[1].cmd_convert_curve_enable=1;
    m_pulse[1].angle_pulse_frame_sum=0;


    m_pulse[2].angle_pulse_frame_counter=0;
    m_pulse[2].cmd_convert_curve_enable=1;
    m_pulse[2].angle_pulse_frame_sum=0;


    m_pulse[3].angle_pulse_frame_counter=0;
    m_pulse[3].cmd_convert_curve_enable=1;
    m_pulse[3].angle_pulse_frame_sum=0;

}

CManagePulse::~CManagePulse()
{


}

int CManagePulse::CheckCurveConvert(const DLPMotorPulse &type)
{
    if(m_pulse[type].cmd_convert_curve_enable==true)
        return 1;
    else
        return -1;
}

void CManagePulse::SetConvertDisable(const DLPMotorPulse &type)
{
    m_pulse[type].cmd_convert_curve_enable=0;
}
void CManagePulse::SetConvertEnable(const DLPMotorPulse &type)
{
    m_pulse[type].cmd_convert_curve_enable=true;
}



void CManagePulse::UpdateCurvePulse(const DLPMotorPulse &type,const uint8_t &len,const uint32_t *src) //convert the angle into pulse according to the curve type
{
    m_pdev_pulses->WriteDevPulsesCurve(type,len,src);
    m_pulse[type].angle_pulse_frame_sum=len;
}
//////////////////////////////////////////////////////////////////////////////////////////////
uint8_t CManagePulse::CheckMotorPulse()
{
    if(m_pulse[0].angle_pulse_frame_sum==0
       &&m_pulse[1].angle_pulse_frame_sum==0
       &&m_pulse[2].angle_pulse_frame_sum==0
       &&m_pulse[3].angle_pulse_frame_sum==0)
    {
        return 1;
    }
    else
        return 0;
}


void CManagePulse::UpdatePulseGroup()
{
    int pos;
    int i;
    uint32_t pulse[100]={0};
    for(i=DLP_PULSE_PAN;i<DLP_PULSE_MAX;(i++))
    {
        if(pos=CheckCurveConvert(static_cast<DLPMotorPulse>(i))!=-1)
        {
            m_pdev_pulses->ReadPulseGroup(pos,pulse);
            m_psys_pulses->WritePulseGroup(pulse,8);
        }

        if(++m_pulse[i].angle_pulse_frame_counter==m_pulse[i].angle_pulse_frame_sum)//whether restarting a movement command
        {
            m_pulse[i].angle_pulse_frame_counter=0;
            m_pulse[i].cmd_convert_curve_enable=1;
        }

   }

}
void CManagePulse::RunPulseGoup()      //run the step motor
{
    m_psys_pulses->RunPulseGroups();
}


int CManagePulse::IsAmend(const DLPMotorPulse &type,const float &coder_angle)
{
    return m_pamend_pulses->IsAmend(type,coder_angle);
}

void CManagePulse::GetAmendParameter(const DLPMotorPulse &type,uint16_t *time_angle)
{
    m_pamend_pulses->AmendParameter(type,time_angle);

}

void CManagePulse::SetMotrAttr(const DLPMotorPulse &type,const AmendAttr &attr)
{
    m_pamend_pulses->SetMotrAttr(type,attr);

}
