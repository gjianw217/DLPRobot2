/**
* @file
* @brief
* @author     GuoJianwei & gjianw217@163.com
* @see        CFocusTask CSysTask CPanTask CZoomTask CTiltTask
*/
#ifndef DLP_TASK_ITASK_H_
#define DLP_TASK_ITASK_H_

#include <deque>
#include <boost/thread.hpp>
#include "../dlp/dlp.h"

class ITask
{
public:
	ITask();
	~ITask();
	void SetRobot(PCRobot robot);
	void SetDataMapping(PCDataMapping datamapping);
	void SetRefresh(PCRefresh refresh);

	void AddCommand(const DLPModbusCmd &modbus_cmd);
	void DelCommand();
	virtual void Init()=0;
	virtual void ExecTask()= 0;

protected:
	std::deque<DLPModbusCmd> m_cmds;
	boost::mutex  m_mutex;

    PCRobot m_probot; //get the equipment pointer to  control specific operation
	PCRefresh m_prefresh;    //update the parameter settings
	PCDataMapping m_pdatamapping;//The main use for CSystem in the CSysTask class

	PIEncoder m_pcoder;
	PIMotor   m_pmotor;
	DLPRole   m_role;
private:
};
#endif //DLP_TASK_ITASK_H_


