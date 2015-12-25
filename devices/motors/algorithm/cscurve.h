#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CSCURVE_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CSCURVE_H_
#include "icurve.h"

class CSCurve:public ICurve
{
public:
	CSCurve();
	~CSCurve();

	int CreatePulseCurve(const double &angle,uint32_t *pwm);
protected:
private:
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CSCURVE_H_