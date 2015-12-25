
#include "../devices/motors/cstepmotorbypru.h"
#include "../devices/encoder/ccancoder.h"
#include "../robot/crobot.h"
#include "local/crefresh.h"

#include "ctilttask.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
CTiltTask::CTiltTask():ITask()
{
    m_role=DLP_TILT;
}
CTiltTask::~CTiltTask()
{

}
void CTiltTask::Init()
{
    if (m_probot.use_count()>0)
	{
		m_pmotor=m_probot->GetMotor(m_role);
	}
}
/************************************************************************/
/*  ����ִ�к���                                                        */
/************************************************************************/
void CTiltTask::ExecTask()
{
	dlp_log(DLP_LOG_DEBUG,"CTiltTask::ExecTask()");
    if(1>m_pmotor.use_count())
    {
        return;
    }
	boost::shared_mutex c_mutex;
	boost::unique_lock<boost::shared_mutex> lock(c_mutex);
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
			case M_RETURN_ORIGIN:
                {
                    m_pmotor->ReturnRefOrigin();
                    break;
                }
                case M_ESTOP:
                {
                    m_pmotor->EmergencyStop();
                    break;
                }
			default:
				{
					dlp_log(DLP_LOG_ERR,"CTiltTask::MODBUS_COILS:NoCMD");
				}

			}//end switch
		}// end if
		else if (MODBUS_HOLDING_REGISTERS==exec_cmd.reg_type)
		{
			switch(exec_cmd.dev_func)
			{

				case M_SET_MAXSPEED: /*<�����������ٶȣ��������ٶ�*/
			{
				m_prefresh->Update(exec_cmd,true);

				break;
			}
			case M_SET_MINSPEED:/*<�����С�����ٶȣ��������ٶ�*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_ATIME: /*<�����������ʱ�� */
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_FACTOR: /*<�������ϸ����*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_GEAR: /*<���������*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_CURVE:/*<������������㷨*/
			{
				m_pmotor->ModifyCurve(static_cast<const DLPMotorCurveType>(exec_cmd.cmd_data[0]));
				m_prefresh->Update(exec_cmd,true);
				break;
			}
			case M_SET_ROTATION:/*<���������ת�㷨*/
			{
				m_pmotor->ModifyRotation(static_cast<const DLPMotorRotationType>(exec_cmd.cmd_data[0]));
				m_prefresh->Update(exec_cmd,true);
				break;
			}
			case M_RUNNING_TIME:
				{
					uint16_t coder_value[5]={0};
					if(exec_cmd_len == 5)
					{
						//m_pdm->GetInputRegisters(0x805, 3, coder_value);
				//m_pmotor->RunningbyTime(exec_cmd.cmd_data,5);
					}
					break;
				}
			case M_RUNNING_ANGLE:
			{
				uint16_t coder_value[3]={0};

				if (exec_cmd_len == 3)
				{
                        //m_pmotor->RunbyAngle(u162d32(exec_cmd.cmd_data),exec_cmd.cmd_data[2]);
				}
				break;
			}
			default:
				{
					dlp_log(DLP_LOG_ERR,"CTiltTask::MODBUS_HOLDING_REGISTERS:NoCMD");
				}
			}//switch
		}//end else if
		else
		{
			exec_cmd_len=0;
			dlp_log(DLP_LOG_ERR,"CTiltTask::ExecTask()::AssignTask:NDFUN");
		}//end else

	}while(exec_cmd_len>0&&cmd_num>0);
}


