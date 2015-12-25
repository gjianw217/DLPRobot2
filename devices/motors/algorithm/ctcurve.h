#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CTCURVE_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CTCURVE_H_
#include "icurve.h"

class CTCurve:public ICurve
{
public:
	CTCurve();
	~CTCurve();

	int CreatePulseCurve(const double &angle,uint32_t *pwm);
protected:
private:
//	int CreateRefPWM(uint16_t *fre_per_step,uint16_t *num_per_step);
//	uint32_t Angle2Step(const float &value);
//	int ComputeOrder(const float &angle,const uint16_t &step_sum,const uint16_t *ref_step,uint32_t &value);
//	void CreatePWM(const int &order,const uint32_t &order_value,const uint16_t *ref_fre,const uint16_t *ref_num,uint32_t *pwm);
    int CreateRefPulses(uint16_t *pulses);
    uint32_t Angle2Step(const float &value);
    int  ComputeFrames(const uint32_t &steps,const uint16_t &ref_sum,const uint16_t *ref_step,uint32_t *pulses);
    int ComputeFrameswithTime(const float time,const float &angle,const uint16_t &ref_sum,const uint16_t *ref_step,uint32_t *pulses);
    int CreatePulses(void);
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CTCURVE_H_
