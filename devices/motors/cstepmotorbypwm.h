#ifndef DLP_DEVICES_MOTORS_CStepMotorbyPWM_H_
#define DLP_DEVICES_MOTORS_CStepMotorbyPWM_H_
#include <string>
#include "imotor.h"
#include "../../dlp/dlpdevices.h"

class CStepMotorbyPWM:public IMotor
{
public:
	CStepMotorbyPWM();
	explicit CStepMotorbyPWM(const std::string &pwm_pin);
	~CStepMotorbyPWM();

	//virtual int SetAttr(const DLPMotorAttr &attr);
	virtual void RunByTime(const double &time,const double &angle,const uint16_t &dir=0);
	virtual void RunbyAngle(const double &angle,const uint16_t &dir=0);
    virtual void EmergencyStop();
	virtual void ReturnRefOrigin();
	//config the amend parameter at 20150916
    virtual void SetCoder(PIEncoder pcoder);
	virtual int SetAttr(const DLPMotorAttr &attr);
protected:
private:
	PCPWM m_ppwm;
	PCAmendPwmMotor m_pamendpwmmotor;
	PCPWMFeedbackControl m_ppwmfeedbackcontrol;
    //AmendAttr m_amendattr;
};

#endif//DLP_DEVICES_MOTORS_CStepMotorbyPWM_H_
