/**
* @file       ͷ�ļ�
* @brief      ��ͷ�佹ģ��������
* @author     GuoJianwei & gjianw217@163.com
* @see        CTask CFocusTask CSysTask CPanTaskCTiltTask
*/
#ifndef DLP_TASK_CZOOMTASK_H_
#define DLP_TASK_CZOOMTASK_H_
#include "itask.h"
class CZoomTask:public ITask
{
public:
	CZoomTask();
	~CZoomTask();
	virtual void Init();
	virtual void ExecTask();
protected:
private:

};
#endif// DLP_TASK_CZOOMTASK_H_
