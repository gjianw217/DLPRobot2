#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CBEZIERCURVE_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CBEZIERCURVE_H_
#include "icurve.h"



typedef struct
{
    uint16_t min_speed;
    uint16_t max_speed;
    BezierWeight x;
    BezierWeight y;

    float inc;

}DLPBEZIERATTR;


class CBezierCurve:public ICurve
{
public:
	CBezierCurve();
	~CBezierCurve();

	int CreatePulseCurve(const uint32_t time,const double &angle,uint32_t *pwm);

protected:
    int  ComputeFrames(const uint32_t &steps,const uint16_t &ref_sum,const uint16_t *ref_step,uint32_t *pulses);
    int ComputeFrameswithTime(uint32_t time,const float &angle,uint32_t *pulses);
    uint32_t Angle2Step(const float &value);
    void CreateBezier();
    int CreateRefPulses(uint16_t *pulses);
private:
    CoordValue m_samplesValue[4];
    //DLPBEZIERATTR m_bezier_attr;
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CBEZIERCURVE_H_
