#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CTESTCURVE_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CTESTCURVE_H_
#include "icurve.h"
class CTestCurve:public ICurve
{
public:
	CTestCurve();
	~CTestCurve();

	int CreatePulseCurve(const double &angle,uint32_t *pwm);
protected:

private:
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CTESTCURVE_H_
