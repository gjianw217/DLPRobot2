#ifndef DLP_COMMON_DLPALGORITHM_H_
#define DLP_COMMON_DLPALGORITHM_H_
#include <stdint.h>

#define PWM_ORDER 10
/*Frequency division coefficient Table of Stepper motor driver (DM856)*/
//typedef enum {
//	one=0,
//	two,
//	four,
//	eight,
//	sixteen,
//	thirtytwo,
//	sixtyfour,
//	huntwneigth,
//	five,
//	ten,
//	twenty,
//	twentyfive,
//	forty,
//	fifty,
//	hundred,
//	huntwnfive
//}MOTOR_SUBDIVISION;
//
//Step torque Angle Table with  corresponding to the above Table
//const float SubdivisionMappingAngle[]={1.8f,0.9f,0.45f,0.225f,0.1125f,0.05625f,0.028125f,0.0140625f,
//	0.36f,0.18f,0.09f,0.072f,0.045f,0.036f,0.018f,0.0144f};
//在数据后面添加f，以抑制VS2010出现 warning C4305: 'initializing' : truncation from 'double' to 'const float
//const float SubdivisionMappingValue[]={1,2,4,8,16,32,64,128,
//	5,10,20,25,40,50,100,125};
//uint16_t speed2pulse(const uint16_t &speed,const MOTOR_SUBDIVISION subdivision);
//MOTOR_SUBDIVISION num2division(const uint16_t &num);



#endif//DLP_COMMON_DLPALGORITHM_H_
