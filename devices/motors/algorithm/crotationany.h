#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CROTATIONANY_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CROTATIONANY_H_
#include "irotation.h"

class CRotationAny:public IRotation
{
public:
	CRotationAny();
	~CRotationAny();

	virtual float GetAnglebyAngle(const uint16_t &dest_dir,const float &dest_angle,const float &coder_angle);
	virtual int GetAnglebyTime(const double &time,const double &angle);
protected:
private:
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CROTATIONANY_H_