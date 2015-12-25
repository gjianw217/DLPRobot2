/*
* @file   头文件
* @brief  封装用于控制系统的类，该类控制云台各部分协调工作
* @author GuoJianwei & gjianw217@163.com
* @see
*/

#ifndef DLP_ROBOT_CSYSTEM_H_
#define DLP_ROBOT_CSYSTEM_H_

#include "../dlp/dlp.h"
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
typedef boost::shared_mutex SMutex;
typedef boost::shared_lock<SMutex> SLock;
typedef boost::unique_lock<SMutex> ULock;

class CSystem
{
public:
	CSystem();
	~CSystem();

	void SetRobot(PCRobot robot);
	void SetDataMapping(PCDataMapping datamapping);

	void CollectSysData();
	void ControlSysMotion();;
	int  AmendSysPulse();
	void ConvertSysPulse();

	void SysEStop();
	void SysReturnOrigin();
	void SelfCheck();

	void Init();
private:
    SMutex m_mutex;

private:

	void LensFocusCheck();
	void LensZoomCheck();
	void ArmsPanCheck();
	void ArmsTiltCheck();
private:
	PCRobot m_probot;
	PCDataMapping m_pdatamapping;

	PIEncoder m_pfocus_coder;
	PIEncoder m_pzoom_coder;
	PIEncoder m_ppan_coder;
	PIEncoder m_ptilt_coder;

	PIMotor m_pfocus_motor;
	PIMotor m_pzoom_motor;
	PIMotor m_ppan_motor;
	PIMotor m_ptilt_motor;

	PCProximitySwitch m_ppan_switch;
	PCProximitySwitch m_ptilt_switch;


    PCManagePulse m_pmanage_pulse;
private:
	uint16_t m_data[5];//save the coder value respectively
    uint32_t m_pulses[100];
    uint32_t m_len;

};
#endif // DLP_ROBOT_CSYSTEM_H_
