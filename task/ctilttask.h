/**
* @file       ͷ�ļ�
* @brief      ����ģ��������
* @author     GuoJianwei & gjianw217@163.com
* @see        CTask  CFocusTask CSysTask CPanTask CZoomTask
*/
#ifndef DLP_TASK_CTILTTASK_H_
#define DLP_TASK_CTILTTASK_H_
#include "itask.h"
class CTiltTask:public ITask
{
public:
	CTiltTask();
	~CTiltTask();
	virtual void Init();
	virtual void ExecTask();
protected:
private:

};

#endif // DLP_TASK_CTILTTASK_H_


