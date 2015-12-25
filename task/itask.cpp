#include "itask.h"
/************************************************************************/
/*                                                                     */
/************************************************************************/
ITask::ITask(){}
ITask::~ITask(){}
/************************************************************************/
/*                                                                    */
/************************************************************************/
void ITask::SetRobot(PCRobot robot)
{
    this->m_probot=robot;
}

void ITask::SetDataMapping(PCDataMapping datamapping)
{
	this->m_pdatamapping=datamapping;
}
void ITask::SetRefresh(PCRefresh refresh)
{
	m_prefresh=refresh;
}
/************************************************************************/
/*  Add and remove command                                                */
/************************************************************************/
void ITask::AddCommand(const DLPModbusCmd &modbus_cmd)
{
	this->m_cmds.push_back(modbus_cmd);//Insert the command queue tail, called by CNetwork::Run()
}
void ITask::DelCommand()
{
    this->m_cmds.pop_back();
}
