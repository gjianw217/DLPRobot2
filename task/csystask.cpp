#include "../robot/crobot.h"
#include "local/crefresh.h"
#include "../robot/csystem.h"
#include "csystask.h"
#include "../utils/cdebug.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
CSysTask::CSysTask():ITask()
{


}
CSysTask::~CSysTask(){}

void CSysTask::SetSystem(PCSystem system)
{
	dlp_log(DLP_LOG_DEBUG,"CSysTask::Init()");//std::cout<<m_probot.use_count()<<":"<<m_pdatamapping.use_count()<<std::endl;
	if (m_probot.use_count()>0&&m_pdatamapping.use_count()>0)
	{
		m_psys=system;
        m_psys->SetRobot(m_probot);
		m_psys->SetDataMapping(m_pdatamapping);
		m_psys->Init();
	}

}
void CSysTask::Init()
{
	dlp_log(DLP_LOG_DEBUG,"CSysTask::Init()");//std::cout<<m_probot.use_count()<<":"<<m_pdatamapping.use_count()<<std::endl;
	if (m_probot.use_count()>0&&m_pdatamapping.use_count()>0)
	{
		m_psys=PCSystem(new CSystem());
        m_psys->SetRobot(m_probot);
		m_psys->SetDataMapping(m_pdatamapping);
		m_psys->Init();
	}

}

/************************************************************************/
/*  ����ִ�к���                                                        */
/************************************************************************/
void CSysTask::ExecTask()
{
    dlp_log(DLP_LOG_DEBUG,"CSysTask::ExecTask()");
	if (m_psys.use_count()==0)
	{
		return ;
	}

	boost::shared_mutex c_mutex;
	boost::unique_lock<boost::shared_mutex> lock(c_mutex);//��֤��������˳��ִ�У�������������Ա�������ĸ���
	DLPModbusCmd exec_cmd ;
	int          cmd_num=m_cmds.size();
	int          exec_cmd_len;

	do
	{
		exec_cmd = m_cmds.at(cmd_num-- -1);/*<ȡ����ͷ�����������1*/
		DelCommand();                      /*<������ɾ����ȡ��������*/
		exec_cmd_len=exec_cmd.cmd_len;
		if(MODBUS_COILS==exec_cmd.reg_type)
		{
			switch(exec_cmd.dev_func)
			{
				case S_COLLECT_DATA:
				{
                    m_psys->ConvertSysPulse();
					break;
				}
				case S_RETURN_REF:
				{
                    m_psys->SysReturnOrigin();
                    break;
				}
				case S_STOP:
				{
                    m_psys->SysEStop();;
                    break;
				}
				default:
				{
                    std::cout<<exec_cmd.dev_func<<std::endl;
                     //m_psys->ConvertSysPulse();
                    // m_psys->AmendSysPulse();
					dlp_log(DLP_LOG_ERR,"CSysTask::MODBUS_COILS:NoCMD");
				}
			}//end switch
		}//end if
		else if (MODBUS_HOLDING_REGISTERS==exec_cmd.reg_type)
		{
			switch(exec_cmd.dev_func)
			{
				case S_SET_ID: /*<���ÿ�������id*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
				case S_OS: /*<ϵͳ�Ĳ���ϵͳ��*/
                {
                    m_prefresh->Update(exec_cmd,true);
                    break;
                }
				case S_VERSION :/*<ϵͳ�İ汾��*/
                {
                    m_prefresh->Update(exec_cmd,true);
                    break;
                }
				case S_PRODUCTION_TIME:/*<ϵͳ�ĳ���ʱ�� */
                {
                    m_prefresh->Update(exec_cmd,true);
                    break;
                }
				case S_MODEL:/*<ϵͳ���ͺ�*/
                {
                    m_prefresh->Update(exec_cmd,true);
                    break;
                }
				case S_SN: /*<ϵͳ�����к�*/
                {
                    m_prefresh->Update(exec_cmd,true);
                    break;
                }
                default:
                {
					dlp_log(DLP_LOG_ERR,"CSysTask::MODBUS_HOLDING_REGISTERS:NoCMD");
                }
			}//end switch
		}//end else if
		else
		{
			exec_cmd_len=0;/*<�˳�*/
			dlp_log(DLP_LOG_ERR,"CSysTask::ExecTask()::AssignTask:NDFUN");
		}//else
	}while(exec_cmd_len>0&&cmd_num>0);
}

void CSysTask::CollectSysData()
{
     m_psys->CollectSysData();
}

void CSysTask::ControlSysMotion()
{
    m_psys->ControlSysMotion();
}

void CSysTask::UpdateSysValue()
{
   // m_psys->UpdateSysValue();
}
