#ifndef DLP_COMMON_DLPALGORITHM_H_
#define DLP_COMMON_DLPALGORITHM_H_
#include <stdint.h>

#define  ORDERNUM 10
#define TORDERNUM 10
#define S1ORDERNUM 10
#define S2ORDERNUM 10
#define S3ORDERNUM 10

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