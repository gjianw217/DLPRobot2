#include "crotation720.h"

CRotation720::CRotation720():IRotation()
{

}

CRotation720::~CRotation720()
{

}

float CRotation720::GetAnglebyAngle(const uint16_t &dest_dir,const float &dest_angle,const float &coder_angle)
{
    dlp_log(DLP_LOG_DEBUG,"CRotation720::GetAnglebyAngle");
	float move_angle=0.0,origin_offset=0.0,coder_offset =0.0;


	return move_angle;
}

int CRotation720::GetAnglebyTime(const double &time,const double &angle)
{


	return 0;
}
