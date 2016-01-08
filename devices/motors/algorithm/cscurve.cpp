#include "cscurve.h"
#include "../../../utils/cconverter.h"


CSCurve::CSCurve()
{

}

CSCurve::~CSCurve()
{

}

int CSCurve::CreatePulseCurve(const uint32_t time,const double &angle,uint32_t *pwm)
{
    dlp_log(DLP_LOG_DEBUG,"CSCurve::CreatePulseCurve");


    std::cout<<"CTCurve::CreatePulseCurve"<<std::endl;
    int ret,sums,steps;
    uint32_t frames;
    uint16_t refPulse[DLP_SMAX_FRAMES+1]={0};
    uint16_t refSubPulse[3]={0};
    uint16_t refSubfrmaes[3]={0};
    uint32_t pulses[DLP_SMAX_FRAMES+1]={0};;
    sums=CreateRefPulses(refPulse,refSubPulse,refSubfrmaes);

    if(0==time)
    {

        steps=Angle2Step(angle);
        frames=ComputeFrames(steps,sums,refPulse,refSubPulse,refSubfrmaes,pulses);
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

int CSCurve::CreateRefPulses(uint16_t *pulses,uint16_t *refSubPulse,uint16_t *refframes)
{
    DLPSAttr attr;
    attr.min_speed=140;
    attr.max_speed=740;
    attr.hmax=2;
    attr.amax=20;

	int j = 0;
	int sum=0;
	int v1, v2;
	int t1, t2, t3;

	if(pulses==NULL)
	{
        return -1;
	}
    uint16_t *v=pulses;

	t1= attr.amax / attr.hmax;
	refframes[0]=t1;
	for (int i = 1; i < t1+1; i++,j++)
	{
		v[j] = attr.min_speed + attr.hmax*i*i / 2;
		sum += v[j];
	}
    refSubPulse[0]=sum;
	v1 = v[j - 1];
	t2 = (attr.max_speed - attr.min_speed) / attr.amax - t1;
	refframes[1]=t2;
	for (int i = 1; i < t2+1; i++,j++)
	{
		v[j] = v1 + attr.amax*(i);
		sum += v[j];
	}
    refSubPulse[1]=sum-refSubPulse[0];
	v2 = v[j - 1];
	t3 = t1;
	refframes[2]=t3;
	for (int i = 1; i < t3+1; i++,j++)
	{

		v[j] = v2 + attr.amax*(i ) - attr.hmax*(i +0)*(i + 0) / 2;
		sum += v[j];
	}
    refSubPulse[2]=sum-refSubPulse[0]-refSubPulse[1];
    //pulses[0]=t1+t2+t3;
	for (int i = 0; i < 50; i++)
	{

		std::cout <<"v["<<i<<"]="<< v[i] << std::endl;
	}
	std::cout << "sum" << sum << std::endl;

    return sum;

    return 0;
}

uint32_t CSCurve::Angle2Step(const float &value)
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

int  CSCurve::ComputeFrames(const uint32_t &steps,const uint16_t &ref_sum,const uint16_t *ref_step,const uint16_t *refSubPulse,const uint16_t *refSubFrame,uint32_t *pulses)
{
    assert(NULL!=ref_step);

    uint32_t ret,i,j,value;
    uint32_t frames=0;
    uint16_t subFrame=0;
    std::cout<<steps<<":"<<ref_sum<<":"<<std::endl;

    if(steps>=2*ref_sum)/// the whole S algorithm
    {
        subFrame=refSubFrame[0]+refSubFrame[1]+refSubFrame[2];
		frames=2*subFrame+((steps-ref_sum)/m_attr.max_speed)+1;
        pulses[0]=frames;

		for(i=1;i<subFrame+1;i++) //save the variable speed pulses
		{
            pulses[i]=ref_step[i-1];
            pulses[frames-i]=ref_step[i-1];
		}

		for(i=subFrame+1;i<frames-subFrame;i++) //save the constant speed pulses
		{
            pulses[i]=m_attr.max_speed;

		}

		pulses[i]=(steps-ref_sum)%m_attr.max_speed;////////////////////////////////////////
    }
    else if(steps<=2*refSubPulse[0])///only the varying acceleration
    {

        uint16_t step_num=steps;
        AssignPulses(steps,subFrame,ref_step,pulses);
    }
    else if(steps<=2*(refSubFrame[0]+refSubFrame[1]))///including the varying acceleration and constant acceleration
    {
        subFrame=refSubFrame[0]+refSubFrame[1];
        AssignPulses(steps,subFrame,ref_step,pulses);

    }
    else ///if(steps<refSubFrame[0]+refSubFrame[1]+refSubFrame[2])///not the constant speed
    {
        subFrame=refSubFrame[0]+refSubFrame[1]+refSubFrame[2];
        AssignPulses(steps,subFrame,ref_step,pulses);

    }



    return frames;
    return 0;
}

int CSCurve::ComputeFrameswithTime(uint32_t time,const float &angle,uint32_t *pulses)
{
    uint32_t angle_frames= time/20;
    uint16_t acceleration_frames=0;
    int16_t temp=angle_frames-acceleration_frames;

    //If greater than zero, then there is uniform speed phase and to modify the speed by the solving equations
    if(temp>0)
    {

    }
    else
    {


    }
    return 0;
}

void CSCurve::AssignPulses(const uint32_t &angle_pulse,const uint16_t &subFrame,const uint16_t *ref_step,uint32_t *pulses)
{
    int i=0,j;
    int frames=0;
    uint32_t step_num=angle_pulse;
     //Get the frames
    for(i=0;i<subFrame;i++)
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
    //Assign the Pulses
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

}
