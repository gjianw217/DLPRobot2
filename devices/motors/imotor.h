#ifndef DLP_DEVICES_MOTORS_IMOTOR_H_
#define DLP_DEVICES_MOTORS_IMOTOR_H_
#include "../../dlp/dlp.h"
#include "../../utils/cdebug.h"
#include <deque>

typedef struct
{
    uint32_t angle;
    uint32_t time;
    uint32_t curve;

}DLPCurveCmd;

class IMotor
{
public:
	IMotor();
	~IMotor();
	virtual void SetCoder(PIEncoder pcoder);
	/////////////////////////////////////////////////
	virtual int SetAttr(const DLPMotorAttr &attr);
	void ModifyCurve(const DLPMotorCurveType &curve);
	void ModifyRotation(const DLPMotorRotationType &roation);
	///////////////////////////////////////

	    /***/
    virtual int ReadCmd()=0;
    virtual void WriteCmd( DLPModbusCmd &cmd)=0;;
    virtual void CmdConvertPulses()=0;;
    virtual int ReadPulses(uint32_t *des)=0;;
    virtual void SetCmdAmendPulses(uint16_t *pdata)=0;
    /***/
	virtual void RunByTime(const double &time,const double &angle,const uint16_t &dir=0)=0;
	virtual void RunbyAngle(const double &angle,const uint16_t &dir=0)=0;
	virtual void RunbyAngleTimeDir(const double &angle,const uint32_t &time,const uint16_t &dir,const uint8_t &curve)=0;
	virtual void EmergencyStop ()=0;
	virtual void ReturnRefOrigin()=0;
protected:
	PCAlgorithm m_palgorithm;//internal maintenance
	PCDirection m_pdirection;//internal maintenance
	PIEncoder     m_pcoder;  //external incoming

	PICurve m_pcurve;
	PIRotation m_protation;
	DLPMotorAttr m_attr;

	 std::deque<DLPModbusCmd> m_curve_cmds;
private:

};

#endif //DLP_DEVICES_MOTORS_IMOTOR_H_
