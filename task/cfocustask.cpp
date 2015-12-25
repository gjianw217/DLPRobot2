#include "../devices/motors/cstepmotorbypwm.h"
#include "../devices/encoder/crs485coder.h"
#include "../robot/crobot.h"
#include "local/crefresh.h"
#include "cfocustask.h"
#include "../utils/cconverter.h"

/************************************************************************/
/*     ��������������                                                  */
/************************************************************************/

CFocusTask::CFocusTask():ITask()
{
    m_role=DLP_FOCUS;
}
CFocusTask::~CFocusTask(){}
/*
* @brief ��ʼ����ͷ�ľ۽�����;۽��������Ŀ���ָ��
* @note  �ú���������ָ֤��m_passembly��Ϊ��
*/

void CFocusTask::Init()
{
    if (m_probot.use_count()>0)
	{
		m_pmotor=m_probot->GetMotor(m_role);
	}
}

/************************************************************************/
/*  ����ִ�к���                                                        */
/************************************************************************/
void CFocusTask::ExecTask()
{
	dlp_log(DLP_LOG_DEBUG,"CFocusTask::ExecTask()");
	 if(1>m_pmotor.use_count())
    {
        return;
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

			case M_SET_MAXSPEED: /*<�����������ٶȣ��������ٶ�*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_MINSPEED: /*<�����С�����ٶȣ��������ٶ�*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_GEAR:/*<���������*/
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
			case M_SET_PERIOD:/*<PWM��������  !!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_DUTY:/*<PWM����ռ�ձ�!!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_POLARIT: /*<PWM���м���!!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_SET_RUN:/*<PWM����״̬!!!!!!20150515!!!!!*/
				{
					m_prefresh->Update(exec_cmd,true);
					break;
				}
			case M_RUNNING_TIME:
				{
					uint16_t coder_value[5]={0};
					if(exec_cmd_len == 5)               /*ʱ�� �� �Ƕ� �� ������� */
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
			exec_cmd_len=0;/*<�˳�*/
			dlp_log(DLP_LOG_ERR,"CFocusTask::ExecTask()::AssignTask:NDFUN");
		}//end else

	}while(exec_cmd_len>0&&cmd_num>0);/*<���뱣֤�������ݵĳ��Ȳ�Ϊ0������������Ϊ0*/

}
