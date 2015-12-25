#include "../../drivers/cpwm.h"
//#include "../../utils/casynctimer.h"
//#include "../../utils/camend.h"
//#include "../../utils/camendpwmmotor.h"
//#include "../../utils/pwmfeedbackcontrol.h"

#include "../encoder/crs485coder.h"
#include "cdirection.h"
#include "cstepmotorbypwm.h"
#include "calgorithm.h"
#include "algorithm/clcurve.h"
#include "algorithm/crotation360.h"
#include "algorithm/crotation720.h"
#include "algorithm/crotation720.h"
#include "algorithm/icurve.h"
#include "algorithm/irotation.h"
#include "algorithm/ctcurve.h"
#include "algorithm/cscurve.h"

#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define BOOST_DATE_TIME_HAS_NANOSECONDS 1
CStepMotorbyPWM::CStepMotorbyPWM():IMotor()
{

}

CStepMotorbyPWM::CStepMotorbyPWM(const std::string &pwm_pin):IMotor()
{
	m_ppwm=PCPWM(new CPWM(pwm_pin));
	//m_pamendpwmmotor=PCAmendPwmMotor(new CAmendPwmMotor());
	///Debug....
//	m_ppwmfeedbackcontrol=PCPWMFeedbackControl(new CPWMFeedbackControl());
//	m_ppwmfeedbackcontrol->Run(1);
}


CStepMotorbyPWM::~CStepMotorbyPWM()
{

}

void CStepMotorbyPWM::RunbyAngle(const double &angle,const uint16_t &dir/* =0 */)
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotorbyPWM::RunbyAngle");

    if(m_ppwm)
    {
        dlp_log(DLP_LOG_DEBUG,"CStepMotorbyPWM::Testing...");
        static int testdir=0;
        m_pdirection->SetDirValue(1);
        m_ppwm->SetPeriod(8333333);
        m_ppwm->SetDuty(5000000);
        m_ppwm->SetRun(1);
        boost::asio::io_service io;
        boost::asio::deadline_timer t(io, boost::posix_time::seconds(10));
        t.async_wait(boost::bind(&CStepMotorbyPWM::EmergencyStop,this));
        io.run();
    }
    return;



    if(m_ppwm)
    {
//        m_pdirection->SetDirValue(1);
//        m_ppwm->SetPeriod(m_attr.dlp_pwm.periodNs);
//        m_ppwm->SetDuty(m_attr.dlp_pwm.dutyNs);
//        m_ppwm->SetRun(1);
//        boost::asio::io_service io;
//        boost::asio::deadline_timer t(io, boost::posix_time::seconds(10));
//        t.async_wait(boost::bind(&CStepMotorbyPWM::EmergencyStop,this));
//        io.run();
        ////////////////////////////////////////////////////
        float coder_angle=0.0,move_angle;
        uint64_t move_time=0;
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


        /*Get real Move Angle */
        // coder_angle=m_pcoder->GetCoderAngle();
        move_angle=m_protation->GetAnglebyAngle(dir,angle,coder_angle);

        /*Get the Move Time*/
        if(m_attr.dlp_pwm.periodNs>8333333&&m_attr.dlp_pwm.periodNs<333333333)//1-36rpm
        {
           // move_time=m_attr.dlp_pwm.periodNs*angle/SubdivisionMappingAngle[num2division(m_attr.dlp_algorithm.division)];

        }
        else
        {
            float temp=move_angle/1.8;
            // move_time=30303030*temp;//10rpm  1 division
             move_time=234411*temp*128;//1rpm 128 division
             move_time=move_time*56;
        }
        move_time=move_time/1000;//ns--->us
        /*Set Move Args*/
//        if(MOTOR_POS_CLOCKWISE==m_pdirectio->GetDirValue())
//            m_pdirection->SetDirValue(MOTOR_NEG_CounterCLOCKWISE);
        m_pdirection->SetDirValue(!m_pdirection->GetDirValue());

        m_ppwm->SetRun(0);
        m_ppwm->SetDuty(0);
        if(m_attr.dlp_pwm.periodNs>8333333&&m_attr.dlp_pwm.periodNs<333333333)//1-36rpm
        {
            m_ppwm->SetPeriod(m_attr.dlp_pwm.periodNs);
            m_ppwm->SetDuty(m_attr.dlp_pwm.dutyNs);
            #ifdef DLP_DEBUG
            printf("Angle %f,Period %ld(ns),move_time %ld(us)\n",move_angle,m_attr.dlp_pwm.periodNs,move_time);
            #endif // DLP_DEBUG
        }
        else
        {
//            m_ppwm->SetPeriod(30303030);
//            m_ppwm->SetDuty(15151515);
            m_ppwm->SetPeriod(234411);
            m_ppwm->SetDuty(117205);
            #ifdef DLP_DEBUG
            printf("Angle %f,Period 234411(ns),move_time %d(us)\n",move_angle,move_time);
            #endif // DLP_DEBUG
        }


        /*Run*/
#ifdef DLP_AMEND_MOTOR1
        std::cout<<"CStepMotorbyPWM::RunbyAngle:Amend"<<std::endl;
        m_pamendpwmmotor->SetExit(boost::bind(&CStepMotorbyPWM::EmergencyStop,this));
        m_pamendpwmmotor->SetCoder(m_pcoder);
        coder_angle=m_pcoder->GetCoderAngle();
        m_pamendpwmmotor->Ready(coder_angle,move_time);//for amendment algorithm
        m_ppwm->SetRun(1);
        m_pamendpwmmotor->Run(move_time,1);

#elif DLP_PWM_FEEDBACK_CONTROL1
        std::cout<<"CStepMotorbyPWM::RunbyAngle:Feedback control"<<std::endl;
        m_ppwmfeedbackcontrol->SetCoder(m_pcoder);
        m_ppwmfeedbackcontrol->Update(Pwm_Focus_Device,move_time,boost::bind(&CStepMotorbyPWM::EmergencyStop,this));//us

        //coder_angle=m_pcoder->GetCoderAngle();
        //m_pamendpwmmotor->Ready(coder_angle,move_time);//for amendment algorithm
         m_ppwm->SetRun(1);m_ppwmfeedbackcontrol->Run(1);


#else
        boost::asio::io_service io;
        std::cout<<"CStepMotorbyPWM::RunbyAngle:Common timer"<<std::endl;
       // boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(move_time));
        boost::asio::deadline_timer t(io, boost::posix_time::microseconds(move_time));
        t.async_wait(boost::bind(&CStepMotorbyPWM::EmergencyStop,this));
        m_ppwm->SetRun(1);
        io.run();
#endif // DLP_AMEND_MOTOR


    }

}

void CStepMotorbyPWM::RunByTime(const double &time,const double &angle,const uint16_t &dir/* =0 */)
{

}

void CStepMotorbyPWM::ReturnRefOrigin()
{
    dlp_log(DLP_LOG_DEBUG," CStepMotorbyPWM::ReturnRefOrigin()");
    if(m_ppwm)
    {

        m_pdirection->SetDirValue(1);
        m_ppwm->SetPeriod(m_attr.dlp_pwm.periodNs);
        m_ppwm->SetDuty(m_attr.dlp_pwm.dutyNs);
        m_ppwm->SetRun(1);
    }
}

void CStepMotorbyPWM::EmergencyStop()
{
    dlp_log(DLP_LOG_DEBUG,"CStepMotorbyPWM::EmergencyStop()");
    if(m_ppwm)
    {
        m_ppwm->SetRun(0);
        m_pdirection->SetDirValue(!m_pdirection->GetDirValue());
    }

}

 void CStepMotorbyPWM::SetCoder(PIEncoder pcoder)
 {
    //m_pamendpwmmotor->SetCoder(pcoder);
//    if(m_ppwmfeedbackcontrol.use_count()!=0)
//    {
//        m_ppwmfeedbackcontrol->SetCoder(pcoder);
//    }

    IMotor::SetCoder(pcoder);
 }
 int CStepMotorbyPWM::SetAttr(const DLPMotorAttr &attr)
 {
//    AmendAttr amendattr;
//    amendattr.coder_gear_rate=17/99.0;
//    amendattr.motor_gear_rate=56/1.0;
//    amendattr.motor_speed=3;
//    //amendattr.pwm_period_ns=30303030;
//    amendattr.pwm_period_ns=234411;
//    amendattr.step_angle=1.8/128;
//    //m_pamendpwmmotor->ConfigAttr(amendattr);
//    if(m_ppwmfeedbackcontrol.use_count()!=0)
//    {
//        m_ppwmfeedbackcontrol->SetAttr(amendattr);
//    }

    return IMotor::SetAttr(attr);
 }
