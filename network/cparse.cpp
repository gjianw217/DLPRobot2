
#include <cstdio>
#include <iostream>
#include "cparse.h"

CParse::CParse()
{
    this->m_device=NDDEV;
    this->m_function=NDFUN;
}

CParse::~CParse(){}

/* ------------------------------------------------------------------------------------------------------*/
/*                                          Modbus TCP Frame Format                                      */
/* ------------------------------------------------------------------------------------------------------*/
/*   [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [....]                                            */
/*   每个单元为一个字节，一般有12个单元，其中：
     单元0和单元1表示事务标识码，
	 单元2和单元3表示协议标识码，
	 单元4和单元5表示长度字段
     单元6表示单元标识码，
     单元7表示功能码，
	 单元8和单元9表示数据地址，
	 单元10，单元11以及后面的，表示传递的数据。                                                          */
/*   在此：使用[8]表示设备类型，[9]表示具体的设备功能，详见下面的解析函数                                */
/*                                                                    http://en.wikipedia.org/wiki/Modbus*/
/* ------------------------------------------------------------------------------------------------------*/

int CParse::Parse(const uint8_t *receive_cmd,DLPModbusCmd &cmd)
{
	ParseTask(receive_cmd,cmd);             /*<填充命令结构体任务选项*/
	ParseDeviceFunction(receive_cmd,cmd);   /*<填充命令结构体设备类型和功能类型选项*/
	ParseRegister(receive_cmd,cmd);         /*<填充命令结构体寄存器选项*/
	ParseCommand(receive_cmd,cmd);          /*<填充命令结构体数据及其长度*/
	//printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",receive_cmd[0],receive_cmd[1],receive_cmd[2],receive_cmd[3],receive_cmd[4],receive_cmd[5],receive_cmd[6],receive_cmd[7],receive_cmd[8],receive_cmd[9],receive_cmd[10]);
	//std::cout<<cmd.dev_type<<":"<<cmd.dev_func<<":"<<cmd.task_type<<":"<<cmd.reg_type<<":"<<cmd.cmd_len<<":"<<cmd.cmd_data[0]<<std::endl;
	return 0;
}

int CParse::ParseTask(const uint8_t *receive_cmd,DLPModbusCmd &cmd)
{
    assert(NULL!=receive_cmd);
    int dlp_dev=receive_cmd[8];
    printf("CParse::ParseTask %d\n",dlp_dev);
    switch(dlp_dev<<8)  /*设备码由3位16进制表示，故左移8位*/
    {
        case SYSTEM:    cmd.task_type=SYS_TASK;break;
        case ZOOMCODER:
        case ZOOMMOTOR: cmd.task_type=ZOOM_TASK;break;
        case FOCUSCODER:
        case FOCUSMOTOR:cmd.task_type=FOCUS_TASK;break;
        case PANMOTOR:
        case PANCODER:   cmd.task_type=PAN_TASK;break;
        case TILTCODER:
        case TILTMOTOR:  cmd.task_type=TILT_TASK;break;
        case PANSWINGCODER:
        case TILTSWINGCODER:
        default:cmd.task_type=NDTASK;break;
    }
    return 0;
}

int CParse::ParseDeviceFunction(const uint8_t *receive_cmd,DLPModbusCmd &cmd)
{
    assert(NULL!=receive_cmd);
    int dlp_dev=receive_cmd[8];
    switch(dlp_dev<<8)  /*设备码由3位16进制表示，故左移8位*/
    {
        case SYSTEM:         cmd.dev_type=SYSTEM;        cmd.dev_func=ParseSysFunction(receive_cmd)  ;break;   /*<控制系统各设备联动、系统软件信息等 */
        case LENS:           cmd.dev_type=LENS;                                                       break;   /*<镜头*/
        case ZOOMCODER:      cmd.dev_type=ZOOMCODER;     cmd.dev_func=ParseCoderFunction(receive_cmd);break;   /*<变焦编码器*/
        case FOCUSCODER:     cmd.dev_type=FOCUSCODER;    cmd.dev_func=ParseCoderFunction(receive_cmd);break;   /*<聚焦编码器*/
        case PANCODER:       cmd.dev_type=PANCODER;      cmd.dev_func=ParseCoderFunction(receive_cmd);break;   /*<平摇编码器*/
        case TILTCODER:      cmd.dev_type=TILTCODER;     cmd.dev_func=ParseCoderFunction(receive_cmd);break;   /*<俯仰编码器*/
        case PANSWINGCODER:  cmd.dev_type=PANSWINGCODER;                                              break;   /*<*/
        case TILTSWINGCODER: cmd.dev_type=TILTSWINGCODER;                                             break;   /*<*/
        case PANMOTOR:       cmd.dev_type=PANMOTOR;      cmd.dev_func=ParseMotorFunction(receive_cmd);break;   /*<平摇摇臂电机*/
        case TILTMOTOR:      cmd.dev_type=TILTMOTOR;     cmd.dev_func=ParseMotorFunction(receive_cmd);break;   /*<平摇摇臂电机*/
        case ZOOMMOTOR:      cmd.dev_type=ZOOMMOTOR;     cmd.dev_func=ParseMotorFunction(receive_cmd);break;   /*<平摇摇臂电机*/
        case FOCUSMOTOR:     cmd.dev_type=FOCUSMOTOR;    cmd.dev_func=ParseMotorFunction(receive_cmd);break;   /*<俯仰摇臂电机*/
        //case 0x0C,this->m_device=;break;
        default:             cmd.dev_type=NDDEV;
    }
	//std::cout<<"CParse::ParseDeviceFunction"<<cmd.dev_type<<std::endl;
	return 0;
}

int CParse::ParseRegister(const uint8_t *receive_cmd,DLPModbusCmd &cmd)
{
    assert(NULL!=receive_cmd);
    int dlp_register=receive_cmd[7];
    switch(dlp_register)
    {
        case MODBUS_WRITE_SINGLE_COIL:
        case MODBUS_WRITE_MULTIPLE_COILS:cmd.reg_type=MODBUS_COILS;break;
        case MODBUS_WRITE_SINGLE_REGISTER:
        case MODBUS_WRITE_MULTIPLE_REGISTERS:cmd.reg_type=MODBUS_HOLDING_REGISTERS;break;
        default:cmd.reg_type=NOREG;
    }
    return 0;
}

int CParse::ParseCommand(const uint8_t *receive_cmd,DLPModbusCmd &cmd)
{
    assert(NULL!=receive_cmd);
    /*取出命令*/
    int i,j=0,loop=1;
    uint8_t modbus_function= receive_cmd[7];
    switch(modbus_function)
    {
        /*Coil*/
        case MODBUS_WRITE_SINGLE_COIL:
        {
             cmd.cmd_len=1;
             if(0xFF==receive_cmd[10]) //0xFF or 0
            {
                cmd.cmd_data[0]=1;
            }
            else
            {
                cmd.cmd_data[0]=0;
            }
            break;
        }
        /*Register*/
        case MODBUS_WRITE_SINGLE_REGISTER:
        {
            cmd.cmd_len=1;
            cmd.cmd_data[0]=receive_cmd[10];
            cmd.cmd_data[0]=cmd.cmd_data[0]<<8;
            cmd.cmd_data[0]=cmd.cmd_data[0]|receive_cmd[11];
            break;
        }
        /*Coils*/
        case MODBUS_WRITE_MULTIPLE_COILS:
        /*Hold Registers*/
        {
            loop=receive_cmd[11];
            cmd.cmd_len=loop;
            for(i=0;i<loop;i++)
            {
                if(0==i%8)
                {
                    j=receive_cmd[i/8+13];
                }

                if(j&0x01)
                {
                    cmd.cmd_data[i]=1;
                }
                else
                {
                    cmd.cmd_data[i]=0;
                }
                j=j>>1;
            }
            break;

        }
        case MODBUS_WRITE_MULTIPLE_REGISTERS:
        {
            loop=receive_cmd[11];
            cmd.cmd_len=loop;

            for(i=0,j=13;i<loop;i++,j=j+2)/*<主要是将2个8位转成1 个16位*/
            {
                cmd.cmd_data[i]=receive_cmd[j];
                cmd.cmd_data[i]=cmd.cmd_data[i]<<8;
                cmd.cmd_data[i]=cmd.cmd_data[i]|receive_cmd[j+1];/*<注意这里是位与，不是逻辑与*/

            }
            break;

        }//case 0x10
        default:;
    }//switch

    return loop;
}



/**
* @brief  私有ParseSysFunction函数主要解析命令中有关系统的功能码
* @param  参数为从上位机接收到的命令
* @return 解析完成，返回功能码
* @note   根据低８位地址，解析出功能码
*/
FunctionType CParse::ParseSysFunction(const uint8_t *receive_cmd)
{
    assert(NULL!=receive_cmd);
    /*Coil*/
    if(MODBUS_WRITE_SINGLE_COIL==receive_cmd[7])
    {
        switch(receive_cmd[9])
        {
		case MODBUS_COIL_TAB_BIT0:this->m_function = S_SET_CONTROL;break; /*<设置控制主机*/
            case MODBUS_COIL_TAB_BIT1:this->m_function = S_SCAN_CODER;break; /*<轮询编码器的id*/
            case MODBUS_COIL_TAB_BIT2:this->m_function = S_CHECK_STATUS;break;/*<检查各设备的状态 */
            case MODBUS_COIL_TAB_BIT3:this->m_function = S_COLLECT_DATA;break; /*<采集各传感器的数据*/
            case MODBUS_COIL_TAB_BIT4:this->m_function = S_RETURN_REF;break;/*<系统返回到参考点*/
            case MODBUS_COIL_TAB_BIT5:this->m_function = S_STOP;break;
            case MODBUS_COIL_TAB_BIT6:this->m_function = S_SERVER_EXIT;break;
            default:this->m_function=NDFUN;
        }
    }
    /*Register*/
    else if(MODBUS_WRITE_SINGLE_REGISTER==receive_cmd[7])
    {
        switch(receive_cmd[9])
        {
            case MODBUS_HOLD_TAB_REGISTER01:this->m_function = S_SET_ID;break;/*<设置控制器的id*/
            case MODBUS_HOLD_TAB_REGISTER02:this->m_function = S_CUR_REF;break;/*<设备当前位置为系统的参考点*/
            case MODBUS_HOLD_TAB_REGISTER03:this->m_function = S_SWITCH_DEVICE;break;
            case MODBUS_HOLD_TAB_REGISTER30:this->m_function = S_OS;break; /*<系统的操作系统号*/
            case MODBUS_HOLD_TAB_REGISTER31:this->m_function = S_VERSION;break;/*<系统的版本号*/
            case MODBUS_HOLD_TAB_REGISTER32:this->m_function = S_PRODUCTION_TIME;break;
            case MODBUS_HOLD_TAB_REGISTER35:this->m_function = S_MODEL;break;/*<系统的型号*/
            case MODBUS_HOLD_TAB_REGISTER39:this->m_function = S_SN;break;/*<系统的序列号*/
            default:this->m_function=NDFUN;
        }
    }
    /*Coils*/
    else if(MODBUS_WRITE_MULTIPLE_COILS==receive_cmd[7])
    {
        switch(receive_cmd[9])
        {
            case MODBUS_COIL_TAB_BIT0:this->m_function = S_SET_CONTROL;break;
            case MODBUS_COIL_TAB_BIT1:this->m_function = S_SCAN_CODER;break;   /*<轮询编码器的id*/
            case MODBUS_COIL_TAB_BIT2:this->m_function = S_CHECK_STATUS;break; /*<检查各设备的状态 */
            case MODBUS_COIL_TAB_BIT3:this->m_function = S_COLLECT_DATA;break; /*<采集各传感器的数据*/
            case MODBUS_COIL_TAB_BIT4:this->m_function = S_RETURN_REF;break;         /*<系统返回到参考点*/
            case MODBUS_COIL_TAB_BIT5:this->m_function = S_STOP;break;
            case MODBUS_COIL_TAB_BIT6:this->m_function = S_SERVER_EXIT;break;
            default:this->m_function=NDFUN;
        }
    }
    /*Registers*/
    else if(MODBUS_WRITE_MULTIPLE_REGISTERS == receive_cmd[7])
    {
        switch(receive_cmd[9])
        {
            case MODBUS_HOLD_TAB_REGISTER01:this->m_function = S_SET_ID;break;/*<设置控制器的id*/
            case MODBUS_HOLD_TAB_REGISTER02:this->m_function = S_CUR_REF;break;/*<设备当前位置为系统的参考点*/
            case MODBUS_HOLD_TAB_REGISTER03:this->m_function = S_SWITCH_DEVICE;break;
            case MODBUS_HOLD_TAB_REGISTER30:this->m_function = S_OS;break; /*<系统的操作系统号*/
            case MODBUS_HOLD_TAB_REGISTER31:this->m_function = S_VERSION;break;/*<系统的版本号*/
            case MODBUS_HOLD_TAB_REGISTER32:this->m_function = S_PRODUCTION_TIME;break;
            case MODBUS_HOLD_TAB_REGISTER35:this->m_function = S_MODEL;break;/*<系统的型号*/
            case MODBUS_HOLD_TAB_REGISTER39:this->m_function = S_SN;break;/*<系统的序列号*/
            default:this->m_function=NDFUN;
        }
    }
    return this->m_function;
	//std::cout<<"CParse::ParseSysFunction"<<m_function<<std::endl;
}



/**
* @brief  私有ParseCoderFunction函数主要解析命令中有关编码器的功能码
* @param  参数为从上位机接收到的命令
* @return 解析完成，返回功能码
* @note   根据低8位地址，解析出功能码
*/
FunctionType CParse::ParseCoderFunction(const uint8_t *receive_cmd)
{
    assert(NULL!=receive_cmd);
    /*Coil*/
    if(MODBUS_WRITE_SINGLE_COIL==receive_cmd[7])//modbus_write_bit
    {
        switch(receive_cmd[9])
        {
            case MODBUS_COIL_TAB_BIT0:this->m_function = C_COLLECT;break;
            case MODBUS_COIL_TAB_BIT1:this->m_function = C_SET_CUR_ORIGIN;break;
            case MODBUS_COIL_TAB_BIT2:this->m_function = C_SCAN_ID;break;
            default:this->m_function=NDFUN;
        }
    }
    /*Register*/
    else if(MODBUS_WRITE_SINGLE_REGISTER==receive_cmd[7])//modbus_write_register
    {
        switch(receive_cmd[9])
        {
            case MODBUS_HOLD_TAB_REGISTER00:this->m_function = C_SET_ID;break;
            case MODBUS_HOLD_TAB_REGISTER03:this->m_function = C_SET_TYPE;break;
            case MODBUS_HOLD_TAB_REGISTER04:this->m_function = C_SET_MODEL;break;
            default:this->m_function=NDFUN;
        }
    }
    /*Coils*/
    else if(MODBUS_WRITE_MULTIPLE_COILS==receive_cmd[7])//modbus_write_bits
    {
        switch(receive_cmd[9])
        {
            case MODBUS_COIL_TAB_BIT0:this->m_function = C_COLLECT;break;
            case MODBUS_COIL_TAB_BIT1:this->m_function = C_SET_CUR_ORIGIN;break;
            case MODBUS_COIL_TAB_BIT2:this->m_function = C_SCAN_ID;break;
            default:this->m_function=NDFUN;
        }
    }
    /*Hold Registers*/
    else if(MODBUS_WRITE_MULTIPLE_REGISTERS==receive_cmd[7])//modbus_write_registers
    {
        switch(receive_cmd[9])
        {
            case MODBUS_HOLD_TAB_REGISTER00:this->m_function = C_SET_ID;break;
            case MODBUS_HOLD_TAB_REGISTER01:this->m_function = C_SET_BAUD;break;
            case MODBUS_HOLD_TAB_REGISTER03:this->m_function = C_SET_TYPE;break;
            case MODBUS_HOLD_TAB_REGISTER04:this->m_function = C_SET_MODEL;break;
            case MODBUS_HOLD_TAB_REGISTER05:this->m_function = C_SET_GEAR;break;
            default:this->m_function=NDFUN;
        }
    }
    return this->m_function;
}

/**
* @brief  私有ParseMotorFunction函数主要解析命令中有关电机的功能码
* @param  参数为从上位机接收到的命令
* @return 解析完成，返回功能码
* @note   根据低地址，解析出功能码
*/
FunctionType CParse::ParseMotorFunction(const uint8_t *receive_cmd)
{
    assert(NULL!=receive_cmd);

    uint8_t modbus_funcode= receive_cmd[7];
    uint8_t dlp_funcode=receive_cmd[9];

    if(MODBUS_WRITE_SINGLE_COIL==modbus_funcode)
    {
        switch(dlp_funcode)
        {
            case MODBUS_COIL_TAB_BIT0:this->m_function = M_DIR;break;
            case MODBUS_COIL_TAB_BIT1:this->m_function = M_RETURN_ORIGIN;break;
            case MODBUS_COIL_TAB_BIT2:this->m_function = M_ESTOP;break;
            case MODBUS_COIL_TAB_BIT3:this->m_function = M_SET_CUR_ORIGIN;break;
            default:this->m_function=NDFUN;
        }

    }
    else if(MODBUS_WRITE_SINGLE_REGISTER==modbus_funcode)
    {
        switch(dlp_funcode)
        {
            case MODBUS_HOLD_TAB_REGISTER00:this->m_function = M_SET_MAXSPEED;break;
            case MODBUS_HOLD_TAB_REGISTER01:this->m_function = M_SET_MINSPEED;break;
            case MODBUS_HOLD_TAB_REGISTER02:this->m_function = M_SET_ATIME;break;
            case MODBUS_HOLD_TAB_REGISTER03:this->m_function = M_SET_FACTOR;break;
            case MODBUS_HOLD_TAB_REGISTER06:this->m_function = M_SET_CURVE;break;
            case MODBUS_HOLD_TAB_REGISTER07:this->m_function = M_SET_ROTATION;break;
            case MODBUS_HOLD_TAB_REGISTER14:this->m_function = M_RUNNING_DIRECTION;break;
            default:this->m_function=NDFUN;
        }
    }
    else if(MODBUS_WRITE_MULTIPLE_COILS==modbus_funcode)
    {
        switch(dlp_funcode)
        {
            case MODBUS_COIL_TAB_BIT0:this->m_function = M_DIR;break;
            case MODBUS_COIL_TAB_BIT1:this->m_function = M_RETURN_ORIGIN;break;
            case MODBUS_COIL_TAB_BIT2:this->m_function = M_ESTOP;break;
            case MODBUS_COIL_TAB_BIT3:this->m_function = M_SET_CUR_ORIGIN;break;
            default:this->m_function=NDFUN;
        }
    }
    else if(MODBUS_WRITE_MULTIPLE_REGISTERS==modbus_funcode)
    {
        switch(dlp_funcode)
        {
            case MODBUS_HOLD_TAB_REGISTER00:this->m_function = M_SET_MAXSPEED;break;
            case MODBUS_HOLD_TAB_REGISTER01:this->m_function = M_SET_MINSPEED;break;
            case MODBUS_HOLD_TAB_REGISTER02:this->m_function = M_SET_ATIME;break;
            case MODBUS_HOLD_TAB_REGISTER03:this->m_function = M_SET_FACTOR;break;
            case MODBUS_HOLD_TAB_REGISTER04:this->m_function = M_SET_GEAR;break;
            case MODBUS_HOLD_TAB_REGISTER06:this->m_function = M_SET_CURVE;break;
            case MODBUS_HOLD_TAB_REGISTER07:this->m_function = M_SET_ROTATION;break;
            case MODBUS_HOLD_TAB_REGISTER10:this->m_function = M_RUNNING_TIME;break;
            case MODBUS_HOLD_TAB_REGISTER12:this->m_function = M_RUNNING_ANGLE;break;
            case MODBUS_HOLD_TAB_REGISTER14:this->m_function = M_RUNNING_DIRECTION;break;
			case MODBUS_HOLD_TAB_REGISTER0A:this->m_function = M_SET_PERIOD;break;
			case MODBUS_HOLD_TAB_REGISTER0C:this->m_function = M_SET_DUTY;break;
			case MODBUS_HOLD_TAB_REGISTER0E:this->m_function = M_SET_POLARIT;break;
			case MODBUS_HOLD_TAB_REGISTER0F:this->m_function = M_SET_RUN;break;
            default:this->m_function=NDFUN;
        }
    }
#ifdef DLP_DEBUG
    //printf("CParse::ParseMotorFunction:cmd[7]:%x,cmd[9]%x,func:%x\n",modbus_funcode,dlp_funcode,m_function);
#endif
    return this->m_function;
}


