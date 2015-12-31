#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CLCURVE_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CLCURVE_H_
#include "icurve.h"
class CLCurve:public ICurve
{
public:
	CLCurve();
	~CLCurve();

	int CreatePulseCurve(const uint32_t time,const double &angle,uint32_t *pwm);
protected:

private:
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CLCURVE_H_
