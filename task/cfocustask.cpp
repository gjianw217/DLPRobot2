#include "../devices/motors/cstepmotorbypwm.h"
#include "../devices/encoder/crs485coder.h"
#include "../robot/crobot.h"
#include "local/crefresh.h"
#include "cfocustask.h"
#include "../utils/cconverter.h"

/************************************************************************/
/*     构造与析构函数                                                  */
/************************************************************************/

CFocusTask::CFocusTask():ITask()
{
    m_role=DLP_FOCUS;
}
CFocusTask::~CFocusTask(){}
/*
* @brief 初始化镜头的聚焦电机和聚焦编码器的控制指针
* @note  该函数，即保证指针m_passembly不为空
*/

void CFocusTask::Init()
{
    if (m_probot.use_count()>0)
	{
		m_pmotor=m_probot->GetMotor(m_role);
	}
}

/************************************************************************/
/*  任务执行函数                                                        */
/************************************************************************/
void CFocusTask::ExecTask()
{
	dlp_log(DLP_LOG_DEBUG,"CFocusTask::ExecTask()");
	 if(1>m_pmotor.use_count())
    {
        return;
    }
	boost::shared_mutex c_mutex;
	boost::unique_lock<boost::shared_mutex> lock(c_mutex);//保证本次任务顺利执行，以免连续命令对本次任务的干扰
	DLPModbusCmd exec_cmd ;
	int          cmd_num=m_cmds.size();
	int          exec_cmd_len;

	do
	{
		exec_cmd = m_cmds.at(cmd_num-- -1);/*<取出队头命令，命令数减1*/
		DelCommand();                      /*<队列中删除刚取出的命令*/
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
					dlp_log(DLP_LOG_ERR,"CFocusTask:MODBUS_COILS:NoCMD");
				}

			}//end switch
		}// end if
		else if (MODBUS_HOLDING_REGISTERS==exec_cmd.reg_type)
		{
			switch(exec_cmd.dev_func)
			{

			case M_SET_MAXSPEED: /*<电机最大运行速度，即正常速度*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_MINSPEED: /*<电机最小运行速度，即启动速度*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_GEAR:/*<电机齿数比*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_CURVE:/*<电机运行曲线算法*/
			{
				m_pmotor->ModifyCurve(static_cast<const DLPMotorCurveType>(exec_cmd.cmd_data[0]));
				m_prefresh->Update(exec_cmd,true);
				break;
			}
			case M_SET_ROTATION:/*<电机运行旋转算法*/
			{
				m_pmotor->ModifyRotation(static_cast<const DLPMotorRotationType>(exec_cmd.cmd_data[0]));
				m_prefresh->Update(exec_cmd,true);
				break;
			}
			case M_SET_PERIOD:/*<PWM运行周期  !!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_DUTY:/*<PWM运行占空比!!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_POLARIT: /*<PWM运行极性!!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_RUN:/*<PWM运行状态!!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_RUNNING_TIME:
				{
					uint16_t coder_value[5]={0};
					if(exec_cmd_len == 5)               /*时间 ＋ 角度 ＋ 方向组合 */
					{
						//m_pdm->GetInputRegisters(0x805, 3, coder_value);
//						m_pmotor->RunningbyTime(exec_cmd.cmd_data,5);
                        dlp_log(DLP_LOG_DEBUG,"--------------------------------------");


                        //m_pmotor->WriteCmd(exec_cmd);
					}
					break;
				}
			case M_RUNNING_ANGLE:
				{
                    dlp_log(DLP_LOG_DEBUG,"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
                    m_pmotor->WriteCmd(exec_cmd);
					break;
				}
			default:
				{
					dlp_log(DLP_LOG_ERR,"CFocusTask:MODBUS_HOLDING_REGISTERS:NoCMD");
				}
			}//switch
		}//end else if
		else
		{
			exec_cmd_len=0;/*<退出*/
			dlp_log(DLP_LOG_ERR,"CFocusTask::ExecTask()::AssignTask:NDFUN");
		}//end else

	}while(exec_cmd_len>0&&cmd_num>0);/*<必须保证命令数据的长度不为0，且命令数不为0*/

}
