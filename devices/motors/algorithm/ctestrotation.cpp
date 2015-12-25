#include "ctestrotation.h"

CTestRotation::CTestRotation():IRotation()
{

}

CTestRotation::~CTestRotation()
{

}

float CTestRotation::GetAnglebyAngle(const uint16_t &dest_dir,const float &dest_angle,const float &coder_angle)
{
    dlp_log(DLP_LOG_DEBUG,"CTestRotation::GetAnglebyAngle");
	float move_angle=0.0,origin_offset=0.0,coder_offset =0.0;

    move_angle=dest_angle;
	return move_angle;
}

int CTestRotation::GetAnglebyTime(const double &time,const double &angle)
{


	return 0;
}
