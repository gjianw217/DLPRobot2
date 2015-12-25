#include <cstring>//memset
#include "../../drivers/cpru.h"
#include "../encoder/ccancoder.h"
#include "calgorithm.h"
#include "algorithm/clcurve.h"
#include "algorithm/crotation360.h"
#include "algorithm/crotation720.h"
#include "algorithm/crotation720.h"
#include "algorithm/icurve.h"
#include "algorithm/irotation.h"
#include "algorithm/ctcurve.h"
#include "algorithm/cscurve.h"
#include "cdirection.h"
#include "cstepmotorbypru.h"

CStepMotorbyPRU::CStepMotorbyPRU():IMotor()
{
	memset(this->m_pwm_array,0,(4*PWM_ORDER+3)*sizeof(uint32_t));
}

CStepMotorbyPRU::CStepMotorbyPRU( std::string pru_pin):IMotor()
{
	m_ppru=PCPRU(new CPRU(pru_pin));
	memset(this->m_pwm_array,0,(4*PWM_ORDER+3)*sizeof(uint32_t));
}

CStepMotorbyPRU::~CStepMotorbyPRU()
{

}

void CStepMotorbyPRU::RunbyAngle(const double &angle,const uint16_t &dir/* =0 */)
{
	//dlp_log(DLP_LOG_DEBUG,"CStepMotorbyPRU::RunbyAngle");
	/*Testpwm array is used to test whether the PRU works properly,which the human eye can seesmall lights flashing  of the corresponding pins*/
//	uint32_t testpwm[4*PWM_ORDER+3]={10,500000000,1,500000000,1,500000000,1,500000000,1,500000000,1,500000000,1,500000000,1,500000000,1,500000000,1,500000000,1} ;
	//uint32_t testpwm[4*PWM_ORDER+3]={1,976,2,0} ;
	//uint32_t testpwm[4*PWM_ORDER+3]={1,2400,8,0} ;
	m_pwm_array[0]=1;
	m_pwm_array[1]=angle;
	m_pwm_array[2]=dir;
	//printf("%d,%d,%d\n",m_pwm_array[0],m_pwm_array[1],m_pwm_array[2]);
	if (m_ppru)
	{
		m_ppru->Run(m_pwm_array);
	}
//	if(m_pdirection)
//	{
//        m_pdirection->SetDirValue(1);
//	}

	return ;

	////////////////////////////////////////////////////
	float coder_angle=0.0,move_angle;
	/**
	* check if the necessary parameters have been set up correctly,
	* if not set,it will not be able to complete the application afterwards.
	*/
    if(m_pcoder.use_count()==0)
    {
        dlp_log(DLP_LOG_ERR,"Without seting the encoder for the motor");
        return;
    }
    if(m_protation.use_count()==0)
    {
        dlp_log(DLP_LOG_ERR,"Without Setting the rotation algorithm for the motor");
        return;
    }
    if(m_pcurve.use_count()==0)
    {
        dlp_log(DLP_LOG_ERR,"Without Setting the curve algorithm for the motor");
        return;
    }

   ///get real rotation angle
   // coder_angle=m_pcoder->GetCoderAngle();
    move_angle=m_protation->GetAnglebyAngle(dir,angle,coder_angle);
	///computing rotation pulse(PWM)
    m_pcurve->CreatePulseCurve(move_angle,m_pwm_array);
	///confirmation the rotation direction
	if (dir!=m_pdirection->GetDirValue())
	{
		m_pdirection->SetDirValue(dir);
	}
	///motor start moving
	m_ppru->Run(m_pwm_array);



}

void CStepMotorbyPRU::RunByTime(const double &time,const double &angle,const uint16_t &dir/* =0 */)
{

}

void CStepMotorbyPRU::EmergencyStop()
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotorbyPRU::EmergencyStop()");
    uint32_t testpwm[4+3]={7,0,0,0,0,0,0} ;
	if (m_ppru)
	{
		m_ppru->Run(testpwm);
	}
	if(m_pdirection)
	{
        m_pdirection->SetDirValue(0);
	}
}

void CStepMotorbyPRU::ReturnRefOrigin()
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotorbyPRU::ReturnRefOrigin()");
    uint32_t testpwm[4*PWM_ORDER+3]={10,50000000,1,50000000,1,50000000,1,50000000,1,50000000,1,50000000,1,50000000,1,50000000,1,50000000,1,50000000,1} ;
	if (m_ppru)
	{
		m_ppru->Run(testpwm);
	}
	if(m_pdirection)
	{
        m_pdirection->SetDirValue(1);
	}
}
