#include "cmanagepulse.h"
#include "csyspulses.h"
#include "cdevpulses.h"
#include "camendpulse.h"
#include "../utils/cdebug.h"

CManagePulse::CManagePulse()
{
    m_psys_pulses=PCSysPulses(new CSysPulses());
    m_pdev_pulses=PCDevPulses(new CDevPulses());
    m_pamend_pulses=PCAmendPulse(new CAmendPulse());

    m_pulse[DLP_PULSE_PAN].angle_pulse_frame_counter=0;
    m_pulse[DLP_PULSE_PAN].cmd_convert_curve_enable=true;
    m_pulse[DLP_PULSE_PAN].angle_pulse_frame_sum=0;
    m_pulse[DLP_PULSE_PAN].angle_pulse_existence=false;

    m_pulse[DLP_PULSE_TILT].angle_pulse_frame_counter=0;
    m_pulse[DLP_PULSE_TILT].cmd_convert_curve_enable=true;
    m_pulse[DLP_PULSE_TILT].angle_pulse_frame_sum=0;
    m_pulse[DLP_PULSE_TILT].angle_pulse_existence=false;

    m_pulse[DLP_PULSE_ZOOM].angle_pulse_frame_counter=0;
    m_pulse[DLP_PULSE_ZOOM].cmd_convert_curve_enable=true;
    m_pulse[DLP_PULSE_ZOOM].angle_pulse_frame_sum=0;
    m_pulse[DLP_PULSE_ZOOM].angle_pulse_existence=false;

    m_pulse[DLP_PULSE_FOCUS].angle_pulse_frame_counter=0;
    m_pulse[DLP_PULSE_FOCUS].cmd_convert_curve_enable=true;
    m_pulse[DLP_PULSE_FOCUS].angle_pulse_frame_sum=0;
    m_pulse[DLP_PULSE_FOCUS].angle_pulse_existence=false;
}

CManagePulse::~CManagePulse()
{


}


///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief Check whether to convert the angle command
*
*/
int CManagePulse::IsConvert(const DLPMotorPulse &type)
{
    if(m_pulse[type].cmd_convert_curve_enable==true)
        return 1;
    else
        return 0;
}

/**
* @brief Save the curve pulse to the current management class
*
*/
void CManagePulse::UpdateCurvePulse(const DLPMotorPulse &type,const uint8_t &len,const uint32_t *src)
{
    m_pdev_pulses->WriteDevPulsesCurve(type,len,src);
    m_pulse[type].angle_pulse_frame_sum=len;
    m_pulse[type].angle_pulse_frame_counter=0;
    m_pulse[type].cmd_convert_curve_enable=false;
    m_pulse[type].angle_pulse_existence=true;

}
///////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief Check whether to execute the pulse
* @return  1:yes
*          0:no
*/
int CManagePulse::IsPulses(void)
{
    if(m_pulse[DLP_PULSE_PAN].angle_pulse_existence==false
       &&m_pulse[DLP_PULSE_TILT].angle_pulse_existence==false
       &&m_pulse[DLP_PULSE_FOCUS].angle_pulse_existence==false
       &&m_pulse[DLP_PULSE_ZOOM].angle_pulse_existence==false
    )
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

/**
* @brief
*
*/
void CManagePulse::UpdatePulseGroup()
{
    int len=8;
    dlp_log(DLP_LOG_DEBUG,"CManagePulse::UpdatePulseGroup()");
    int i;
    uint32_t pulse[8]={0};//////////////////////////////////////////////Max variable setting................
    for(i=DLP_PULSE_PAN;i<DLP_PULSE_MAX;i++)
    {
        if(m_pulse[i].angle_pulse_frame_sum!=0)//if angle_pulse_frame_sum=0 ,and need to update the DLPMotorPulse pulse
        {
            m_pdev_pulses->ReadPulseGroup(pulse);
            m_psys_pulses->WritePulseGroup(pulse,len);

            m_pulse[i].angle_pulse_frame_counter+=1;

            if(m_pulse[i].angle_pulse_frame_counter==m_pulse[i].angle_pulse_frame_sum)//whether Command execution completed
            {
                m_pulse[i].angle_pulse_existence=false;
                m_pulse[i].cmd_convert_curve_enable=true;
                m_pulse[i].angle_pulse_frame_counter=0;
                m_pulse[i].angle_pulse_frame_sum=0;
            }
        }


    }

}

void CManagePulse::RunPulseGroup()      //run the step motor
{
    dlp_log(DLP_LOG_DEBUG,"CManagePulse::RunPulseGroup()");
    m_psys_pulses->RunPulseGroups();
 #ifdef DLP_DEBUG
    std::cout<<"[debug] m_pulse[0].angle_pulse_existence "<<m_pulse[0].angle_pulse_existence<<std::endl;
    std::cout<<"[debug] m_pulse[0].cmd_convert_curve_enable "<<m_pulse[0].cmd_convert_curve_enable<<std::endl;
    std::cout<<"[debug] m_pulse[0].angle_pulse_frame_counter "<<m_pulse[0].angle_pulse_frame_counter<<std::endl;
    std::cout<<"[debug] m_pulse[0].angle_pulse_frame_sum "<<m_pulse[0].angle_pulse_frame_sum<<std::endl;
#endif // DLP_DEBUG
}


//////////////////////////////////////////////////////////////////////////////////////////////////////f
/**
* @brief Check whether to amend the pulse
*
*/
int CManagePulse::IsAmend(const DLPMotorPulse &type,const float &coder_angle)
{
    return 0;//m_pamend_pulses->IsAmend(type,coder_angle);
}



void CManagePulse::GetAmendParameter(const DLPMotorPulse &type,uint16_t *time_angle)
{
    //m_pamend_pulses->GetAmendParameter(type,time_angle);

}

void CManagePulse::SetAmendParameter(const DLPMotorPulse &type,uint16_t *time_angle)
{
    //m_pamend_pulses->SetAmendParameter(type,time_angle);

}

void CManagePulse::SetMotrAttr(const DLPMotorPulse &type,const DLPMotorAttr &mattr,const DLPEncoderAttr &eattr)
{
    //m_pamend_pulses->SetAmendAttr(type,mattr,eattr);

}
//////////////////////////////////////////////////////////
