/**
* @file       CDataMapping成员函数
* @author     GuoJianwei & gjianw217@163.com
* @date       2014.10.21
*/
#include "cdata-mapping.h"
CDataMapping::CDataMapping(PCConfig config)
{
    this->m_pconfig=config;
    this->m_pmb_mapping=modbus_mapping_new(3072,3072,3072 ,3072); /*< 12x256=3072.第3个参数，用来存放执行的命令，第4个参数，用来存放采集的数据*/

    Init();
}
CDataMapping::~CDataMapping()
{
    if(NULL!=m_pmb_mapping)
	{
		modbus_mapping_free(this->m_pmb_mapping);
	}

    std::cout<<"~CDataMapping()"<<std::endl;
}
/***
* @brief 根据配置文件，初始化数据单元
*/
void CDataMapping::Init()
{
    /*Initialization of system parameters*/
    this->m_pmb_mapping->tab_input_registers[0x005] = this->m_pconfig->GetValue("sys","cip4");
    this->m_pmb_mapping->tab_input_registers[0x004] = this->m_pconfig->GetValue("sys","cip3");
    this->m_pmb_mapping->tab_input_registers[0x003] = this->m_pconfig->GetValue("sys","cip2");
    this->m_pmb_mapping->tab_input_registers[0x002]=  this->m_pconfig->GetValue("sys","cip1");
    this->m_pmb_mapping->tab_input_registers[0x001] = this->m_pconfig->GetValue("sys","cip0");
	this->m_pmb_mapping->tab_input_registers[0x035] = this->m_pconfig->GetValue("sys","mac5");
	this->m_pmb_mapping->tab_input_registers[0x034] = this->m_pconfig->GetValue("sys","mac4");
	this->m_pmb_mapping->tab_input_registers[0x033] = this->m_pconfig->GetValue("sys","mac3");
	this->m_pmb_mapping->tab_input_registers[0x032] = this->m_pconfig->GetValue("sys","mac2");
	this->m_pmb_mapping->tab_input_registers[0x031] = this->m_pconfig->GetValue("sys","mac1");
	this->m_pmb_mapping->tab_input_registers[0x030] = this->m_pconfig->GetValue("sys","mac0");

    this->m_pmb_mapping->tab_registers[0x001]=  this->m_pconfig->GetValue("sys","id");
    this->m_pmb_mapping->tab_registers[0x004]=  this->m_pconfig->GetValue("sys","mip0");
    this->m_pmb_mapping->tab_registers[0x005]=  this->m_pconfig->GetValue("sys","mip1");
    this->m_pmb_mapping->tab_registers[0x006]=  this->m_pconfig->GetValue("sys","mip2");
    this->m_pmb_mapping->tab_registers[0x007]=  this->m_pconfig->GetValue("sys","mip3");
    this->m_pmb_mapping->tab_registers[0x008]=  this->m_pconfig->GetValue("sys","mip4");

    this->m_pmb_mapping->tab_registers[0x030]= this->m_pconfig->GetValue("sys","os");
    this->m_pmb_mapping->tab_registers[0x031]= this->m_pconfig->GetValue("sys","ver");
    this->m_pmb_mapping->tab_registers[0x032]= this->m_pconfig->GetValue("sys","ft0");
    this->m_pmb_mapping->tab_registers[0x033]= this->m_pconfig->GetValue("sys","ft1");
    this->m_pmb_mapping->tab_registers[0x034]= this->m_pconfig->GetValue("sys","ft2");
    this->m_pmb_mapping->tab_registers[0x035]= this->m_pconfig->GetValue("sys","model0");
    this->m_pmb_mapping->tab_registers[0x036]= this->m_pconfig->GetValue("sys","model1");
    this->m_pmb_mapping->tab_registers[0x037]= this->m_pconfig->GetValue("sys","model2");
    this->m_pmb_mapping->tab_registers[0x038]= this->m_pconfig->GetValue("sys","model3");
    this->m_pmb_mapping->tab_registers[0x039]= this->m_pconfig->GetValue("sys","SN0");
    this->m_pmb_mapping->tab_registers[0x03A]= this->m_pconfig->GetValue("sys","SN1");

    /*Pan encoder initialization*/
    this->m_pmb_mapping->tab_input_registers[0x204] = this->m_pconfig->GetValue("pansensor","origin0");
    this->m_pmb_mapping->tab_input_registers[0x205] = this->m_pconfig->GetValue("pansensor","origin1");

    this->m_pmb_mapping->tab_registers[0x200] = this->m_pconfig->GetValue("pansensor","id");
    this->m_pmb_mapping->tab_registers[0x201] = this->m_pconfig->GetValue("pansensor","baud0");
    this->m_pmb_mapping->tab_registers[0x202] = this->m_pconfig->GetValue("pansensor","baud1");
    this->m_pmb_mapping->tab_registers[0x203] = this->m_pconfig->GetValue("pansensor","type");
    this->m_pmb_mapping->tab_registers[0x204] = this->m_pconfig->GetValue("pansensor","mode");
    this->m_pmb_mapping->tab_registers[0x205] = this->m_pconfig->GetValue("pansensor","gear0");
    this->m_pmb_mapping->tab_registers[0x206] = this->m_pconfig->GetValue("pansensor","gear1");
    this->m_pmb_mapping->tab_registers[0x207] = this->m_pconfig->GetValue("pansensor","bits");


    /*Tilt encoder initialization*/
    this->m_pmb_mapping->tab_input_registers[0x304] = this->m_pconfig->GetValue("tiltsensor","origin0");
    this->m_pmb_mapping->tab_input_registers[0x305] = this->m_pconfig->GetValue("tiltsensor","origin1");

    this->m_pmb_mapping->tab_registers[0x300] = this->m_pconfig->GetValue("tiltsensor","id");
    this->m_pmb_mapping->tab_registers[0x301] = this->m_pconfig->GetValue("tiltsensor","baud0");
    this->m_pmb_mapping->tab_registers[0x302] = this->m_pconfig->GetValue("tiltsensor","baud1");
    this->m_pmb_mapping->tab_registers[0x303] = this->m_pconfig->GetValue("tiltsensor","type");
    this->m_pmb_mapping->tab_registers[0x304] = this->m_pconfig->GetValue("tiltsensor","mode");
    this->m_pmb_mapping->tab_registers[0x305] = this->m_pconfig->GetValue("tiltsensor","gear0");
    this->m_pmb_mapping->tab_registers[0x306] = this->m_pconfig->GetValue("tiltsensor","gear1");
    this->m_pmb_mapping->tab_registers[0x307] = this->m_pconfig->GetValue("tiltsensor","bits");

	/*Lens Zoom encoder initialization*/
	this->m_pmb_mapping->tab_input_registers[0x404] = this->m_pconfig->GetValue("zoomsensor","origin0");
	this->m_pmb_mapping->tab_input_registers[0x405] = this->m_pconfig->GetValue("zoomsensor","origin1");
	this->m_pmb_mapping->tab_input_registers[0x406] = this->m_pconfig->GetValue("zoomsensor","databit");
	this->m_pmb_mapping->tab_input_registers[0x407] = this->m_pconfig->GetValue("zoomsensor","stopbit");
	this->m_pmb_mapping->tab_input_registers[0x408] = this->m_pconfig->GetValue("zoomsensor","flowbit");
	this->m_pmb_mapping->tab_input_registers[0x409] = this->m_pconfig->GetValue("zoomsensor","paritybit");

	this->m_pmb_mapping->tab_registers[0x400] = this->m_pconfig->GetValue("zoomsensor","id");
	this->m_pmb_mapping->tab_registers[0x401] = this->m_pconfig->GetValue("zoomsensor","baud0");
	this->m_pmb_mapping->tab_registers[0x402] = this->m_pconfig->GetValue("zoomsensor","baud1");
	this->m_pmb_mapping->tab_registers[0x403] = this->m_pconfig->GetValue("zoomsensor","type");
	this->m_pmb_mapping->tab_registers[0x404] = this->m_pconfig->GetValue("zoomsensor","mode");
	this->m_pmb_mapping->tab_registers[0x405] = this->m_pconfig->GetValue("zoomsensor","gear0");
	this->m_pmb_mapping->tab_registers[0x406] = this->m_pconfig->GetValue("zoomsensor","gear1");
	this->m_pmb_mapping->tab_registers[0x407] = this->m_pconfig->GetValue("zoomsensor","bits");

	/*Lens Focus encoder initialization*/
	this->m_pmb_mapping->tab_input_registers[0x504] = this->m_pconfig->GetValue("focussensor","origin0");

	this->m_pmb_mapping->tab_input_registers[0x505] = this->m_pconfig->GetValue("focussensor","origin1");
	this->m_pmb_mapping->tab_input_registers[0x506] = this->m_pconfig->GetValue("focussensor","databit");
	this->m_pmb_mapping->tab_input_registers[0x507] = this->m_pconfig->GetValue("focussensor","stopbit");
	this->m_pmb_mapping->tab_input_registers[0x508] = this->m_pconfig->GetValue("focussensor","flowbit");
	this->m_pmb_mapping->tab_input_registers[0x509] = this->m_pconfig->GetValue("focussensor","paritybit");

	this->m_pmb_mapping->tab_registers[0x500] = this->m_pconfig->GetValue("focussensor","id");
	this->m_pmb_mapping->tab_registers[0x501] = this->m_pconfig->GetValue("focussensor","baud0");
	this->m_pmb_mapping->tab_registers[0x502] = this->m_pconfig->GetValue("focussensor","baud1");
	this->m_pmb_mapping->tab_registers[0x503] = this->m_pconfig->GetValue("focussensor","type");
	this->m_pmb_mapping->tab_registers[0x504] = this->m_pconfig->GetValue("focussensor","mode");
	this->m_pmb_mapping->tab_registers[0x505] = this->m_pconfig->GetValue("focussensor","gear0");
	this->m_pmb_mapping->tab_registers[0x506] = this->m_pconfig->GetValue("focussensor","gear1");
	this->m_pmb_mapping->tab_registers[0x507] = this->m_pconfig->GetValue("focussensor","bits");


    /*Pan Motor Initialization*/
    this->m_pmb_mapping->tab_input_registers[0x800] = this->m_pconfig->GetValue("panmotor","origin0");
    this->m_pmb_mapping->tab_input_registers[0x801] = this->m_pconfig->GetValue("panmotor","origin1");
	this->m_pmb_mapping->tab_input_registers[0x804] = this->m_pconfig->GetValue("panorigin","pin");
    this->m_pmb_mapping->tab_input_registers[0x807] = this->m_pconfig->GetValue("panmotor","dirpin");
    this->m_pmb_mapping->tab_input_registers[0x808] = this->m_pconfig->GetValue("panmotor","dirvalue");
    this->m_pmb_mapping->tab_registers[0x800] = this->m_pconfig->GetValue("panmotor","max");
    this->m_pmb_mapping->tab_registers[0x801] = this->m_pconfig->GetValue("panmotor","min");
    this->m_pmb_mapping->tab_registers[0x802] = this->m_pconfig->GetValue("panmotor","acc");
    this->m_pmb_mapping->tab_registers[0x803] = this->m_pconfig->GetValue("panmotor","subdivision");
    this->m_pmb_mapping->tab_registers[0x804] = this->m_pconfig->GetValue("panmotor","gear0");
    this->m_pmb_mapping->tab_registers[0x805] = this->m_pconfig->GetValue("panmotor","gear1");
    this->m_pmb_mapping->tab_registers[0x806] = this->m_pconfig->GetValue("panmotor","curve");
    this->m_pmb_mapping->tab_registers[0x807] = this->m_pconfig->GetValue("panmotor","rotation");
    this->m_pmb_mapping->tab_registers[0x814] = this->m_pconfig->GetValue("panmotor","direction");
    /*Tilt Motor Initialization*/
    this->m_pmb_mapping->tab_input_registers[0x0900] = this->m_pconfig->GetValue("tiltmotor","origin0");
    this->m_pmb_mapping->tab_input_registers[0x0901] = this->m_pconfig->GetValue("tiltmotor","origin1");
	this->m_pmb_mapping->tab_input_registers[0x0904] = this->m_pconfig->GetValue("tiltorigin","pin");
    this->m_pmb_mapping->tab_input_registers[0x0907] = this->m_pconfig->GetValue("tiltmotor","dirpin");
    this->m_pmb_mapping->tab_input_registers[0x0908] = this->m_pconfig->GetValue("tiltmotor","dirvalue");
    this->m_pmb_mapping->tab_registers[0x0900] = this->m_pconfig->GetValue("tiltmotor","max");
    this->m_pmb_mapping->tab_registers[0x0901] = this->m_pconfig->GetValue("tiltmotor","min");
    this->m_pmb_mapping->tab_registers[0x0902] = this->m_pconfig->GetValue("tiltmotor","acc");
    this->m_pmb_mapping->tab_registers[0x0903] = this->m_pconfig->GetValue("tiltmotor","subdivision");
    this->m_pmb_mapping->tab_registers[0x0904] = this->m_pconfig->GetValue("tiltmotor","gear0");
    this->m_pmb_mapping->tab_registers[0x0905] = this->m_pconfig->GetValue("tiltmotor","gear1");
    this->m_pmb_mapping->tab_registers[0x0906] = this->m_pconfig->GetValue("tiltmotor","curve");
    this->m_pmb_mapping->tab_registers[0x0907] = this->m_pconfig->GetValue("tiltmotor","rotation");
    this->m_pmb_mapping->tab_registers[0x0914] = this->m_pconfig->GetValue("tiltmotor","direction");

	/*Lens Zoom Motor Initialization*/

	this->m_pmb_mapping->tab_input_registers[0x0A05] = this->m_pconfig->GetValue("zoommotor","pwmpin");
	this->m_pmb_mapping->tab_input_registers[0x0A06] = this->m_pconfig->GetValue("zoommotor","pwmvalue");
	this->m_pmb_mapping->tab_input_registers[0x0A07] = this->m_pconfig->GetValue("zoommotor","dirpin");
	this->m_pmb_mapping->tab_input_registers[0x0A08] = this->m_pconfig->GetValue("zoommotor","dirvalue");

	this->m_pmb_mapping->tab_registers[0x0A04] = this->m_pconfig->GetValue("zoommotor","gear0");
	this->m_pmb_mapping->tab_registers[0x0A05] = this->m_pconfig->GetValue("zoommotor","gear1");
	this->m_pmb_mapping->tab_registers[0x0A06] = this->m_pconfig->GetValue("zoommotor","curve");
    this->m_pmb_mapping->tab_registers[0x0A07] = this->m_pconfig->GetValue("zoommotor","rotation");

	this->m_pmb_mapping->tab_registers[0x0A0A] = this->m_pconfig->GetValue("zoommotor","period0");
	this->m_pmb_mapping->tab_registers[0x0A0B] = this->m_pconfig->GetValue("zoommotor","period1");
	this->m_pmb_mapping->tab_registers[0x0A0C] = this->m_pconfig->GetValue("zoommotor","duty0");
	this->m_pmb_mapping->tab_registers[0x0A0D] = this->m_pconfig->GetValue("zoommotor","duty1");
	this->m_pmb_mapping->tab_registers[0x0A0E] = this->m_pconfig->GetValue("zoommotor","polarity");
	this->m_pmb_mapping->tab_registers[0x0A0F] = this->m_pconfig->GetValue("zoommotor","run");;

	/*Lens Focus Motor Initialization*/

	this->m_pmb_mapping->tab_input_registers[0x0B05] = this->m_pconfig->GetValue("focusmotor","pwmpin");
	this->m_pmb_mapping->tab_input_registers[0x0B06] = this->m_pconfig->GetValue("focusmotor","pwmvalue");
	this->m_pmb_mapping->tab_input_registers[0x0B07] = this->m_pconfig->GetValue("focusmotor","dirpin");
	this->m_pmb_mapping->tab_input_registers[0x0B08] = this->m_pconfig->GetValue("focusmotor","dirvalue");

	this->m_pmb_mapping->tab_registers[0x0B04] = this->m_pconfig->GetValue("focusmotor","gear0");
	this->m_pmb_mapping->tab_registers[0x0B05] = this->m_pconfig->GetValue("focusmotor","gear1");
	this->m_pmb_mapping->tab_registers[0x0B06] = this->m_pconfig->GetValue("focusmotor","curve");
    this->m_pmb_mapping->tab_registers[0x0B07] = this->m_pconfig->GetValue("focusmotor","rotation");

	this->m_pmb_mapping->tab_registers[0x0B0A] = this->m_pconfig->GetValue("focusmotor","period0");
	this->m_pmb_mapping->tab_registers[0x0B0B] = this->m_pconfig->GetValue("focusmotor","period1");
	this->m_pmb_mapping->tab_registers[0x0B0C] = this->m_pconfig->GetValue("focusmotor","duty0");
	this->m_pmb_mapping->tab_registers[0x0B0D] = this->m_pconfig->GetValue("focusmotor","duty1");
	this->m_pmb_mapping->tab_registers[0x0B0E] = this->m_pconfig->GetValue("focusmotor","polarity");
	this->m_pmb_mapping->tab_registers[0x0B0F] = this->m_pconfig->GetValue("focusmotor","run");;


}
/************************************************************************/
/* 以下8个函数，分别为：对数据结构中的数据元素进行读取或存放操作        */
/************************************************************************/
/***
* @brief 对线圈进行写操作
*/
void CDataMapping::SetCoils(const uint8_t *src, int addr, const int nb)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=src);

    for(int i=0;i<nb;i++)
    {
        this->m_pmb_mapping->tab_bits[addr++]=src[i];
    }
}

/***
* @brief 对线圈进行读操作
*/
void CDataMapping::GetCoils(int addr, const int nb,uint16_t *dest)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=dest);

    for(int i=0;i<nb;i++)
    {
        dest[i]=this->m_pmb_mapping->tab_bits[addr++];
    }

}
/***
* @brief 对离散输入进行写操作
*/
void CDataMapping::SetDiscreteInputs(const uint8_t *src,int addr, const int nb)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=src);

    for(int i=0;i<nb;i++)
    {
        this->m_pmb_mapping->tab_bits[addr++]=src[i];
    }
}
/***
* @brief 对离散输入进行读操作
*/
void CDataMapping::GetDiscreteInputs(int addr, const int nb, uint8_t *dest)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=dest);

    for(int i=0;i<nb;i++)
    {
        dest[i]=this->m_pmb_mapping->tab_input_bits[addr++];
    }
}
/***
* @brief 对输入寄存器进行写操作
*/
void CDataMapping::SetInputRegisters(const uint16_t *src,int addr,const int nb)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=src);

    for(int i=0;i<nb;i++)
    {
        this->m_pmb_mapping->tab_input_registers[addr++]=src[i];
    }
}
/***
* @brief 对输入寄存器进行读操作
*/
void CDataMapping::GetInputRegisters(int addr, const int nb, uint16_t *dest)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=dest);

    for(int i=0;i<nb;i++)
    {
        dest[i]=this->m_pmb_mapping->tab_input_registers[addr++];
    }
}
/***
* @brief 对保持寄存器进行写操作
*/
void CDataMapping::SetHoldRegisters(const uint16_t *src,int addr,const int nb)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=src);

    for(int i=0;i<nb;i++)
    {
        this->m_pmb_mapping->tab_registers[addr++]=src[i];
    }
}
/***
* @brief 对保持寄存器进行读操作
*/
void CDataMapping::GetHoldRegisters(int addr, const int nb, uint16_t *dest)
{
    assert(0==addr||0<addr);
    assert(0<nb);
    assert(NULL!=dest);

    for(int i=0;i<nb;i++)
    {
        dest[i]=this->m_pmb_mapping->tab_registers[addr++];
    }

}

/***
* @brief 为modbus提供无缝接口
*/
modbus_mapping_t *CDataMapping::GetUnit()
{
    return this->m_pmb_mapping;

}
