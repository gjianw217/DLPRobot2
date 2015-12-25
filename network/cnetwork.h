/*
* @file   头文件
* @brief  定义网络类，用于管理与上位机的通信，并向下分发各命令任务
* @author GuoJianwei & gjianw217@163.com
*/

#ifndef DLP_NETWORK_CNETWORK_H_
#define DLP_NETWORK_CNETWORK_H_
#include "../dlp/dlp.h"

class CNetwork
{
public:
	CNetwork();
	~CNetwork();
	void SetModbus(PCModbus modbus);
	void SetSysTask(PCSysTask sys_task);
	void SetFocusTask(PCFocusTask focus_task);
	void SetZoomTask(PCZoomTask zoom_task);
	void SetPanTask(PCPanTask pan_task);
	void SetTiltTask(PCTiltTask tilt_task);

	void SetSysThread(PCTaskThread sys_thread);
	void SetFocusThread(PCTaskThread focus_thread);
	void SetZoomThread(PCTaskThread zoom_thread);
	void SetPanThread(PCTaskThread pan_thread);
	void SetTiltThread(PCTaskThread tilt_thread);

	void Init(const uint8_t &client_num);
	void Run();

	void Test();
private:
	void TriggerCmdTask(const DLPModbusCmd &cmd);
private:
	PCModbus m_pmodbus;
	PCSelect m_pselect;
	PCParse  m_pparse;
	PCControl m_pcontrol;

	PCSysTask m_psys_task;
	PCFocusTask m_pfocus_task;
	PCZoomTask m_pzoom_task;
	PCPanTask  m_ppan_task;
	PCTiltTask m_ptilt_task;

	PCTaskThread m_psysthread;
	PCTaskThread m_pfocusthread;
	PCTaskThread m_pzoomthread;
	PCTaskThread m_ppanthread;
	PCTaskThread m_ptiltthread;
	//int m_socket;
};

#endif // DLP_NETWORK_CNETWORK_H_


