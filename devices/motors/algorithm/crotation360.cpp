#include "crotation360.h"

CRotation360::CRotation360():IRotation()
{

}

CRotation360::~CRotation360()
{


}
/*
This method will divide the circle into positive and negative 360 , respectively starting from the origin
the dest_dir decide the positive or negative,dest_angle decide the stop position
*/
float CRotation360::GetAnglebyAngle(const uint16_t &dest_dir,const float &dest_angle,const float &coder_angle)
{
	dlp_log(DLP_LOG_DEBUG,"CRotation360::GetAnglebyAngle");
	float move_angle=0.0,origin_offset=0.0,coder_offset =0.0;
	std::cout<<dest_angle<<":"<<coder_angle<<std::endl;
	coder_offset=coder_angle;

    if(m_attr.role==DLP_TILT)
	{
		origin_offset=-origin_offset;
	}
	/*4x2*/
	if(-360<origin_offset&&origin_offset<0)
	{
		move_angle=dest_angle-(360+origin_offset);
		if(POS_CLOCKWISE==dest_dir)
		{
			if(move_angle<0)
			{
				move_angle=360+move_angle;
				dlp_log(DLP_LOG_DEBUG,"00000-00000-00000");
			}
		}
		else
		{
			if(move_angle<=0)
			{
				move_angle=-move_angle;
				dlp_log(DLP_LOG_DEBUG,"00000-11111-00000");

			}
			else
			{
				//move_angle=360-move_angle;//    360
				move_angle=0;
				dlp_log(DLP_LOG_DEBUG,"00000-11111-11111");
			}
		}

	}
	else if(0<=origin_offset&&origin_offset<360)
	{
		move_angle=dest_angle-origin_offset;
		if(POS_CLOCKWISE==dest_dir)
		{
			if(move_angle<0)
			{
				//move_angle=360+move_angle;//    360
				move_angle=0;
				dlp_log(DLP_LOG_DEBUG,"11111-00000-00000");
			}
		}
		else
		{
			if(move_angle<=0)
			{
				move_angle=-move_angle;
				dlp_log(DLP_LOG_DEBUG,"11111-11111-00000");
			}
			else
			{
				move_angle=360-move_angle;
				dlp_log(DLP_LOG_DEBUG,"11111-11111-11111");
			}
		}

	}
	else
	{
		move_angle=0;
	}
	return move_angle;

}

int CRotation360::GetAnglebyTime(const double &time,const double &angle)
{

	return 0;
}
