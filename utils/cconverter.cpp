#include "cconverter.h"

void u322u16(const uint32_t &u32,uint16_t *u16)
{
	uint32_t temp=u32;
	u16[0]=temp;
	u16[1]=temp>>16;
}

uint32_t u162u32(const uint16_t *u16)
{
	uint32_t ret=u16[1];
	ret=ret<<16;

	return ret=ret|u16[0];
}

///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//uint32_t pos2angle(const uint16_t *cur_pos,const uint16_t *ref_pos,uint16_t *angle)
//{
//    uint32_t ret=150;2^14=16384
//
//    return ret;
//}


double u162d16(const uint16_t *value)
{
	double data=value[0]/1.0;

	return value[1]/data;
}


double u162d32(const uint16_t *value)
{

	double data=value[0]%10000;
	data=data/10000.0+value[1];
	return data;
}

void d322u16(const double &d32,uint16_t *u16)
{

	u16[1]=(uint16_t)d32;
	u16[0]=(d32-u16[1])*10000;
}


double u162t32(const uint16_t *time)
{
	double data=time[0]%1000;
	data=time[0]/1000+data/1000.0+time[1];

	return data;
}


std::string pin2str(const uint16_t &pin_addr)
{
    std::string ret;
    switch(pin_addr)
    {
        case 0x26:ret="";break;
        default:ret="";
    }

    return ret;
}


/*Step torque Angle Table with  corresponding to the above Table*/
static const float SubdivisionMappingAngle[]={1.8f,0.9f,0.45f,0.225f,0.1125f,0.05625f,0.028125f,0.0140625f,
	0.36f,0.18f,0.09f,0.072f,0.045f,0.036f,0.018f,0.0144f};
//在数据后面添加f，以抑制VS2010出现 warning C4305: 'initializing' : truncation from 'double' to 'const float
static const int SubdivisionMappingValue[]={1,2,4,8,16,32,64,128,
	5,10,20,25,40,50,100,125};

float division2angle(STEPMOTORDIVISION &division)
{
    return SubdivisionMappingAngle[division];

}
uint8_t division2ratio(STEPMOTORDIVISION &division)
{
    return SubdivisionMappingValue[division];

}
STEPMOTORDIVISION ratio2division(uint8_t ratio)
{
    STEPMOTORDIVISION  subdivision;
	switch(ratio)
	{
	case 1:subdivision=one;break;
	case 2:subdivision=two;break;
	case 4:subdivision=four;break;
	case 5:subdivision= five;break;
	case 8:subdivision=eight;break;
	case 10:subdivision=ten;break;
	case 16:subdivision=sixteen;break;
	case 20:subdivision=twenty;break;
	case 25:subdivision=twentyfive;break;
	case 32:subdivision=thirtytwo;break;
	case 40:subdivision=forty;break;
	case 50:subdivision=fifty;break;
	case 64:subdivision=sixtyfour;break;
	case 100:subdivision=hundred;break;
	case 125:subdivision=huntwnfive;break;
	case 128:subdivision=huntwneigth;break;
	default :subdivision=huntwneigth;
	}
	return subdivision;


}



