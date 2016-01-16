#include "crobot.h"
#include "../parts/cfocuspart.h"
#include "../parts/czoompart.h"
#include "../parts/cpanpart.h"
#include "../parts/ctiltpart.h"

#include "../parts/cfocuspart.h"
#include "../devices/switch/cproximityswitch.h"

#include "../utils/cdebug.h"

CRobot::CRobot(PCDataMapping datamapping)
{
	m_pdatamapping=datamapping;
	//Init();
}

CRobot::~CRobot()
{

}
/*need to judge the return value*/
PIEncoder CRobot::GetCoder(DLPRole &role)
{
	std::map<DLPRole,PIEncoder>::iterator dlp_iterator;
	dlp_iterator=m_coders.find(role);
	if (dlp_iterator==m_coders.end())
	{
		//CreateParts(role);
		m_coders[role].reset();
	}

	return m_coders[role];
}


PIMotor CRobot::GetMotor(DLPRole &role)
{
	std::map<DLPRole,PIMotor>::iterator dlp_iterator;
	dlp_iterator=m_motors.find(role);
	if (dlp_iterator==m_motors.end())
	{
		//CreateParts(role);
		m_motors[role].reset();
	}
	return m_motors[role];
}

PCProximitySwitch CRobot::GetSwitch(DLPRole &role)
{
	std::map<DLPRole,PCProximitySwitch>::iterator dlp_iterator;
	dlp_iterator=m_switchs.find(role);
	if (dlp_iterator==m_switchs.end())
	{
		m_switchs[role].reset();
		//CreateParts(role);
	}
	return m_switchs[role];
}

void CRobot::Init()
{
    dlp_log(DLP_LOG_DEBUG,"--------------------------------------------");
    dlp_log(DLP_LOG_DEBUG,"Robot::PanPart-----------------------");
    m_ppan=PCPanPart(new CPanPart(m_pdatamapping));
    m_ppan->Init();                          //create the devices(coder motor switch) and config the attribute
    m_coders[DLP_PAN]=m_ppan->GetCoder();   //IPart implement
    m_motors[DLP_PAN]=m_ppan->GetMotor();
    m_switchs[DLP_PAN]=m_ppan->GetSwitch();

//    dlp_log(DLP_LOG_DEBUG,"Robot::FocusPart-----------------------");
//    m_pfocus=PCFocusPart(new CFocusPart(m_pdatamapping));
//    m_pfocus->Init();                                      //create the coder and motor
//    m_coders[DLP_FOCUS]=m_pfocus->GetCoder();
//    m_motors[DLP_FOCUS]=m_pfocus->GetMotor();
//
//    dlp_log(DLP_LOG_DEBUG,"--------------------------------------------");
}
void CRobot::CreateParts()
{
    std::cout<<"CRobot::CreateParts"<<std::endl;
//	switch(role)
//	{
//	case DLP_PAN:
//		{
//
//			break;
//		}
//	case DLP_TILT:
//		{
//
//			break;
//		}
//	case DLP_FOCUS:
//		{
//
//
//			break;
//		}
//	case DLP_ZOOM:
//		{
//
//			break;
//		}
//
//	}
}
