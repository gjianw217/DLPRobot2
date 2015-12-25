//#include "dlpalgorithm.h"
//
//uint16_t speed2pulse(const uint16_t &speed,const MOTOR_SUBDIVISION subdivision)
//{
//	uint16_t pps;
//	uint8_t division=SubdivisionMappingValue[subdivision];
////	uint8_t division=subdivision; //enum setting value by 20150820
//	pps=speed*200*division/60.0; //pps max 153
//
//	return pps;
//}
//
//MOTOR_SUBDIVISION num2division(const uint16_t &num)
//{
//	MOTOR_SUBDIVISION  subdivision;
//	switch(num)
//	{
//	case 1:subdivision=one;break;
//	case 2:subdivision=two;break;
//	case 4:subdivision=four;break;
//	case 5:subdivision= five;break;
//	case 8:subdivision=eight;break;
//	case 10:subdivision=ten;break;
//	case 16:subdivision=sixteen;break;
//	case 20:subdivision=twenty;break;
//	case 25:subdivision=twentyfive;break;
//	case 32:subdivision=thirtytwo;break;
//	case 40:subdivision=forty;break;
//	case 50:subdivision=fifty;break;
//	case 64:subdivision=sixtyfour;break;
//	case 100:subdivision=hundred;break;
//	case 125:subdivision=huntwnfive;break;
//	case 128:subdivision=huntwneigth;break;
//	default :subdivision=huntwneigth;
//	}
//	return subdivision;
//}
