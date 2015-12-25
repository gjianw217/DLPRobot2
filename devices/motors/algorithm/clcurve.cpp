#include "clcurve.h"
#include <stdio.h>
#include <math.h>

CLCurve::CLCurve():ICurve()
{

}

CLCurve::~CLCurve()
{

}

int CLCurve::CreatePulseCurve(const double &angle,uint32_t *pwm)
{
    dlp_log(DLP_LOG_DEBUG,"CLCurve::CreatePulseCurve");
    if(DLP_PAN==m_attr.role||DLP_TILT==m_attr.role)
    {
        dlp_log(DLP_LOG_DEBUG,"PTZ::CreatePulseCurve");
        pwm[0]=1;
        //PRU Unit Simulation PWM Period Num
//        pwm[1]=SubdivisionMappingAngle[num2division(m_attr.division)]*pow(10,8)/(m_attr.max_speed+m_attr.min_speed)/6;
//        //PRU Unit Simulation PWM Pulse Num to Rotation given angle
//        pwm[2]=angle/SubdivisionMappingAngle[num2division(m_attr.division)];
#ifdef DLP_DEBUG
        printf("DLP_LOG_DEBUG,Angle %f\n",angle);
        printf("DLP_LOG_DEBUG,Division %d",m_attr.division);
       /// printf(",Step Angle %f",SubdivisionMappingAngle[num2division(m_attr.division)]);
        printf(",Max Speed%d",m_attr.max_speed);
        printf(",Min Speed%d\n",m_attr.min_speed);
#endif // DLP_DEBUG
    }
	return 0;
}
