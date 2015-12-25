#ifndef DLP_PTZ_IPART_H_
#define DLP_PTZ_IPART_H_

#include "../dlp/dlp.h"
class IParts
{
public:
	explicit IParts(PCDataMapping datamapping);
    virtual ~IParts();

    virtual void Init()=0;
    PIEncoder GetCoder();
	PIMotor GetMotor();
	PCProximitySwitch GetSwitch();
protected:
    virtual PIEncoder CreateCoder(DLPCoderType type,DLPRole role);
	virtual PIMotor CreateMotor(DLPMotorType type,DLPRole role);
	virtual PCProximitySwitch CreateSwitch(DLPSwitchType type,DLPRole role);
	PIEncoder m_pcoder;
	PIMotor   m_pmotor;
	PCProximitySwitch m_pswitch;
	PCDataMapping m_pdatamapping;
private:
    uint8_t getCoderConfigID(DLPRole &role);
    std::string getCoderConfigCom(DLPRole &role);
    std::string getMotorDriverPin(DLPRole &role);
    std::string getMotorDriverPRU(DLPRole &role);
};

#endif //DLP_PTZ_IPART_H_

