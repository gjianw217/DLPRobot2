#ifndef DLP_DEVICES_MOTORS_IMPL_H_
#define DLP_DEVICES_MOTORS_IMPL_H_
#include "../../../common/dlp.h"
class CPWMBase
{
public:
    CPWMBase();
    ~CPWMBase();

    void SetAttr(const DLPArmsMotorAttr &attr);
    void GetAttr(DLPArmsMotorAttr &attr);
	/*���ݲ�ͬ���㷨���ڲ�ͬ������ʵ��*/
	virtual void CreatePWMbyAngle(const float &angle, uint32_t *pwm)=0;
	virtual void CreatePWMbyTime(const float &time,const float &angle,  uint32_t *pwm)=0;
protected:
    DLPArmsMotorAttr m_attr;
};
#endif // DLP_DEVICES_MOTORS_IMPL_H_
