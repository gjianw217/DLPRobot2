#include "cbeziercurve.h"
#include "../../../utils/cconverter.h"

CBezierCurve::CBezierCurve()
{
    //initial point
    m_samplesValue[0].x=0;
    m_samplesValue[0].y=m_attr.g.min_speed;
    //control dot
    m_samplesValue[1].x=m_attr.b.inc;
    m_samplesValue[1].y=m_attr.g.min_speed*2;
    //control dot
    m_samplesValue[2].x=3*m_attr.b.inc;
    m_samplesValue[2].y=3*m_attr.g.max_speed/4;
    //terminal point
    m_samplesValue[3].x=1;
    m_samplesValue[3].y=m_attr.g.max_speed;

    CreateBezier();//generate the bezier curve
}

CBezierCurve::~CBezierCurve()
{

}


int CBezierCurve::CreatePulseCurve(const uint32_t time,const double &angle,uint32_t *pwm)
{
    dlp_log(DLP_LOG_DEBUG,"CSCurve::CreatePulseCurve");

    int ret,sums,steps;
    uint32_t frames;
    uint16_t refPulse[50]={0};
    uint32_t pulses[50]={0};;

    if(0==time)
    {
        sums=CreateRefPulses(refPulse);
        steps=Angle2Step(angle);
        frames=ComputeFrames(steps,sums,refPulse,pulses);
    }
    else
    {
        frames=ComputeFrameswithTime(time,angle,pulses);
    }

    std::cout<<"show --------------"<<std::endl;
    for(int i=0;i<frames;i++)
    {
        std::cout<<pulses[i]<<std::endl;
    }
    std::cout<<"end ................"<<std::endl;
	return 0;

}

/**
* @brief generating the bezier curve
*
*/
void CBezierCurve::CreateBezier()
{
    m_attr.b.x.c=3.0 * (m_samplesValue[1].x - m_samplesValue[0].x);
    m_attr.b.x.b=3.0 * (m_samplesValue[2].x - m_samplesValue[1].x) - m_attr.b.x.c;
	m_attr.b.x.a = m_samplesValue[3].x - m_samplesValue[0].x - m_attr.b.x.c - m_attr.b.x.b;

	m_attr.b.y.c = 3.0 * (m_samplesValue[1].y - m_samplesValue[0].y);
	m_attr.b.y.b = 3.0 * (m_samplesValue[2].y - m_samplesValue[1].y) - m_attr.b.y.c;
	m_attr.b.y.a = m_samplesValue[3].y - m_samplesValue[0].y - m_attr.b.y.c - m_attr.b.y.b;
}

/**
* @brief Creating the reference pulses by the bezier curve algorithm
* @param  saving the reference pulses by created
* @return pulses sum
*/
int CBezierCurve::CreateRefPulses(uint16_t *pulses)
{

	float tSquared, tCubed;
	int sum=0;
	float t=0;

	for (int i = 0; t <= 1; i++,t += m_attr.b.inc)
	{
		tSquared = t * t;
		tCubed = tSquared * t;
		pulses[i] = (m_attr.b.y.a * tCubed) + (m_attr.b.y.b * tSquared) + (m_attr.b.y.c * t) + m_samplesValue[0].y;
        sum+=pulses[i];
		std::cout << "speed: " << pulses[i]<<std::endl;

	}

	return 2*sum;

}

/**
* @brief moving angle into the driving pulses
* @param angle value
* @return pulses quantity
*/
uint32_t CBezierCurve::Angle2Step(const float &value)
{
    double angle=value;
    //double step_angle=SubdivisionMappingAngle[num2division(m_attr.division)];;
    STEPMOTORDIVISION division=ratio2division(m_attr.g.division);
    double step_angle=division2angle(division);
//    uint32_t step = (uint32_t)(angle*m_attr.gear[1]/m_attr.gear[0]/step_angle);
    uint32_t step = (uint32_t)(angle*m_attr.g.gear[1]/m_attr.g.gear[0]/step_angle);
    std::cout<<"Request Angles "<< angle<<" to Steps "<<step<<std::endl;
    std::cout<<"gear[1] "<<m_attr.g.gear[1]<<" gear[0] "<<m_attr.g.gear[0]<<std::endl;
    std::cout<<"step angle "<<step_angle<<std::endl;

    return step ;


}

/**
*
*
*
*/
int  CBezierCurve::ComputeFrames(const uint32_t &steps,const uint16_t &ref_sum,const uint16_t *ref_step,uint32_t *pulses)
{
    assert(NULL!=ref_step);

    uint32_t ret,i,j,value;
    uint32_t frames=0;

    std::cout<<steps<<":"<<ref_sum<<":"<<std::endl;

    if (steps>ref_sum)
	{

		value=(steps-ref_sum); //constantSpeedNum

		frames=2*BORDERNUM+(steps-ref_sum)/m_attr.g.max_speed+1;
		std::cout<<"frames "<< frames<<std::endl;
        pulses[0]=frames;
		for(i=1;i<BORDERNUM+1;i++) //save the variable speed pulses
		{
            pulses[i]=ref_step[i-1];
            pulses[frames-i]=ref_step[i-1];
		}

		for(int i=BORDERNUM+1;i<frames-BORDERNUM;i++) //save the constant speed pulses
		{
            pulses[i]=m_attr.g.max_speed;

		}

		pulses[i]=(steps-ref_sum)%m_attr.g.max_speed;

	}
	else
	{
        std::cout<<"only accelaration"<<std::endl;
        uint16_t step_num=steps;
        for(i=0;i<BORDERNUM;i++)
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


int CBezierCurve::ComputeFrameswithTime(uint32_t time,const float &angle,uint32_t *pulses)
{

    return 0;
}


