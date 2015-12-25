#include "crobot.h"
#include "csystem.h"
#include "../network/cdata-mapping.h"
#include "../devices/encoder/ccancoder.h"
#include "../devices/encoder/crs485coder.h"
#include "../devices/motors/cstepmotorbypru.h"
#include "../devices/motors/cstepmotorbypwm.h"
#include "../devices/motors/imotor.h"
#include "../devices/switch/cproximityswitch.h"

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

		m_pfocus_coder=m_probot->GetCoder(role[2]);//Testing the motor amend algorithm
		m_pfocus_motor=m_probot->GetMotor(role[2]);
//
//		m_pzoom_coder=m_probot->GetCoder(role[3]);
//		m_pzoom_motor=m_probot->GetMotor(role[3]);
//
//
//
	}
}
void CSystem::CollectSysData()
{
	dlp_log(DLP_LOG_DEBUG,"CSystem::CollectSysData()");
//    SLock datalock(m_mutex);
//	time_t time_stamp;                                                                /*<采集数据的时间戳*/
//	uint16_t time_array[2]={0};                                                       /*<存放时间戳：低位，高位*/
//	uint16_t *pdata=&this->m_pdatamapping->GetUnit()->tab_input_registers[SYSTEM|S_GET_DATAS];/*<存放采集数据的地址单元*/
//    DLPRole role;
//#ifdef DLP_CANOPEN_CODER
//    role=DLP_PAN;
//    this->m_ppan_coder=this->m_probot->GetCoder(role);
//    role=DLP_TILT;
//    this->m_ptilt_coder=this->m_probot->GetCoder(role);
//
//    this->m_ppan_coder->GetData(pdata);
//    this->m_ptilt_coder->GetData(pdata);
//#endif // DLP_CAN_CODER
//
//#ifdef DLP_RS485_CODER
//    role=DLP_FOCUS;
//    this->m_pfocus_coder=this->m_probot->GetCoder(role);
//    role=DLP_ZOOM;
//    this->m_pzoom_coder=this->m_probot->GetCoder(role);
//
//    this->m_pfocus_coder->GetData(pdata);
//    this->m_pzoom_coder->GetData(pdata);
//
//#endif // DLP_RS485_CODER
//
//	更斗ש״戳*/
//	time_stamp=time(NULL);
//	u322u16(time_stamp,time_array);
//	this->m_pdatamapping->SetInputRegisters(time_array,SYSTEM|(S_GET_DATAS+12),2);                     /*<加入时间戮*/

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
   if(m_pmanage_pulse->CheckMotorPulse())
   {
        m_pmanage_pulse->UpdatePulseGroup();
        m_pmanage_pulse->RunPulseGoup();

   }

}

int CSystem::AmendSysPulse()
{

    DLPMotorPulse workmotor[4]={DLP_PULSE_PAN,DLP_PULSE_TILT,DLP_PULSE_ZOOM,DLP_PULSE_FOCUS}; /*<The current work of motor*/
    DLPMotorPulse amendmark[4]={DLP_PULSE_NO,DLP_PULSE_NO,DLP_PULSE_NO,DLP_PULSE_NO};         /*<Need to modify the motor*/
    uint16_t pamend_data[6]={0};

    //float coder_angle=m_ppan_coder->GetCoderAngle();/*<Storing Coder angle and to judge the amend*/
    //debug test
    float coder_angle=3.3;
    if(m_pmanage_pulse->IsAmend(DLP_PULSE_PAN,coder_angle))
    {
        m_pmanage_pulse->GetAmendParameter(DLP_PULSE_PAN,pamend_data);
        std::cout<<"20151225 GetAmendParameter"<<std::endl;
        m_ppan_motor->SetCmdAmendPulses(pamend_data);
        std::cout<<"20151225 SetCmdAmendPulses"<<std::endl;
        m_pmanage_pulse->SetConvertEnable(DLP_PULSE_PAN);
        std::cout<<"20151225 SetConvertEnable"<<std::endl;
        m_ppan_motor->CmdConvertPulses();
        std::cout<<"20151225 CmdConvertPulses"<<std::endl;
        m_len=m_ppan_motor->ReadPulses(m_pulses);
        std::cout<<"20151225 ReadPulses"<<std::endl;
        m_pmanage_pulse->UpdateCurvePulse(DLP_PULSE_PAN,//curve type T=1
                                        m_len,
                                        m_pulses);
        std::cout<<"20151225 UpdateCurvePulse"<<std::endl;
        m_pmanage_pulse->SetConvertDisable(DLP_PULSE_PAN);
        std::cout<<"20151225 SetConvertDisable"<<std::endl;


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
    std::cout<<"ConvertSysPulse"<<std::endl;
    std::cout<<m_pmanage_pulse->CheckCurveConvert(DLP_PULSE_PAN)<<std::endl;
    std::cout<<m_ppan_motor->ReadCmd()<<std::endl;

    if(m_pmanage_pulse->CheckCurveConvert(DLP_PULSE_PAN) //a enable variable control wether convert the command
        &&m_ppan_motor->ReadCmd())         //check whether there is control motor motion command
    {
        m_ppan_motor->CmdConvertPulses();
        std::cout<<"CmdConvertPulses"<<std::endl;
        m_len=m_pfocus_motor->ReadPulses(m_pulses);
        std::cout<<"ReadPulses"<<std::endl;

        m_pmanage_pulse->UpdateCurvePulse(DLP_PULSE_PAN,//curve type T=1
                                        m_len,m_pulses);
        std::cout<<"UpdateCurvePulse"<<std::endl;

        m_pmanage_pulse->SetConvertDisable(DLP_PULSE_PAN);
        std::cout<<"SetConvertDisable"<<std::endl;

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
