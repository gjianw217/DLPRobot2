#ifndef DLP_COMMON_DLPALGORITHM_H_
#define DLP_COMMON_DLPALGORITHM_H_
#include <stdint.h>

#define  ORDERNUM (10)
#define TORDERNUM (10)  //trapezoid order
#define SORDERNUM (62)  //S-shape order,not used ,Determined by the algorithm itself
#define BORDERNUM (40)  //bezier order
#define DLP_PULSE_MAX_FRAME (2000)
//#define DLP_PULSE_MAX_FRAME (3876+224)
#define DLP_MAX_PULSES (2000) //cdevpulses

//1 is PTZ mapped to the resolution of the encoder
//0.02(0.021974) resolution of the encoder that 360/(pow(2,coder_bits)-1);
//16 The number of pulses that encoder rotates a step
#define DLP_MAX_AMEND_ERROR (1/0.02*16)
//0.02
#define DLP_MAX_AMEND_INTERNAL (2)



/*Frequency division coefficient Table of Stepper motor driver (DM856)*/
typedef enum {
	one=0,
	two=1,
	four=2,
	eight=3,
	sixteen=4,
	thirtytwo=5,
	sixtyfour=6,
	huntwneigth=7,
	five=8,
	ten=9,
	twenty=10,
	twentyfive=11,
	forty=12,
	fifty=13,
	hundred=14,
	huntwnfive=15
}DM856DIVISION;

#define  STEPMOTORDIVISION DM856DIVISION


#endif//DLP_COMMON_DLPALGORITHM_H_
