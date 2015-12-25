#include <cmath>
#include <iostream>
#include <iomanip>

#include "ctcurve.h"
#include "../../../utils/cconverter.h"
//#define TORDERNUM 10
#define DLP_MAX_FRAMES 200

CTCurve::CTCurve():ICurve()
{

}

CTCurve::~CTCurve()
{

}


int CTCurve::CreatePulseCurve(const double &angle,uint32_t *pwm)
{

    std::cout<<"CTCurve::CreatePulseCurve"<<std::endl;
    int ret,sums,steps;
    uint32_t frames;

    uint16_t refPulse[DLP_MAX_FRAMES+1]={0};
    uint32_t pulses[DLP_MAX_FRAMES+1]={0};;
    sums=CreateRefPulses(refPulse);
    steps=Angle2Step(angle);
    if(1==1)
    {
        frames=ComputeFrames(steps,sums,refPulse,pulses);
    }

    std::cout<<"show --------------"<<std::endl;
    for(int i=0;i<frames;i++)
    {
        std::cout<<pulses[i]<<std::endl;
    }
    std::cout<<"end ................"<<std::endl;
	return 0;
}

int CTCurve::CreateRefPulses(uint16_t *pulses)
{
    int i,sum=0;

    for(i=0;i<TORDERNUM;i++)
    {
        pulses[i]=(m_attr.max_speed-m_attr.min_speed)*(2*i-1)/(2*TORDERNUM)+m_attr.min_speed;
        sum+=pulses[i];
        std::cout<<pulses[i]<<"--";

    }
    pulses[TORDERNUM]=2*sum;  //sum frames
    std::cout<<std::endl;

    return pulses[TORDERNUM];
}

uint32_t CTCurve::Angle2Step(const float &value)
{
    double angle=value;
    //double step_angle=SubdivisionMappingAngle[num2division(m_attr.division)];;
    STEPMOTORDIVISION division=ratio2division(m_attr.division);
    double step_angle=division2angle(division);
//    uint32_t step = (uint32_t)(angle*m_attr.gear[1]/m_attr.gear[0]/step_angle);
    uint32_t step = (uint32_t)(angle*m_attr.gear[1]/m_attr.gear[0]/step_angle);
    std::cout<<"Request Angles "<< angle<<" to Steps "<<step<<std::endl;
    std::cout<<"gear[1] "<<m_attr.gear[1]<<" gear[0] "<<m_attr.gear[0]<<std::endl;
    std::cout<<"step angle "<<step_angle<<std::endl;

    return step ;
    return 0;
}
/**
*
 frames  data1 data2 ...
*/
int CTCurve::ComputeFrames(const uint32_t &steps,const uint16_t &ref_sum,const uint16_t *ref_step,uint32_t *pulses)
{
    assert(NULL!=ref_step);

    uint32_t ret,i,j,value;
    uint32_t frames=0;

    std::cout<<steps<<":"<<ref_sum<<":"<<std::endl;

    if (steps>ref_sum)
	{

		value=(steps-ref_sum); //constantSpeedNum

		frames=2*TORDERNUM+(steps-ref_sum)/m_attr.max_speed+1;
		std::cout<<"frames "<< frames<<std::endl;
        pulses[0]=frames;
		for(i=1;i<TORDERNUM+1;i++) //save the variable speed pulses
		{
            pulses[i]=ref_step[i-1];
            pulses[frames-i]=ref_step[i-1];
		}

		for(int i=TORDERNUM+1;i<frames-TORDERNUM;i++) //save the constant speed pulses
		{
            pulses[i]=m_attr.max_speed;

		}

		pulses[i]=(steps-ref_sum)%m_attr.max_speed;

	}
	else
	{
        std::cout<<"only accelaration"<<std::endl;
        uint16_t step_num=steps;
        for(i=0;i<TORDERNUM;i++)
		{
			if(step_num<2*ref_step[i])
			{
				frames=(i+1);
				break;
			}
			else
			{
                step_num=step_num-2*ref_step[i];

			}

        }

        std::cout<<"frames"<<frames<<std::endl;
        pulses[0]=2*frames;
		for(i=1;i<frames;i++)
		{
            pulses[i]=ref_step[i-1];
        }
		for(i=2*frames,j=0;i>frames+1;i--,j++)
		{
             pulses[i]=ref_step[j];
		}
		pulses[frames]=step_num/2;
		pulses[frames+1]=step_num/2;

	  }//else

    return frames;
	return 0;

}

/*

*/
int CTCurve::ComputeFrameswithTime(const float time,const float &angle,const uint16_t &ref_sum,const uint16_t *ref_step,uint32_t *pulses)
{
    int ret,i,value;
    uint8_t feilds=20;
    int frames=0;
    uint16_t step_num=Angle2Step(angle);


    uint16_t  numerator,denominator;
    numerator=step_num-TORDERNUM*m_attr.min_speed;
    denominator=time/feilds+TORDERNUM;

    frames=numerator/denominator;
	return 0;


}

int CTCurve::CreatePulses()
{
	return 0;

}



