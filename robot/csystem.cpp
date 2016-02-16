#include "crobot.h"
#include "csystem.h"
#include "../network/cdata-mapping.h"
#include "../devices/encoder/ccancoder.h"
#include "../devices/encoder/crs485coder.h"
#include "../devices/motors/cstepmotorbypru.h"
#include "../devices/motors/cstepmotorbypwm.h"
#include "../devices/motors/imotor.h"
#include "../devices/switch/cproximityswitch.h"
#include "../utils/cconverter.h"
#include "../devices/motors/cdirection.h"
#include "cmanagepulse.h"


CSystem::CSystem()
{
    m_pmanage_pulse=PCManagePulse(new CManagePulse);

}

CSystem::~CSystem()
{

}

void CSystem::SetRobot(PCRobot robot)
{
	this->m_probot=robot;
	//初始化各成员变量

}
void CSystem::SetDataMapping(PCDataMapping datamapping)
{
	this->m_pdatamapping=datamapping;
}

void CSystem::Init()
{
    dlp_log(DLP_LOG_DEBUG,"CSystem::Init()");
	if (m_probot.use_count()>0)
	{
        DLPRole role[]={DLP_PAN,DLP_TILT,DLP_FOCUS,DLP_ZOOM};

        m_ppan_coder=m_probot->GetCoder(role[0]);
        m_ppan_motor=m_probot->GetMotor(role[0]);
        m_ppan_switch=m_probot->GetSwitch(role[0]);
//
//		m_ptilt_coder=m_probot->GetCoder(role[1]);
//		m_ptilt_motor=m_probot->GetMotor(role[1]);
//		m_ptilt_switch=m_probot->GetSwitch(role[1]);

//		m_pfocus_coder=m_probot->GetCoder(role[2]);//Testing the motor amend algorithm
//		m_pfocus_motor=m_probot->GetMotor(role[2]);
//
//		m_pzoom_coder=m_probot->GetCoder(role[3]);
//		m_pzoom_motor=m_probot->GetMotor(role[3]);
//
//
//

    InitMotorAmendAttr();
	}
}
void CSystem::CollectSysData()
{
	dlp_log(DLP_LOG_INFOS,"CSystem::CollectSysData()");
    SLock datalock(m_mutex);
	time_t time_stamp;                                                                /*<采集数据的时间戳*/
	uint16_t time_array[2]={0};                                                       /*<存放时间戳：低位，高位*/
	uint16_t *pdata=&this->m_pdatamapping->GetUnit()->tab_input_registers[SYSTEM|S_GET_DATAS];/*<存放采集数据的地址单元*/
    DLPRole role;

    role=DLP_PAN;
    this->m_ppan_coder=this->m_probot->GetCoder(role);
    this->m_ppan_coder->GetData(pdata);
    //Debug
    printf("pan coder %d,%d\n",pdata[1],pdata[0]);

//    role=DLP_TILT;
//    this->m_ptilt_coder=this->m_probot->GetCoder(role);
//    this->m_ptilt_coder->GetData(pdata);
#ifdef DLP_CANOPEN_CODER
#endif // DLP_CAN_CODER


//    role=DLP_FOCUS;
//    this->m_pfocus_coder=this->m_probot->GetCoder(role);
//    role=DLP_ZOOM;
//    this->m_pzoom_coder=this->m_probot->GetCoder(role);
//
//    this->m_pfocus_coder->GetData(pdata);
//    this->m_pzoom_coder->GetData(pdata);
#ifdef DLP_RS485_CODER
#endif // DLP_RS485_CODER

	//Update the timestamp
	time_stamp=time(NULL);
	u322u16(time_stamp,time_array);
	this->m_pdatamapping->SetInputRegisters(time_array,SYSTEM|(S_GET_DATAS+12),2);                     /*<adding the timestamp*/

}
void CSystem::SysEStop()
{
//    dlp_log(DLP_LOG_DEBUG,"CSystem::SysEStop()");
//    m_ppan_motor->EmergencyStop();;
//    m_ptilt_motor->EmergencyStop();;
//    m_pfocus_motor->EmergencyStop();;
//    m_pzoom_motor->EmergencyStop();;
}
void CSystem::SysReturnOrigin()
{
//    dlp_log(DLP_LOG_DEBUG,"CSystem::SysReturnOrigin()");
//    m_ppan_motor->ReturnRefOrigin();
//    m_ptilt_motor->ReturnRefOrigin();;
//    m_pfocus_motor->ReturnRefOrigin();;
//    m_pzoom_motor->ReturnRefOrigin();;
}
void CSystem::SelfCheck()
{

//	LensFocusCheck();
//	LensZoomCheck();
//	ArmsPanCheck();
//	ArmsTiltCheck();


}


void CSystem::LensFocusCheck()
{

	////变量初始化
	//m_pfocus_sensor= m_probot->GetLensSensor(Lens_Focus_Sensor);
	//m_pfocus_motor = m_probot->GetLensDriver(Lens_Focus)->GetMotor();
	//DLPRS485Attr old_data,new_data;

	////开启电机转动
	//m_probot->GetLensDriver(Lens_Focus)->GetMotor()->GetDirection()->SetDirValue(0);
	//m_pfocus_motor->Start();
	//do
	//{
	//	m_pfocus_sensor->ReadData(old_data);
	//	m_pfocus_sensor->ReadData(new_data);

	//}while(old_data.dlp_rs485_data[0]==new_data.dlp_rs485_data[0]);//直到电机转到一边
	//m_pfocus_motor->Stop();
	////记录电机位置或量程

	////电机向另一方向转动
	//m_probot->GetLensDriver(Lens_Focus)->GetMotor()->GetDirection()->SetDirValue(1);
	//m_pfocus_motor->Start();
	//do
	//{
	//	m_pfocus_sensor->ReadData(old_data);
	//	m_pfocus_sensor->ReadData(new_data);

	//}while(old_data.dlp_rs485_data[0]==new_data.dlp_rs485_data[0]);//直到电机转到另一边
	//m_pfocus_motor->Stop();
	////记录电机位置或量程

	/////得到最大量程


}
void CSystem::LensZoomCheck()
{

}
void CSystem::ArmsPanCheck()
{
 //   //变量初始化
 //   m_ppan_motor=m_probot->GetArmsDriver(Arms_Pan)->GetMotor();
	//m_ppan_origin=m_probot->GetArmsDriver(Arms_Pan)->GetOrigin();
	//m_ppan_sensor=m_probot->GetArmSensor(Arms_Pan_Sensor);

	////电机开始转动
	//m_ppan_motor->Start();
 //   while(1)
 //   {
 //       if(m_ppan_origin->IsOn())//如果到初始零点
 //       {
 //           //stop
	//		m_ppan_motor->Stop();
 //           //跳出循环
	//		break;
 //       }
 //   }
 //   //
 //   //record current position infos
	//memset(m_data,0,5);
	//m_ppan_sensor->GetData(m_data);
	//m_ppan_sensor->CounterInit(); //coder clear the angle


}
void CSystem::ArmsTiltCheck()
{

}

void CSystem::ControlSysMotion()//driver the step motor movement
{
  dlp_log(DLP_LOG_INFOS,"CSystem::ControlSysMotion");
   if(m_pmanage_pulse->IsPulses())
   {

        m_pmanage_pulse->UpdatePulseGroup();
        m_pmanage_pulse->RunPulseGroup();

   }

}

int CSystem::AmendSysPulse()
{
    dlp_log(DLP_LOG_INFOS,"CSystem::AmendSysPulse()");
    DLPMotorPulse workmotor[4]={DLP_PULSE_PAN,DLP_PULSE_TILT,DLP_PULSE_ZOOM,DLP_PULSE_FOCUS}; /*<The current work of motor*/
    DLPMotorPulse amendmark[4]={DLP_PULSE_NO,DLP_PULSE_NO,DLP_PULSE_NO,DLP_PULSE_NO};         /*<Need to modify the motor*/
    uint16_t pamend_data[6]={0};

    float coder_angle=m_ppan_coder->GetCoderAngle();/*<Storing Coder angle and to judge the amend*/
    //debug test
    //float coder_angle=3.3;
    std::cout<<" CSystem::AmendSysPulse() "<<"coder->GetCoderAngle()"<<coder_angle<<std::endl;
    if(m_pmanage_pulse->IsAmend(DLP_PULSE_PAN,coder_angle))
    {
        std::cout<<"20160121 GetAmendParameter"<<std::endl;
        m_pmanage_pulse->GetAmendParameter(DLP_PULSE_PAN,pamend_data);
        std::cout<<"20160121 GetAmendParameter"<<std::endl;
        m_ppan_motor->SetCmdAmendPulses(pamend_data);
        std::cout<<"20160121 SetConvertEnable"<<std::endl;
        ConvertSysPulse();

    }



//    if(amendmark[DLP_PULSE_PAN]==DLP_PULSE_PAN)
//    {
//
//    }
//
//    if(amendmark[DLP_PULSE_TILT]==DLP_PULSE_TILT)
//    {
//
//    }
//
//    if(amendmark[DLP_PULSE_ZOOM]==DLP_PULSE_ZOOM)
//    {
//
//    }

//
    return 0;

}

void CSystem::ConvertSysPulse()
{
#ifdef DLP_DEBUG
    dlp_log(DLP_LOG_INFOS,"CSystem::ConvertSysPulse()");
    std::cout<<"[msg] convert enable(1) "<<m_pmanage_pulse->IsConvert(DLP_PULSE_PAN)<<std::endl;
    std::cout<<"[msg] command counter "<<m_ppan_motor->ReadCmdSize()<<std::endl;
#endif // DLP_DEBUG

    if(m_pmanage_pulse->IsConvert(DLP_PULSE_PAN) //a enable variable control wether convert the command
        &&m_ppan_motor->ReadCmdSize())         //check whether there is control motor motion command
    {
        uint32_t pulses[DLP_PULSE_MAX_FRAME]={0};//If a member variable,lead to segment errors
        m_ppan_motor->CmdConvertPulses();
        m_len=m_ppan_motor->ReadPulses(pulses);
        m_pmanage_pulse->UpdateCurvePulse(DLP_PULSE_PAN,m_len,pulses);
        float coder_angle=m_ppan_coder->GetCoderAngle();/*<Storing Coder angle and make it the base value*/
        m_pmanage_pulse->UpdateCurveAngle(DLP_PULSE_PAN,coder_angle);;
    }

//    if(m_pmanage_pulse->CheckCurveConvert(DLP_PULSE_PAN))
//    {
//
//        m_pmanage_pulse->SetConvertDisable(DLP_PULSE_PAN);
//    }
//
//    if(m_pmanage_pulse->CheckCurveConvert(DLP_PULSE_TILT))
//    {
//
//        m_pmanage_pulse->SetConvertDisable(DLP_PULSE_TILT);
//    }
//
//    if(m_pmanage_pulse->CheckCurveConvert(DLP_PULSE_ZOOM))
//    {
//
//        m_pmanage_pulse->SetConvertDisable(DLP_PULSE_ZOOM);
//    }

}

void CSystem::InitMotorAmendAttr()
{
    DLPMotorAttr mattr;
    DLPEncoderAttr eattr;
    DLPMotorPulse type;
                                                       /*<存放时间戳：低位，高位*/
	uint16_t *pdata=NULL;
	//Set Pan Attribute
	type=DLP_PULSE_PAN;
	pdata=&this->m_pdatamapping->GetUnit()->tab_registers[PANCODER|C_SET_GEAR];/*coder gear value address*/
	eattr.dlp_gear[0]=*pdata;
	eattr.dlp_gear[1]=*(++pdata);
	eattr.dlp_bits=*(++pdata);

	pdata=&this->m_pdatamapping->GetUnit()->tab_registers[PANMOTOR|M_SET_MAXSPEED];/*<motor gear value address*/
	mattr.dlp_algorithm.g.max_speed=*pdata;
	mattr.dlp_algorithm.g.division=*(pdata+3);
	mattr.dlp_algorithm.g.gear[0]=*(pdata+4);
	mattr.dlp_algorithm.g.gear[1]=*(pdata+5);
//
//    std::cout<<"CSystem::InitMotorAmendAttr"<<std::endl;
//        std::cout<<"coder gear "<<eattr.dlp_gear[0]<<":"<<eattr.dlp_gear[1]<<std::endl;
//        std::cout<<"coder bits "<<eattr.dlp_bits<<std::endl;
//        std::cout<<"motor gear "<<mattr.dlp_algorithm.gear[0]<<":"<<mattr.dlp_algorithm.gear[1]<<std::endl;
//        std::cout<<"motor speed "<<mattr.dlp_algorithm.max_speed<<std::endl;
//        std::cout<<"motor division "<<mattr.dlp_algorithm.division<<std::endl;

    m_pmanage_pulse->SetMotrAttr(type,mattr,eattr);

    //Set Tilt Attribute

    //Set Focus Attribute

    //Set Zoom Attribute


}
