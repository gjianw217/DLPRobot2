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

/**
* @brief Custom PRU dirver the step motor
*/
CStepMotor::CStepMotor():IMotor()
{
	memset(this->m_pwm_array,0,(4*PWM_ORDER+3)*sizeof(uint32_t));
	m_ppru=PCPRU(new CPRU("pru1"));
}

/**
*@brief System PWM dirver the step motor
*/
CStepMotor::CStepMotor( std::string pru_pin):IMotor()
{

	m_ppru=PCPRU(new CPRU("pru0")); //Test Used
	memset(this->m_pwm_array,0,(4*PWM_ORDER+3)*sizeof(uint32_t));
}

CStepMotor::~CStepMotor()
{

}

/**
* @brief Check whether there is any commands(not executing) in the command queue.
* @return the acount of the command in the command queue.
**/
int CStepMotor::ReadCmd()
{
    return m_curve_cmds.size();
}
/**
* @brief Save the received command to the command queue
* @param received the command
*/
void CStepMotor::WriteCmd(DLPModbusCmd &cmd)
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotor::WriteCmd");
    this->m_curve_cmds.push_back(cmd);

    //CmdConvertPulses();
}

/**
* @brief  convert angle command into the control pulse
*/
void CStepMotor::CmdConvertPulses()
{

    if(m_pcurve.use_count()==0)
    {
        dlp_log(DLP_LOG_ERR,"Not Setting the curve algorithm for the motor");
        return;
    }
    dlp_log(DLP_LOG_DEBUG,"CStepMotor::CmdConvertPulses()");

    DLPModbusCmd cmd;
    uint32_t time=0;
    float angle=0.0;

    cmd = m_curve_cmds.at(m_curve_cmds.size() -1);
    this->m_curve_cmds.pop_front();

    /**
    data[4]   data[3]   data[2]        data[1]         data[0]
    time(s)   time(ms) angle(integer) angle(decimal)  direction
    */
    angle=static_cast<float>(cmd.cmd_data[2]+cmd.cmd_data[1]*0.001);;
    time=cmd.cmd_data[4]*1000+cmd.cmd_data[3];
#ifdef DLP_DEBUG
    std::cout<<"angle:"<<angle<<"time:"<<time<<std::endl;
#endif // DLP_DEBUG
    m_pcurve->CreatePulseCurve(time,angle,m_pwm_array);

    //Test Used----------------------------------------------------
    if (m_ppru)
	{
		m_ppru->Run(m_pwm_array);
	}
}

/**
* @brief  read the generated pulse array, it is produced by the specified curve algorithm
* @param  storing the addresses of pulse
* @return the group number of the pulse
*/
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

/**
* @brief Save the Amend the data into the command queue
* @param cmd pointer ,including the angle (and the time)
*/
void CStepMotor::SetCmdAmendPulses(uint16_t *pdata)
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotor::SetCmdAmendPulses");
    DLPModbusCmd cmd;
    cmd.cmd_data[2]=pdata[2];
    cmd.cmd_data[1]=pdata[1];

    this->m_curve_cmds.push_front(cmd);//put the cmd on the  most front in the command queue
}

/*********************************************************************************************/
/**@deprecated*/
void CStepMotor::Run(uint32_t pulseNum,uint8_t status)
{
    uint32_t pwm[2]={0};
    pwm[0]=status;
    pwm[1]=pulseNum;

    m_ppru->Run(pwm);
}


/**

*/
/**@deprecated*/
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


/**@deprecated*/
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
/**@deprecated*/
void CStepMotor::RunByTime(const double &time,const double &angle,const uint16_t &dir/* =0 */)
{

}
/**@deprecated*/
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
/**@deprecated*/
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


