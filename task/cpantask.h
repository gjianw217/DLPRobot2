/**
* @file      ͷ�ļ�
* @brief     ƽҡģ���������
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
	virtual void Init();//һ��Ҫ��ִ����SetAssembly���������

private:

};
#endif // DLP_TASK_PANTASK_H_



