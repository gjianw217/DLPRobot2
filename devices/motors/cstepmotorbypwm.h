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

    /***/
    virtual void WriteCmd( DLPModbusCmd &cmd);
    virtual void CmdConvertPulses();
    virtual int ReadPulses(uint32_t *des);
    virtual int ReadCmdSize();
    virtual void SetCmdAmendPulses(uint16_t *pdata);

    /***/
	void Run(uint32_t pulseNum,uint8_t status);
	virtual void RunByTime(const double &time,const double &angle,const uint16_t &dir=0);
	virtual void RunbyAngle(const double &angle,const uint16_t &dir=0);
    virtual void RunbyAngleTimeDir(const double &angle,const uint32_t &time,const uint16_t &dir,const uint8_t &curve);
    virtual void EmergencyStop();
	virtual void ReturnRefOrigin();

    /**/


    /**/
	//config the amend parameter at 20150916
//    virtual void SetCoder(PIEncoder pcoder);
//	virtual int SetAttr(const DLPMotorAttr &attr);
protected:
private:
    PCAmend m_pamend;
};

#endif//DLP_DEVICES_MOTORS_CStepMotorbyPWM_H_
