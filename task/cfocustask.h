/**
* @file       头文件
* @brief      镜头聚焦模块任务类
* @author     GuoJianwei & gjianw217@163.com
* @see        CTask CSysTask CPanTask CZoomTask CTiltTask
*/
#ifndef DLP_TASK_CFOCUSTASK_H_
#define DLP_TASK_CFOCUSTASK_H_
#include "itask.h"
class CFocusTask:public ITask
{
public:
	CFocusTask();
	~CFocusTask();

	virtual void Init();//一定要在执行了SetAssembly函数后调用
	virtual void ExecTask();
private:


};

#endif // DLP_TASK_CFOCUSTASK_H_


