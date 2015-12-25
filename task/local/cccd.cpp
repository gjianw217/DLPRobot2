#include "cccd.h"
#include "../../utils/cdebug.h"

CCCD::CCCD(){}

CCCD::~CCCD(){}

/**
* @brief  Ced2Cs函数，将类中使用的设备梅举类型转成配置类中的字符串
* @param  类中使用的设备梅举类型
* @note   Ced2Cs>>Class enum device (type) to Config string
* @return 转换后，配置类（配置文件）中对应结点的字符串
*/
std::string CCCD::Ced2Cs(const DeviceType &device)
{
    assert(NDDEV!=device);

    std::string ret_str=" ";
    switch(device)
    {
        case SYSTEM:      ret_str="sys"  ;break;      /*<控制系统 */
        case LENS:        ret_str="lens";break;          /*<镜头*/
        case PANCODER:    ret_str="pansensor";break;   /*<平摇编码器*/
        case TILTCODER:   ret_str="tiltsensor";break;   /*<俯仰编码器*/
		case ZOOMCODER:   ret_str="zoomsensor";break;      /*<变焦编码器*/
        case FOCUSCODER:  ret_str="focussensor";break;    /*<聚焦编码器*/

        case PANSWINGCODER:      ret_str="";break;  /*<编码器*/
        case TILTSWINGCODER:      ret_str="";break;  /*<编码器*/
        case PANMOTOR:    ret_str="panmotor";break;  /*<平摇电机*/
        case TILTMOTOR:   ret_str="tiltmotor";break;  /*<平摇电机*/
        case ZOOMMOTOR:   ret_str="zoommotor";break;  /*<变焦电机*/
        case FOCUSMOTOR:  ret_str="focusmotor";break;   /*<聚焦电机*/
        case NDDEV:       ret_str="";break;
        default:dlp_log(DLP_LOG_ERR,"CCD::Cef2Cs....");
    }
    return ret_str;
}

/**
* @brief  Cef2Cs函数将类中使用的功能梅举类型转换成配置文件中的字符串
* @param  类中使用的功能梅举类型
* @return 转换后功能码对应配置文件中的字符串或标识
* @note   Cef2Cs>>Class enum function (type) to Config string
* @see    如果该功能码代表一个32位的数据，在配置文件中会存在两个标识，默认返回低位标识，xxxl
*/
std::string CCCD::Cef2Cs(const DeviceType &dev,const FunctionType &func,const RegisterType &reg)
{
    assert(NDDEV!=dev);
    assert(NDFUN!=func);
    assert(NOREG!=reg);

    std::string ret=" ";
	uint16_t dev_func=dev|func;
    if(MODBUS_COILS==reg)
    {
        switch(dev_func)
        {
            case 0x300:  ret ="direction";break;

        }
    }
    else if(MODBUS_INPUT_REGISTERS==reg)
    {
        switch(dev_func)
        {

            case 0x204:  ret ="origin0";break;
            case 0x300:  ret ="origin0";break;

        }
    }
    else if(MODBUS_HOLDING_REGISTERS==reg)
    {
        switch(dev_func)
        {
            /*定义系统命令类型*/
            case 0x001:  ret = "id";break; /*<设置控制器的id*/
            case 0x030:  ret = "os";break; /*<系统的操作系统号*/
            case 0x031:  ret = "ver";break; /*<系统的版本号*/
            case 0x032:  ret = "ft0";break; /*<系统的出厂时间 */
            case 0x035:  ret = "model0";break;/*<系统的型号*/
            case 0x039:  ret = "SN0";break; /*<系统的序列号*/
            /*定义平摇编码器命令类型*/
            case 0x200:  ret = "id";break; /*<设置编码器的id*/
            case 0x201:  ret = "baud0";break; /*<设置编码器的波特率*/
            case 0x203:  ret = "type";break; /*<设置编码器的类型*/
            case 0x204:  ret = "mode";break; /*<设置编码器的型号*/
            case 0x205:  ret = "gear0";break; /*<设置编码器的齿数比*/
			case 0x207:  ret = "bits";break; /*<编码器位数*/
			/*定义俯仰编码器命令类型*/
			case 0x300:  ret = "id";break; /*<设置编码器的id*/
			case 0x301:  ret = "baud0";break; /*<设置编码器的波特率*/
			case 0x303:  ret = "type";break; /*<设置编码器的类型*/
			case 0x304:  ret = "mode";break; /*<设置编码器的型号*/
			case 0x305:  ret = "gear0";break; /*<设置编码器的齿数比*/
			case 0x307:  ret = "bits";break; /*<编码器位数*/
			/*定义变焦编码器命令类型*/
			case 0x400:  ret = "id";break; /*<设置编码器的id*/
			case 0x401:  ret = "baud0";break; /*<设置编码器的波特率*/
			case 0x403:  ret = "type";break; /*<设置编码器的类型*/
			case 0x404:  ret = "mode";break; /*<设置编码器的型号*/
			case 0x405:  ret = "gear0";break; /*<设置编码器的齿数比*/
			case 0x407:  ret = "bits";break; /*<编码器位数*/
			/*定义聚集编码器命令类型*/
			case 0x500:  ret = "id";break; /*<设置编码器的id*/
			case 0x501:  ret = "baud0";break; /*<设置编码器的波特率*/
			case 0x503:  ret = "type";break; /*<设置编码器的类型*/
			case 0x504:  ret = "mode";break; /*<设置编码器的型号*/
			case 0x505:  ret = "gear0";break; /*<设置编码器的齿数比*/
			case 0x507:  ret = "bits";break; /*<编码器位数*/
			/*定义平摇电机命令类型*/
            case 0x800:  ret = "max";break; /*<电机最大运行速度，即正常速度*/
            case 0x801:  ret = "min";break; /*<电机最小运行速度，即启动速度*/
            case 0x802:  ret = "acc";break; /*<电机启动加速时间 */
            case 0x803:  ret = "subdivision";break; /*<电机驱动细分数*/
            case 0x804:  ret = "gear0";break; /*<电机齿数比*/
            case 0x806:  ret = "algorithm";break; /*<电机运行算法*/

			/*定义俯仰电机命令类型*/
			case 0x900:  ret = "max";break; /*<电机最大运行速度，即正常速度*/
			case 0x901:  ret = "min";break; /*<电机最小运行速度，即启动速度*/
			case 0x902:  ret = "acc";break; /*<电机启动加速时间 */
			case 0x903:  ret = "subdivision";break; /*<电机驱动细分数*/
			case 0x904:  ret = "gear0";break; /*<电机齿数比*/
			case 0x906:  ret = "algorithm";break; /*<电机运行算法*/
			/*定义变焦电机命令类型*/
			case 0xA00:  ret = "max";break; /*<电机最大运行速度，即正常速度*/
			case 0xA01:  ret = "min";break; /*<电机最小运行速度，即启动速度*/
            case 0xA04:  ret = "gear0";break; /*<电机齿数比*/
			case 0xA0A:  ret = "period0";break; /*<电机最大运行速度，即正常速度*/
			case 0xA0C:  ret = "duty0";break; /*<电机最小运行速度，即启动速度*/
			case 0xA0E:  ret = "polarity";break; /*<电机启动加速时间 */
			case 0xA0F:  ret = "run";break; /*<电机驱动细分数*/


			/*定义聚焦电机命令类型*/
			case 0xB00:  ret = "max";break; /*<电机最大运行速度，即正常速度*/
			case 0xB01:  ret = "min";break; /*<电机最小运行速度，即启动速度*/
            case 0xB04:  ret = "gear0";break; /*<电机齿数比*/
			case 0xB0A:  ret = "period0";break; /*<电机最大运行速度，即正常速度*/
			case 0xB0C:  ret = "duty0";break; /*<电机最小运行速度，即启动速度*/
			case 0xB0E:  ret = "polarity";break; /*<电机启动加速时间 */
			case 0xB0F:  ret = "run";break; /*<电机驱动细分数*/

        }
    }
    else
    {
        dlp_log(DLP_LOG_ERR,"CCD::Cef2Cs....");
    }

    //printf("CCD::Cef2Cs:task_func>%x,task>%x,func>%x,ret>%s\n",task_func,task,func,ret.c_str());
    return ret;
}
/**
* @brief  Ced2Dnh函数使类中使用的设备梅举类型转成映射文件中的高地址，即modbus tcp通信帧的第８位
* @param  类中使用的设备梅举类型的变量
* @note Ced2Dnh>>Class enum device (type) to  Device int high (address)
* @return 如果是-1,则表明没有该设备,否则返回设备码对应的映射文件中的高地址

*/
/**/
int CCCD::Ced2Dnh(const DeviceType &device)
{
    assert(NDDEV!=device);

    uint8_t ret=-1;
    switch(device)
    {
        case SYSTEM:        ret = 0;break;   /*<控制系统 */
        case LENS:          ret = 1;break;   /*<镜头*/
        case PANCODER:      ret = 2;break;   /*<变焦编码器*/
        case TILTCODER:     ret = 3;break;   /*<聚焦编码器*/
        case ZOOMCODER:     ret = 4;break;   /*<平摇编码器*/
        case FOCUSCODER:    ret = 5;break;   /*<俯仰编码器*/
        case PANSWINGCODER: ret = 6;break;   /*<平摇摇臂编码器*/
        case TILTSWINGCODER:ret = 7;break;   /*<俯仰摇臂编码器*/
        case PANMOTOR:      ret = 8;break;   /*<平摇摇臂电机*/
        case TILTMOTOR:     ret = 9;break;   /*<平摇摇臂电机*/
        case ZOOMMOTOR:     ret = 10;break;  /*<变焦电机*/
        case FOCUSMOTOR:    ret = 11;break;  /*<聚焦电机*/
        case PANSWINGMOTOR: ret = 12;break;  /*<平摇摇臂电机*/
        case TILTSWINGMOTOR:ret = 13;break;  /*<俯仰摇臂电机*/
        case NDDEV:         ret = -1;break;
        default:dlp_log(DLP_LOG_ERR,"CCD::Ced2Dnh....");
    }

    return ret;
}

/**
* @brief  Cef2Dnl函数使类中使用的功能枚举类型围成Modbus映射文件中的低地址，即modbus　tcp通信帧的第９位
* @param  类中使用的功能枚举类型变量
* @note   Cef2Dnl>>Class enum function (type) to Device int low (address)
* @return 如果是-1,则表明没有该设备,否则返回功能码对应的映射文件中的低地址
*/
int CCCD::Cef2Dnl(const DeviceType &dev,const FunctionType &func,const RegisterType &reg)
{
    assert(NDDEV!=dev);
    assert(NDFUN!=func);
    assert(NOREG!=reg);

    int ret= -1;
    TaskType task;
    Device2Task(dev,task);
    int task_func=task|func;

    if(MODBUS_COILS==reg)
    {
        switch(task_func)
        {
            case 0x300:  ret = 0x00;break;

        }
    }
    else if(MODBUS_INPUT_REGISTERS==reg)
    {
        switch(task_func)
        {
            case 0x001:  ret = 0x01;break;
            case 0x006:  ret = 0x06;break;
            case 0x00E:  ret = 0x0E;break;
            case 0x010:  ret = 0x10;break;

            case 0x200:  ret = 0x00;break;
            case 0x204:  ret = 0x04;break;
            case 0x206:  ret = 0x06;break;

            case 0x300:  ret = 0x00;break;

        }
    }
    else if(MODBUS_HOLDING_REGISTERS==reg)
    {
        switch(task_func)
        {
            case 0x001:  ret = 0x01;break; /*<系统控制器的id*/
            case 0x030:  ret = 0x30;break; /*<系统的操作系统号*/
            case 0x031:  ret = 0x31;break; /*<系统的版本号*/
            case 0x032:  ret = 0x32;break; /*<系统的出厂时间 */
            case 0x035:  ret = 0x35;break; /*<系统的型号*/
            case 0x039:  ret = 0x39;break; /*<系统的序列号*/

            case 0x200:  ret = 0x00;break; /*<平摇编码器的id*/
            case 0x201:  ret = 0x01;break; /*<平摇编码器的波特率*/
            case 0x203:  ret = 0x03;break; /*<平摇编码器的类型*/
            case 0x204:  ret = 0x04;break; /*<平摇编码器的型号*/
            case 0x205:  ret = 0x05;break; /*<平摇编码器的齿数比*/
            case 0x207:  ret = 0x07;break; /*<平摇编码器的位数*/

            case 0x300:  ret = 0x00;break; /*<俯仰编码器的id*/
            case 0x301:  ret = 0x01;break; /*<俯仰编码器的波特率*/
            case 0x303:  ret = 0x03;break; /*<俯仰编码器的类型*/
            case 0x304:  ret = 0x04;break; /*<俯仰编码器的型号*/
            case 0x305:  ret = 0x05;break; /*<俯仰编码器的齿数比*/
            case 0x307:  ret = 0x07;break; /*<俯仰编码器的位数*/

            case 0x400:  ret = 0x00;break; /*<变焦编码器的id*/
            case 0x401:  ret = 0x01;break; /*<变焦编码器的波特率*/
            case 0x403:  ret = 0x03;break; /*<变焦编码器的类型*/
            case 0x404:  ret = 0x04;break; /*<变焦编码器的型号*/
            case 0x405:  ret = 0x05;break; /*<变焦编码器的齿数比*/
            case 0x407:  ret = 0x07;break; /*<变焦编码器的位数*/

            case 0x500:  ret = 0x00;break; /*<聚焦编码器的id*/
            case 0x501:  ret = 0x01;break; /*<聚焦编码器的波特率*/
            case 0x503:  ret = 0x03;break; /*<聚焦编码器的类型*/
            case 0x504:  ret = 0x04;break; /*<聚焦编码器的型号*/
            case 0x505:  ret = 0x05;break; /*<聚焦编码器的齿数比*/
            case 0x507:  ret = 0x07;break; /*<聚焦编码器的位数*/


            case 0x800:  ret = 0x00;break; /*<平摇电机最大运行速度，即正常速度*/
            case 0x801:  ret = 0x01;break; /*<平摇电机最小运行速度，即启动速度*/
            case 0x802:  ret = 0x02;break; /*<平摇电机启动加速时间 */
            case 0x803:  ret = 0x03;break; /*<平摇电机驱动细分数*/
            case 0x804:  ret = 0x04;break; /*<平摇电机齿数比*/
            case 0x806:  ret = 0x06;break; /*<平摇电机运行算法*/

            case 0x900:  ret = 0x00;break; /*<俯仰电机最大运行速度，即正常速度*/
            case 0x901:  ret = 0x01;break; /*<俯仰电机最小运行速度，即启动速度*/
            case 0x902:  ret = 0x02;break; /*<俯仰电机启动加速时间 */
            case 0x903:  ret = 0x03;break; /*<俯仰电机驱动细分数*/
            case 0x904:  ret = 0x04;break; /*<俯仰电机齿数比*/
            case 0x906:  ret = 0x06;break; /*<俯仰电机运行算法*/

            case 0xA00:  ret = 0x00;break; /*<变焦电机最大运行速度*/
            case 0xA01:  ret = 0x01;break; /*<变焦电机最小运行速度*/
            case 0xA04:  ret = 0x04;break; /*<变焦电机齿数比*/
            case 0xA0A:  ret = 0x0A;break; /*<变焦驱动周期*/
            case 0xA0C:  ret = 0x0C;break; /*<变焦驱动点空比*/
            case 0xA0E:  ret = 0x0E;break; /*<变焦驱动极性*/
            case 0xA0F:  ret = 0x0F;break; /*<变焦驱动状态*/

            case 0xB00:  ret = 0x00;break; /*<聚焦电机最大运行速度*/
            case 0xB01:  ret = 0x01;break; /*<聚焦电机最小运行速度*/
            case 0xB04:  ret = 0x04;break; /*<聚焦电机齿数比*/
            case 0xB0A:  ret = 0x0A;break; /*<聚焦驱动周期*/
            case 0xB0C:  ret = 0x0C;break; /*<聚焦驱动点空比*/
            case 0xB0E:  ret = 0x0E;break; /*<聚焦驱动极性*/
            case 0xB0F:  ret = 0x0F;break; /*<聚焦驱动状态*/

        }
    }
    else if(MODBUS_COILS)
    {
          switch(task_func)
          {
            case 0x300:  ret = 0x10;break; /*<电机运行方向*/
          }
    }
    else
    {
         dlp_log(DLP_LOG_ERR,"CCD::Cef2Dnl....");
    }

    return ret;
}

void CCCD::Device2Task(const DeviceType &device,TaskType &task)
{
	switch(device)
    {
        case SYSTEM:task=SYS_TASK;break;
     /* case LENS:task=LENS_TASK;break;
          case ZOOMCODER:
        case FOCUSCODER:
        case PANNINGCODER:
        case PITCHCODER:
        case PASWINGCODER:
        case PISWINGCODER:task=CODER_TASK;break;
        case PANNINGMOTOR:
        case PITCHMOTOR:
        case PASWINGMOTOR:
        case PISWINGMOTOR:task=MOTOR_TASK;break;*/
        default:task=NDTASK;
    }

}
