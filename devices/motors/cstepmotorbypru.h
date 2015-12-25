#ifndef DLP_DEVICES_MOTORS_CStepMotorbyPRU_H_
#define DLP_DEVICES_MOTORS_CStepMotorbyPRU_H_
#include "imotor.h"
#define PWM_ORDER 10
class CStepMotorbyPRU:public IMotor
{
public:
	CStepMotorbyPRU();
	explicit CStepMotorbyPRU( std::string pru_pin);
	~CStepMotorbyPRU();

	//virtual int SetAttr(const DLPMotorAttr &attr);
	virtual void RunByTime(const double &time,const double &angle,const uint16_t &dir=0);
	virtual void RunbyAngle(const double &angle,const uint16_t &dir=0);
    virtual void EmergencyStop();
	virtual void ReturnRefOrigin();
protected:
private:
	PCPRU m_ppru;
	uint32_t m_pwm_array[4*PWM_ORDER+3];

};
#endif//DLP_DEVICES_MOTORS_CStepMotorbyPRU_H_
