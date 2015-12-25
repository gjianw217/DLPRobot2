/*无符号整形的32位数据转成无符号整形的16位数据*/
#include <stdint.h>
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


/*两数相除，得到小数值*/
double u162d16(const uint16_t *value)
{
	double data=value[0]/1.0;

	return value[1]/data;
}
/*整数表示小数间的转换*/
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
