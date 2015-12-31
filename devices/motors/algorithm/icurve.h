#ifndef DLP_DEVICES_MOTORS_ALGORITHM_ICURVE_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_ICURVE_H_
#include "../../../dlp/dlp.h"
#include "../../../utils/cdebug.h"

class ICurve
{
public:
	ICurve();
	~ICurve();
	void SetAttr(const DLPAlgorithmAttr &attr);
	virtual int CreatePulseCurve(const uint32_t time,const double &angle,uint32_t *pwm)=0;
protected:
	DLPAlgorithmAttr m_attr;
private:
};
#endif
