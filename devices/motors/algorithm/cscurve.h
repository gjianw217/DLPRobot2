#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CSCURVE_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CSCURVE_H_
#include "icurve.h"
#define DLP_SMAX_FRAMES 200
typedef struct
{
    uint16_t min_speed;
    uint16_t max_speed;
    uint16_t hmax;
    uint16_t amax;
}DLPSAttr;

class CSCurve:public ICurve
{
public:
	CSCurve();
	~CSCurve();

	int CreatePulseCurve(const uint32_t time,const double &angle,uint32_t *pwm);
protected:
    int CreateRefPulses(uint16_t *pulses,uint16_t *refSubPulse,uint16_t *refframes);
    uint32_t Angle2Step(const float &value);
    int  ComputeFrames(const uint32_t &steps,const uint16_t &ref_sum,const uint16_t *ref_step,const uint16_t *refSubPulse,const uint16_t *refSubFrame,uint32_t *pulses);
    int ComputeFrameswithTime(uint32_t time,const float &angle,uint32_t *pulses);
private:
    void AssignPulses(const uint32_t &angel_pusle,const uint16_t &subframe,const uint16_t *ref_step,uint32_t *pulses);
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CSCURVE_H_
