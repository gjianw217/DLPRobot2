/**
* @file      头文件
* @brief     平摇模块的任务类
* @author     GuoJianwei & gjianw217@163.com
* @see        CTask  CFocusTask CSysTask CZoomTask CTiltTask
*/
#ifndef DLP_TASK_PANTASK_H_
#define DLP_TASK_PANTASK_H_
#include "itask.h"
class  CPanTask:public ITask
{
public:
	CPanTask();
	~CPanTask();
	virtual void ExecTask();
	virtual void Init();//一定要在执行了SetAssembly函数后调用

private:

};
#endif // DLP_TASK_PANTASK_H_



