#include <cstdio>
#include <iostream>
#include <string>
#include "cprintattr.h"
static std::string ret;
static std::string enumRole2string(const DLPRole &role)
{

    switch(role)
    {
        case DLP_PAN:ret="Pan ";break;
        case DLP_TILT:ret="Tilt ";break;
        case DLP_FOCUS:ret="FOCUS ";break;
        case DLP_ZOOM: ret="ZOOM ";break;
        default:ret="unknown ";
    }
    return ret;
}

void PrintCoderAttr(const DLPEncoderAttr &attr)
{
#ifdef DLP_DEBUG
	std::cout<<"DLP "<<enumRole2string(attr.dlp_role)<< "Coder Info::"<<std::endl
		<<"    dlp_id:"<<attr.dlp_id<<std::endl
		<<"    dlp_bits:"<<attr.dlp_bits<<std::endl
		<<"    dlp_role:"<<attr.dlp_role<<std::endl
        <<"    dlp_type:"<<attr.dlp_type<<std::endl
		<<"    dlp_model:"<<attr.dlp_model<<std::endl
		<<"    dlp_coder_gear:"<<attr.dlp_gear[1]<<":"<<attr.dlp_gear[0]<<std::endl;
		if(DLP_FOCUS==attr.dlp_role||DLP_ZOOM==attr.dlp_role)
		{
   printf("    dlp_serial.databit:%x\n",attr.dlp_serial.databit);
   printf("    dlp_serial.stop::%x\n",attr.dlp_serial.stop);
   printf("    dlp_serial.parity:%x\n",attr.dlp_serial.parity);
   printf("    dlp_serial.flow:%x\n",attr.dlp_serial.flow);
		}
#endif
}
void PrintMotorAttr(const DLPMotorAttr &attr)
{
#ifdef DLP_DEBUG
    std::cout<<"DLP "<<enumRole2string(attr.dlp_algorithm.role)<< "Motor Info::"<<std::endl

		<<"    dlp_role:"<<attr.dlp_algorithm.role<<std::endl

		<<"    dlp_curve:"<<attr.dlp_curve<<std::endl
		<<"    dlp_rotation:"<<attr.dlp_rotation<<std::endl
        <<"    dlp_type:"<<attr.dlp_type<<std::endl
		<<"    dlp_model:"<<attr.dlp_model<<std::endl
		<<"    dlp_algorithm.division:"<<attr.dlp_algorithm.g.division<<std::endl
		<<"    dlp_algorithm.gear:"<<attr.dlp_algorithm.g.gear[1]<<":"<<attr.dlp_algorithm.g.gear[0]<<std::endl
		<<"    dlp_algorithm.g.max_speed :"<<attr.dlp_algorithm.g.max_speed <<std::endl
		<<"    dlp_algorithm.g.min_speed :"<<attr.dlp_algorithm.g.min_speed <<std::endl
		<<"    dlp_algorithm.t.acc  :"<<attr.dlp_algorithm.t.acc <<std::endl
		<<"    dlp_algorithm.s.amax :"<<attr.dlp_algorithm.s.amax <<std::endl
		<<"    dlp_algorithm.s.hmax  :"<<attr.dlp_algorithm.s.hmax <<std::endl
		<<"    dlp_algorithm.b.in :"<<attr.dlp_algorithm.b.inc <<std::endl

		<<"    dlp_dir:"<<attr.dlp_dir.pin<<":"<<attr.dlp_dir.value<<std::endl
        <<"    pwmpin:"<<attr.dlp_pwm.pwmpin<<std::endl
		<<"    pwmvalue:"<<attr.dlp_pwm.pwmvalue<<std::endl;
		if(DLP_FOCUS==attr.dlp_algorithm.role||DLP_ZOOM==attr.dlp_algorithm.role)
		{
    std::cout
        <<"    dlp_pwm.periodNs:"<<attr.dlp_pwm.periodNs<<std::endl
		<<"    dlp_pwm.dutyNs:"<<attr.dlp_pwm.dutyNs<<std::endl
		<<"    dlp_pwm.polarity:"<<attr.dlp_pwm.polarity<<std::endl
        <<"    dlp_pwm.runStatus:"<<attr.dlp_pwm.runStatus<<std::endl;
		}
#endif
}

