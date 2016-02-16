#include "cstepmotorbypwm.h"
#include "correction/camend.h"

#include "../../drivers/cpwm.h"
CStepMotorbyPWM::CStepMotorbyPWM():IMotor()
{
    m_pamend=PCAmend(new CAmend());
}

CStepMotorbyPWM::CStepMotorbyPWM(const std::string &pwm_pin):IMotor()
{

	//m_pamendpwmmotor=PCAmendPwmMotor(new CAmendPwmMotor());
	///Debug....
//	m_ppwmfeedbackcontrol=PCPWMFeedbackControl(new CPWMFeedbackControl());
//	m_ppwmfeedbackcontrol->Run(1);
}


CStepMotorbyPWM::~CStepMotorbyPWM()
{

}
////////////////////////////////////////////////////////////////////////////////////////
void CStepMotorbyPWM::WriteCmd( DLPModbusCmd &cmd)
{

}

void CStepMotorbyPWM::CmdConvertPulses()
{

}

uint16_t CStepMotorbyPWM::ReadPulses(uint32_t *des)
{

}

int CStepMotorbyPWM::ReadCmdSize()
{

}

void CStepMotorbyPWM::SetCmdAmendPulses(uint16_t *pdata)
{

}


void CStepMotorbyPWM::Run(uint32_t pulseNum,uint8_t status)
{

}

void CStepMotorbyPWM::RunByTime(const double &time,const double &angle,const uint16_t &dir)
{

}

void CStepMotorbyPWM::RunbyAngle(const double &angle,const uint16_t &dir)
{

}

void CStepMotorbyPWM::RunbyAngleTimeDir(const double &angle,const uint32_t &time,const uint16_t &dir,const uint8_t &curve)
{
    /**/

    /**/
    if(m_pamend->IsControl())// Check Whether to Convert the Pulses
    {

    }


    if(m_pamend->IsAmend()) // Check  Whether to Amend the Pulses
    {

    }

    if(m_pamend->IsDriver()) //Check Whether to Driver the Pulses
    {

    }

}

void CStepMotorbyPWM::EmergencyStop()
{

}

void CStepMotorbyPWM::ReturnRefOrigin()
{

}

