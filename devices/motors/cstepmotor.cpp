#include <cstring>//memset
#include "../../drivers/cpru.h"
#include "../../drivers/cpwm.h"
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
#include "cstepmotor.h"

CStepMotor::CStepMotor():IMotor()
{
	memset(this->m_pwm_array,0,(4*PWM_ORDER+3)*sizeof(uint32_t));
	m_ppru=PCPRU(new CPRU("pru1"));
}

CStepMotor::CStepMotor( std::string pru_pin):IMotor()
{
	m_ppru=PCPRU(new CPRU(pru_pin));
	//m_ppwm=PCPWM(new CPWM("xxx",5000,3));
	memset(this->m_pwm_array,0,(4*PWM_ORDER+3)*sizeof(uint32_t));
}

CStepMotor::~CStepMotor()
{

}

int CStepMotor::ReadCmd()
{
    return m_curve_cmds.size();
}

void CStepMotor::WriteCmd(DLPModbusCmd &cmd)
{
    dlp_log(DLP_LOG_DEBUG,"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
    this->m_curve_cmds.push_back(cmd);
    std::cout<<m_curve_cmds.size()<<std::endl;

    //CmdConvertPulses();
}

void CStepMotor::CmdConvertPulses()
{

    if(m_pcurve.use_count()==0)
    {
        dlp_log(DLP_LOG_ERR,"Without Setting the curve algorithm for the motor");
        return;
    }
    dlp_log(DLP_LOG_ERR,"Without Setting the curve algorithm for the motor");

    DLPModbusCmd cmd;
    uint32_t time=0;
    float angle=0.0;

    cmd = m_curve_cmds.at(m_curve_cmds.size() -1);
    this->m_curve_cmds.pop_front();
    angle=static_cast<float>(cmd.cmd_data[2]+cmd.cmd_data[1]*0.001);;
    time=cmd.cmd_data[4]*1000+cmd.cmd_data[3];

    std::cout<<"angle:"<<angle<<"time:"<<time<<std::endl;

    m_pcurve->CreatePulseCurve(time,angle,m_pwm_array);

}
int CStepMotor::ReadPulses(uint32_t *des)
{
    if(des!=NULL)
    {
        for(int i=0;i<m_pwm_array[0]+1;i++)
        {
            des[i]=m_pwm_array[i+1];

        }
    }
    return m_pwm_array[0];
}

void CStepMotor::SetCmdAmendPulses(uint16_t *pdata)
{
    std::cout<<" CStepMotor::CmdAmendPulses"<<std::endl;
    DLPModbusCmd cmd;
    cmd.cmd_data[2]=pdata[2];
    cmd.cmd_data[1]=pdata[1];


    this->m_curve_cmds.push_front(cmd);
}

/***********************************/

void CStepMotor::Run(uint32_t pulseNum,uint8_t status)
{
    uint32_t pwm[2]={0};
    pwm[0]=status;
    pwm[1]=pulseNum;

    m_ppru->Run(pwm);
}


/**

*/

void CStepMotor::RunbyAngleTimeDir(const double &angle,const uint32_t &time,const uint16_t &dir,const uint8_t &curve)
{
/*Naked command test
    unsigned int pwm[]={ 0,10, 1, 10 };
	if (m_ppru)
	{
		m_ppru->Run(pwm);
	}
*/


/**/
     if(m_pcurve.use_count()==0)
    {
        dlp_log(DLP_LOG_ERR,"Without Setting the curve algorithm for the motor");
        return;
    }

    //m_pcurve->CreatePulseCurve(angle,m_pwm_array);
    std::cout<<"4444444444444444444444444"<<std::endl;
    ///motor start moving
    //m_ppru->Run(m_pwm_array);

/**/




}



void CStepMotor::RunbyAngle(const double &angle,const uint16_t &dir/* =0 */)
{
	//dlp_log(DLP_LOG_DEBUG,"CStepMotor::RunbyAngle");
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
    //m_pcurve->CreatePulseCurve(move_angle,m_pwm_array);
	///confirmation the rotation direction
	if (dir!=m_pdirection->GetDirValue())
	{
		m_pdirection->SetDirValue(dir);
	}
	///motor start moving
	m_ppru->Run(m_pwm_array);



}

void CStepMotor::RunByTime(const double &time,const double &angle,const uint16_t &dir/* =0 */)
{

}

void CStepMotor::EmergencyStop()
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotor::EmergencyStop()");
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

void CStepMotor::ReturnRefOrigin()
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotor::ReturnRefOrigin()");
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


