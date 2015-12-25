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
	two,
	four,
	eight,
	sixteen,
	thirtytwo,
	sixtyfour,
	huntwneigth,
	five,
	ten,
	twenty,
	twentyfive,
	forty,
	fifty,
	hundred,
	huntwnfive
}DM856DIVISION;

#define  STEPMOTORDIVISION DM856DIVISION


#endif//DLP_COMMON_DLPALGORITHM_H_
