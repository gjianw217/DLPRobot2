#include "crotationany.h"

CRotationAny::CRotationAny():IRotation()
{

}

CRotationAny::~CRotationAny()
{

}

float CRotationAny::GetAnglebyAngle(const uint16_t &dest_dir,const float &dest_angle,const float &coder_angle)
{
    dlp_log(DLP_LOG_DEBUG,"CRotationAny::GetAnglebyAngle");
	float move_angle=0.0;

	return move_angle;
}

int CRotationAny::GetAnglebyTime(const double &time,const double &angle)
{

	return 0;
}
