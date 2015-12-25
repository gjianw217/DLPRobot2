#ifndef DLP_DEVICES_MOTORS_ALGORITHM_CROTATION360_H_
#define DLP_DEVICES_MOTORS_ALGORITHM_CROTATION360_H_
#include "irotation.h"

class CRotation360:public IRotation
{
public:
	CRotation360();
	~CRotation360();

	virtual float GetAnglebyAngle(const uint16_t &dest_dir,const float &dest_angle,const float &coder_angle);
	virtual int GetAnglebyTime(const double &time,const double &angle);

protected:
private:
};
#endif //DLP_DEVICES_MOTORS_ALGORITHM_CROTATION360_H_