#include "camend.h"
#include <cmath>
#include <iostream>
const float EPSINON = 0.00001;
CAmend::CAmend()
{
    m_amendment_time_internal=1;//task_internal_ms

    m_last_coder_angle=0;
    m_last_timing_time=0;
    m_attr.coder_gear_rate=17/99.0;
    m_attr.motor_speed=3;
    m_attr.pwm_period_ns=3;
    m_attr.step_angle=3;
}

CAmend::~CAmend()
{

}

/**
 * @code
 *
 *  //Config the relevant parameters
 *  ConfigAttr(AmendAttr);
 *  // Prepare correction error
 *  Ready(current_coder_angle,all_the_timing_time)
 *  //Get Amend delay length
 *  GetAmendTime(current_coder_angle)
 *  // to Modify the timer length
 * @endcode
 */

/**
* @brief
* @param
* @param
* @return
*/
void CAmend::ConfigAttr(DLPAmendAttr &attr)
{
    std::cout<<"CAmend::ConfigAttr"<<std::endl;
    m_attr=attr;
    std::cout<<m_attr.coder_gear_rate<<":"<<m_attr.motor_gear_rate<<":"<<m_attr.motor_speed<<":"<<m_attr.pwm_period_ns<<":"<<m_attr.step_angle<<std::endl;
}

/**
* @brief
* @param motor_speed (rpm:round per minute)
* @param timing_time (ns:nanosecond)
* @return
*/
void CAmend::Ready(const float &coder_angle,const long &timing_time)
{
    /*
    pwm_period
    step_angle
    gear_rate
    motor_speed

    last_coder_angle
    last_timing_time

    amendment_time_internal

    */
    std::cout<<"CAmend::Ready"<<coder_angle<<":"<<timing_time<<std::endl;
    m_last_coder_angle=coder_angle;//startup task 's coder angle
    m_last_timing_time=timing_time;//task timer time
}
/**
* @brief
* @param
* @param
* @return
*/
long CAmend::GetAmendTime(const float &cur_coder_angle)
{

    float real_angle,logic_angle,amend_angle;
    float delta;//real_angle-logic_angle
    float rho;  //delta/logic_angle
    long ret=0;

    real_angle=(cur_coder_angle-m_last_coder_angle)*m_attr.coder_gear_rate;
   // if(0==real_angle) return ret;
    if((real_angle<=EPSINON)&&(real_angle>=-EPSINON))//real_angle==0
    {
        return ret;//motor stop
    }
    else
    {
        m_last_coder_angle=cur_coder_angle;//update the coder angle
    }
    //logic_angle=m_attr.motor_speed*60*m_last_timing_time*pow(10,-9);//motor_speed*360/60/10^9*timing_time
     //logic_angle=m_attr.motor_speed*60*m_amendment_time_internal*pow(10,-9);//motor_speed*360/60/10^9*timing_time
     logic_angle=m_amendment_time_internal*1000000/m_attr.pwm_period_ns*m_attr.step_angle;//internal:ms period:ns
    //if()//
    delta=fabs(real_angle)-logic_angle;

    if (delta>=EPSINON)//real_angle is greater than logic_angle and timing will be decreasing
    {
        m_last_timing_time=m_last_timing_time-delta/m_attr.step_angle*m_attr.pwm_period_ns/1000;//us;
    }
    else
    {
        m_last_timing_time=m_last_timing_time+(-delta/m_attr.step_angle*m_attr.pwm_period_ns/1000);//us;
    }
    ret=m_last_timing_time;
    std::cout<<"real_angle:"<<real_angle<<":cur_coder_angle:"<<cur_coder_angle<<":m_last_coder_angle:"<<m_last_coder_angle<<std::endl;
    std::cout<<"logic_angle:"<<logic_angle<<":delta:"<<delta<<":m_last_timing_time:"<<m_last_timing_time<<std::endl;
    return ret;
}

void CAmend::Reset(void)
{


}



