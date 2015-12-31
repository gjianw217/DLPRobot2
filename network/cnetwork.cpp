#include "../utils/ctaskthread.h"
#include "../task/cfocustask.h"
#include "../task/cpantask.h"
#include "../task/ctilttask.h"
#include "../task/czoomtask.h"
#include "../task/csystask.h"
#include "ccontrol.h"
#include "cmodbus.h"
#include "cparse.h"
#include "cselect.h"
#include "cnetwork.h"
//#include <sys/select.h>
#include "../utils/cdebug.h"

CNetwork::CNetwork()
{
	m_pselect=PCSelect(new CSelect()); //Asynchronous concurrent server
	m_pparse=PCParse(new CParse());    //Parse the PC command
	m_pcontrol=PCControl(new CControl());
}

CNetwork::~CNetwork()
{

}

void CNetwork::SetModbus(PCModbus modbus)
{
	this->m_pmodbus=modbus;
	m_pcontrol->SetDataMapping(this->m_pmodbus->GetDataMapping());
}

void CNetwork::SetSysTask(PCSysTask sys_task)
{
	this->m_psys_task=sys_task;
}

void CNetwork::SetFocusTask(PCFocusTask focus_task)
{
	this->m_pfocus_task=focus_task;
}
void CNetwork::SetZoomTask(PCZoomTask zoom_task)
{
	this->m_pzoom_task=zoom_task;
}
void CNetwork::SetPanTask(PCPanTask pan_task)
{
	this->m_ppan_task=pan_task;
}
void CNetwork::SetTiltTask(PCTiltTask tilt_task)
{
	this->m_ptilt_task=tilt_task;
}

void CNetwork::SetSysThread(PCTaskThread sys_thread)
{
	this->m_psysthread=sys_thread;
}
void CNetwork::SetFocusThread(PCTaskThread focus_thread)
{
	this->m_pfocusthread=focus_thread;
}
void CNetwork::SetZoomThread(PCTaskThread zoom_thread)
{
	this->m_pzoomthread=zoom_thread;
}
void CNetwork::SetPanThread(PCTaskThread pan_thread)
{
	this->m_ppanthread=pan_thread;
}
void CNetwork::SetTiltThread(PCTaskThread tilt_thread)
{
	this->m_ptiltthread=tilt_thread;
}

void CNetwork::Init(const uint8_t &client_num)
{
	uint8_t num;
	if (client_num<0||client_num>256)
	{
		//num=SERVER_LISTEN_NUM;
		num=5;
	}
	else
	{
		num=client_num;
	}
	m_pselect->server_sock=m_pmodbus->ListenNum(num);
	m_pselect->fdZero(&m_pselect->refset);
	m_pselect->fdSet(m_pselect->server_sock,&m_pselect->refset);
	m_pselect->fdmax=m_pselect->server_sock;
}
/************************************************************************/
/*                                                           */
/************************************************************************/
void CNetwork::Run()
{

	int ret,ret_len;
	bool dlp_no_exit=true;
	int master_socket,new_socket;
	std::string new_ip;          //
	uint8_t client_cmd[256]={0};
	DLPModbusCmd parse_cmd;

    //struct timeval timeout= {10,00}; //set the server multiplexing I/O nonblocking
	do
	{
		dlp_log(DLP_LOG_DEBUG,"CNetwork::Run:Server is Running");
		m_pselect->curset=m_pselect->refset;
		//ret=m_pselect->select(m_pselect->fdmax+1,&m_pselect->curset,NULL,NULL,NULL);
		//ret=select(m_pselect->fdmax+1,&m_pselect->curset,NULL,NULL,&timeout);//timeout
		ret=select(m_pselect->fdmax+1,&m_pselect->curset,NULL,NULL,NULL);//timeout=NULL==> blocking model
		switch(ret)
		{
            case -1:dlp_log_value(DLP_LOG_DEBUG,strerror(errno),errno);break;
            case 0: dlp_log(DLP_LOG_DEBUG,"Server select() timeout");break;
            default:
			{
				for(master_socket=0; master_socket<=m_pselect->fdmax; master_socket++) //
				{
					if(m_pselect->fdIsset(master_socket,&m_pselect->curset))
					{
						if(master_socket==m_pselect->server_sock) //the Client is asking a new connection
						{
							dlp_log(DLP_LOG_DEBUG,"CNetwork_Run::A New Connection Request");
							new_socket=m_pselect->newclient(new_ip);
							m_pcontrol->Start(new_socket,new_ip);
						}
						else
						{
							dlp_log(DLP_LOG_DEBUG,"CNetwork_Run::A Old Process Request");

							m_pmodbus->SetSocket(master_socket);
							ret_len=m_pmodbus->Receive(client_cmd);
							//if(DLP_FAILURE!=ret_len)
							if(Modbus_TCP_Network_DisConnection!=ret_len)
							{
								/*Modbus regulation, the maximum delay 0.5ms of receive and send */

								m_pmodbus->Reply(client_cmd,ret_len);
								//if write command ,namely control command
								if((MODBUS_WRITE_SINGLE_COIL==client_cmd[7]
								||MODBUS_WRITE_SINGLE_REGISTER==client_cmd[7]
								||MODBUS_WRITE_MULTIPLE_COILS==client_cmd[7]
								||MODBUS_WRITE_MULTIPLE_REGISTERS==client_cmd[7]))
								{
									//m_modbus->Show(0x000,3);//Debug
									ret=m_pparse->Parse(client_cmd,parse_cmd);/*<Parse PC Command*/
									if (m_pcontrol->GetControl(master_socket,parse_cmd))
									{
										TriggerCmdTask(parse_cmd);
									}
								}
							}//if(DLP_FAILURE!=ret_len)
							else
							{
								dlp_log_value(DLP_LOG_WARN,"CNetwork_Run::Connection closed on socket",master_socket);
								close(master_socket);

								m_pselect->fdClr(master_socket,&m_pselect->refset);
								if(master_socket==m_pselect->fdmax)
								{
									m_pselect->fdmax--;
								}
								//m_pcontrol->Close(m_socket);
							}

						}
					}//select.fdIsset if

				}//end for
			}//end switch default
		}//switch

	}while(dlp_no_exit);//end while
}

void CNetwork::Test()
{
    std::cout<<"Test CNetwork Signal Thread Response"<<std::endl;
    int ret;
    fd_set readfds;
    int fd;

    fd=m_pselect->server_sock;
    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd,&readfds);

        ret=select(fd+1,&readfds,NULL,NULL,NULL);
        if(ret<0)
        {
            printf("select error!\n");
            return ;
        }

        ret=FD_ISSET(fd,&readfds);
        if(ret>0)
        {
            printf("select\n");
        }

    }

	//    struct timeval timeout= {10,00}; //set the server multiplexing I/O nonblocking
	do
	{
		dlp_log(DLP_LOG_DEBUG,"CNetwork::Run:Server is Running");
		m_pselect->curset=m_pselect->refset;
		ret=select(m_pselect->fdmax+1,&m_pselect->curset,NULL,NULL,NULL);//timeout=NULL==> blocking model
		switch(ret)
		{
            case -1:dlp_log_value(DLP_LOG_DEBUG,strerror(errno),errno);break;
            case 0: dlp_log(DLP_LOG_DEBUG,"Server select() timeout");break;
            default:
                {
                    dlp_log(DLP_LOG_DEBUG,"Server select()");break;
                }
        }

    }while(1);
}
void CNetwork::TriggerCmdTask(const DLPModbusCmd &cmd)
{
	dlp_log(DLP_LOG_WARN,"Assign Task...");
	switch(cmd.task_type)
	{

		case SYS_TASK:
		{
			//this->m_sys_task->OnUpdate(m_cmd);
			dlp_log(DLP_LOG_WARN,"this->m_sys_taskthread->SigTask()");
			this-> m_psys_task->AddCommand(cmd);
			this->m_psysthread->SigTask();
			break;
		}
		case FOCUS_TASK:
		{
			//this->m_coder_task->OnUpdate(m_cmd);
			dlp_log(DLP_LOG_WARN,"this->m_focus_taskthread->SigTask()");
			this->m_pfocus_task->AddCommand(cmd);
			this->m_pfocusthread->SigTask();
			break;
		}
		case ZOOM_TASK:
		{
			//this->m_motor_task->OnUpdate(m_cmd);
			dlp_log(DLP_LOG_WARN,"this->m_zoom_taskthread->SigTask()");
			this->m_pzoom_task->AddCommand(cmd);
			this->m_pzoomthread->SigTask();
			break;
		}
		case PAN_TASK:
		{
			//this->m_lens_task->OnUpdate(m_cmd);
			dlp_log(DLP_LOG_WARN,"this->m_pan_taskthread->SigTask()");
			this->m_ppan_task->AddCommand(cmd);
			this->m_ppanthread->SigTask();
			break;
		}
		case TILT_TASK:
		{
			//this->m_lens_task->OnUpdate(m_cmd);
			dlp_log(DLP_LOG_WARN,"this->m_tilt_taskthread->SigTask()");
			this->m_ptilt_task->AddCommand(cmd);
			this->m_ptiltthread->SigTask();
			break;
		}
		default:
		{
			dlp_log(DLP_LOG_ERR,"CNetwork::Run:Command Error");;
		}

	}//end switch
}
