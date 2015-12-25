#ifndef DLP_DEVICES_MOTORS_ALGORITHM_IROTATION_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_IROTATION_H_
#include "../../../dlp/dlp.h"
#include "../../../utils/cdebug.h"

class IRotation
{
public:
	IRotation();
	~IRotation();
	void SetAttr(const DLPAlgorithmAttr &attr);
	virtual float GetAnglebyAngle(const uint16_t &dest_dir,const float &dest_angle,const float &coder_angle)=0;
	virtual int GetAnglebyTime(const double &time,const double &angle)=0;

protected:
	DLPAlgorithmAttr m_attr;
private:
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_IROTATION_H_
