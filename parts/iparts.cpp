//#include "ipartsfactory.h"
//
//IPartsFactory::IPartsFactory()
//{
//
//}
//
//IPartsFactory::IPartsFactory(PCDataMapping datamapping)
//{
//	m_pdatamapping=datamapping;
//}
//IPartsFactory::~IPartsFactory()
//{
//
//}
//#include "../utils/converter.h"
#include "iparts.h"
#include "../devices/encoder/ccancoder.h"
#include "../devices/encoder/crs485coder.h"
//#include "../devices/motors/cstepmotorbypwm.h"
//#include "../devices/motors/cstepmotorbypru.h"
#include "../devices/motors/cstepmotor.h"
#include "../devices/switch/cproximityswitch.h"
#include "../network/cdata-mapping.h"
#include <sstream>


IParts::IParts(PCDataMapping datamapping)
{
    m_pdatamapping=datamapping;
}

IParts::~IParts()
{

}

PIEncoder IParts::GetCoder()
{
    return m_pcoder;
}
PIMotor IParts::GetMotor()
{
    return m_pmotor;
}
PCProximitySwitch IParts::GetSwitch()
{
    return m_pswitch;
}
PIEncoder IParts::CreateCoder(DLPCoderType type,DLPRole role)
{
    std::string com;
    uint8_t id;
    if(CAN_CODER_BOCHEN==type)
    {
        id=getCoderConfigID(role);
        m_pcoder=PCCANCoder(new CCANCoder(id));/////////////////////////////////
       // m_pcoder=PCCANCoder(new CCANCoder(0x21));
    }
    else if(RS485_CODER_BOCHEN==type)
    {
        com=getCoderConfigCom(role);
        m_pcoder=PCRS485Coder(new CRS485Coder(com));
    }
    else
    {
        m_pmotor.reset();
    }
    return m_pcoder;
}

PIMotor IParts::CreateMotor(DLPMotorType type,DLPRole role)
{
    m_pmotor=PCStepMotor(new CStepMotor());
//    std::string str;
//    if(STEP_MOTOR_BY_PRU==type)
//    {
//        str=getMotorDriverPRU(role);
//        m_pmotor=PCStepMotorbyPRU(new CStepMotorbyPRU(str));
//    }
//    else if(STEP_MOTOR_BY_PWM==type)
//    {
//        str=getMotorDriverPin(role);
//        m_pmotor=PCStepMotorbyPWM(new CStepMotorbyPWM(str));
//    }
//    else
//    {
//        m_pmotor.reset();
//    }

    return m_pmotor;

}

PCProximitySwitch IParts::CreateSwitch(DLPSwitchType type,DLPRole role)
{
    return m_pswitch=PCProximitySwitch(new CProximitySwitch());

}

uint8_t IParts::getCoderConfigID(DLPRole &role)
{
    uint16_t id;
    m_pdatamapping->GetHoldRegisters((role+1)<<8,1,&id);//ZOOM==3,FOCUS==4,Zoom-Sensor=0x400,Focus-Sensor==0x500

    return id;
}
std::string IParts::getCoderConfigCom(DLPRole &role)
{
    std::string com="/dev/ttyO";
    std::ostringstream ost;
    uint16_t no;
    m_pdatamapping->GetHoldRegisters((role+1)<<8,1,&no);
    ost<<no;
    com=com+ost.str();

    return com;
}

std::string IParts::getMotorDriverPin(DLPRole &role)
{
    std::string pin;
    if(role=DLP_FOCUS)
    {
        pin="P8_34.11";
    }
    else
    {
        pin="P8_45.12";
    }

    return pin;
}
std::string IParts::getMotorDriverPRU(DLPRole &role)
{
    std::string pru;
    uint16_t data;
    m_pdatamapping->GetInputRegisters(role<<8,1,&data);
    if(data==0x12)
        pru=="pru0";
    else if(data==0x22)
        pru=="pru1";
    else pru="";

    return pru;
}
