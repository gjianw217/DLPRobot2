/**
* @file       头文件
* @brief      系统模块任务类
* @author     GuoJianwei & gjianw217@163.com
* @see        CTask  CFocusTaskCPanTask CZoomTask CTiltTask
*/
#ifndef DLP_TASK_CSYSTASK_H_
#define DLP_TASK_CSYSTASK_H_
#include "itask.h"
class CSysTask:public ITask
{
public:
	CSysTask();
	~CSysTask();
	virtual void ExecTask();
	virtual void Init();
	void SetSystem(PCSystem system);
	void CollectSysData();
	void ControlSysMotion();
	void UpdateSysValue();

private:
	PCSystem m_psys;
};

#endif//DLP_TASK_CSYSTASK_H_
