/**
* @file       ͷ�ļ�
* @brief      ��ͷ�۽�ģ��������
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

	virtual void Init();//һ��Ҫ��ִ����SetAssembly���������
	virtual void ExecTask();
private:


};

#endif // DLP_TASK_CFOCUSTASK_H_


