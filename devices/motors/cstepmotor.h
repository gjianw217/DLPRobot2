#ifndef DLP_DEVICES_MOTORS_CStepMotor_H_
#define DLP_DEVICES_MOTORS_CStepMotor_H_
#include "imotor.h"
#define PWM_ORDER 10

class CStepMotor:public IMotor
{
public:
	CStepMotor();
	explicit CStepMotor( std::string pru_pin);
	~CStepMotor();

    /***/
    virtual void WriteCmd( DLPModbusCmd &cmd);
    virtual void CmdConvertPulses();
    virtual int ReadPulses(uint32_t *des);
    virtual int ReadCmd();
    virtual void SetCmdAmendPulses(uint16_t *pdata);
    /***/
	//virtual int SetAttr(const DLPMotorAttr &attr);
	void Run(uint32_t pulseNum,uint8_t status);
	virtual void RunByTime(const double &time,const double &angle,const uint16_t &dir=0);
	virtual void RunbyAngle(const double &angle,const uint16_t &dir=0);
    virtual void RunbyAngleTimeDir(const double &angle,const uint32_t &time,const uint16_t &dir,const uint8_t &curve);
    virtual void EmergencyStop();
	virtual void ReturnRefOrigin();
protected:
private:
	PCPRU m_ppru;
	//PCPWM m_ppwm;
	uint32_t m_pwm_array[4000];//{360/(1.8/(128*56))}/740=1937 ==> 4000=2000*2

};
#endif//DLP_DEVICES_MOTORS_CStepMotor_H_
