#include "cccd.h"
#include "../../utils/cdebug.h"

CCCD::CCCD(){}

CCCD::~CCCD(){}

/**
* @brief  Ced2Cs������������ʹ�õ��豸÷������ת���������е��ַ���
* @param  ����ʹ�õ��豸÷������
* @note   Ced2Cs>>Class enum device (type) to Config string
* @return ת���������ࣨ�����ļ����ж�Ӧ�����ַ���
*/
std::string CCCD::Ced2Cs(const DeviceType &device)
{
    assert(NDDEV!=device);

    std::string ret_str=" ";
    switch(device)
    {
        case SYSTEM:      ret_str="sys"  ;break;      /*<����ϵͳ */
        case LENS:        ret_str="lens";break;          /*<��ͷ*/
        case PANCODER:    ret_str="pansensor";break;   /*<ƽҡ������*/
        case TILTCODER:   ret_str="tiltsensor";break;   /*<����������*/
		case ZOOMCODER:   ret_str="zoomsensor";break;      /*<�佹������*/
        case FOCUSCODER:  ret_str="focussensor";break;    /*<�۽�������*/

        case PANSWINGCODER:      ret_str="";break;  /*<������*/
        case TILTSWINGCODER:      ret_str="";break;  /*<������*/
        case PANMOTOR:    ret_str="panmotor";break;  /*<ƽҡ���*/
        case TILTMOTOR:   ret_str="tiltmotor";break;  /*<ƽҡ���*/
        case ZOOMMOTOR:   ret_str="zoommotor";break;  /*<�佹���*/
        case FOCUSMOTOR:  ret_str="focusmotor";break;   /*<�۽����*/
        case NDDEV:       ret_str="";break;
        default:dlp_log(DLP_LOG_ERR,"CCD::Cef2Cs....");
    }
    return ret_str;
}

/**
* @brief  Cef2Cs����������ʹ�õĹ���÷������ת���������ļ��е��ַ���
* @param  ����ʹ�õĹ���÷������
* @return ת���������Ӧ�����ļ��е��ַ������ʶ
* @note   Cef2Cs>>Class enum function (type) to Config string
* @see    ����ù��������һ��32λ�����ݣ��������ļ��л����������ʶ��Ĭ�Ϸ��ص�λ��ʶ��xxxl
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
            /*����ϵͳ��������*/
            case 0x001:  ret = "id";break; /*<���ÿ�������id*/
            case 0x030:  ret = "os";break; /*<ϵͳ�Ĳ���ϵͳ��*/
            case 0x031:  ret = "ver";break; /*<ϵͳ�İ汾��*/
            case 0x032:  ret = "ft0";break; /*<ϵͳ�ĳ���ʱ�� */
            case 0x035:  ret = "model0";break;/*<ϵͳ���ͺ�*/
            case 0x039:  ret = "SN0";break; /*<ϵͳ�����к�*/
            /*����ƽҡ��������������*/
            case 0x200:  ret = "id";break; /*<���ñ�������id*/
            case 0x201:  ret = "baud0";break; /*<���ñ������Ĳ�����*/
            case 0x203:  ret = "type";break; /*<���ñ�����������*/
            case 0x204:  ret = "mode";break; /*<���ñ��������ͺ�*/
            case 0x205:  ret = "gear0";break; /*<���ñ������ĳ�����*/
			case 0x207:  ret = "bits";break; /*<������λ��*/
			/*���帩����������������*/
			case 0x300:  ret = "id";break; /*<���ñ�������id*/
			case 0x301:  ret = "baud0";break; /*<���ñ������Ĳ�����*/
			case 0x303:  ret = "type";break; /*<���ñ�����������*/
			case 0x304:  ret = "mode";break; /*<���ñ��������ͺ�*/
			case 0x305:  ret = "gear0";break; /*<���ñ������ĳ�����*/
			case 0x307:  ret = "bits";break; /*<������λ��*/
			/*����佹��������������*/
			case 0x400:  ret = "id";break; /*<���ñ�������id*/
			case 0x401:  ret = "baud0";break; /*<���ñ������Ĳ�����*/
			case 0x403:  ret = "type";break; /*<���ñ�����������*/
			case 0x404:  ret = "mode";break; /*<���ñ��������ͺ�*/
			case 0x405:  ret = "gear0";break; /*<���ñ������ĳ�����*/
			case 0x407:  ret = "bits";break; /*<������λ��*/
			/*����ۼ���������������*/
			case 0x500:  ret = "id";break; /*<���ñ�������id*/
			case 0x501:  ret = "baud0";break; /*<���ñ������Ĳ�����*/
			case 0x503:  ret = "type";break; /*<���ñ�����������*/
			case 0x504:  ret = "mode";break; /*<���ñ��������ͺ�*/
			case 0x505:  ret = "gear0";break; /*<���ñ������ĳ�����*/
			case 0x507:  ret = "bits";break; /*<������λ��*/
			/*����ƽҡ�����������*/
            case 0x800:  ret = "max";break; /*<�����������ٶȣ��������ٶ�*/
            case 0x801:  ret = "min";break; /*<�����С�����ٶȣ��������ٶ�*/
            case 0x802:  ret = "acc";break; /*<�����������ʱ�� */
            case 0x803:  ret = "subdivision";break; /*<�������ϸ����*/
            case 0x804:  ret = "gear0";break; /*<���������*/
            case 0x806:  ret = "algorithm";break; /*<��������㷨*/

			/*���帩�������������*/
			case 0x900:  ret = "max";break; /*<�����������ٶȣ��������ٶ�*/
			case 0x901:  ret = "min";break; /*<�����С�����ٶȣ��������ٶ�*/
			case 0x902:  ret = "acc";break; /*<�����������ʱ�� */
			case 0x903:  ret = "subdivision";break; /*<�������ϸ����*/
			case 0x904:  ret = "gear0";break; /*<���������*/
			case 0x906:  ret = "algorithm";break; /*<��������㷨*/
			/*����佹�����������*/
			case 0xA00:  ret = "max";break; /*<�����������ٶȣ��������ٶ�*/
			case 0xA01:  ret = "min";break; /*<�����С�����ٶȣ��������ٶ�*/
            case 0xA04:  ret = "gear0";break; /*<���������*/
			case 0xA0A:  ret = "period0";break; /*<�����������ٶȣ��������ٶ�*/
			case 0xA0C:  ret = "duty0";break; /*<�����С�����ٶȣ��������ٶ�*/
			case 0xA0E:  ret = "polarity";break; /*<�����������ʱ�� */
			case 0xA0F:  ret = "run";break; /*<�������ϸ����*/


			/*����۽������������*/
			case 0xB00:  ret = "max";break; /*<�����������ٶȣ��������ٶ�*/
			case 0xB01:  ret = "min";break; /*<�����С�����ٶȣ��������ٶ�*/
            case 0xB04:  ret = "gear0";break; /*<���������*/
			case 0xB0A:  ret = "period0";break; /*<�����������ٶȣ��������ٶ�*/
			case 0xB0C:  ret = "duty0";break; /*<�����С�����ٶȣ��������ٶ�*/
			case 0xB0E:  ret = "polarity";break; /*<�����������ʱ�� */
			case 0xB0F:  ret = "run";break; /*<�������ϸ����*/

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
* @brief  Ced2Dnh����ʹ����ʹ�õ��豸÷������ת��ӳ���ļ��еĸߵ�ַ����modbus tcpͨ��֡�ĵڣ�λ
* @param  ����ʹ�õ��豸÷�����͵ı���
* @note Ced2Dnh>>Class enum device (type) to  Device int high (address)
* @return �����-1,�����û�и��豸,���򷵻��豸���Ӧ��ӳ���ļ��еĸߵ�ַ

*/
/**/
int CCCD::Ced2Dnh(const DeviceType &device)
{
    assert(NDDEV!=device);

    uint8_t ret=-1;
    switch(device)
    {
        case SYSTEM:        ret = 0;break;   /*<����ϵͳ */
        case LENS:          ret = 1;break;   /*<��ͷ*/
        case PANCODER:      ret = 2;break;   /*<�佹������*/
        case TILTCODER:     ret = 3;break;   /*<�۽�������*/
        case ZOOMCODER:     ret = 4;break;   /*<ƽҡ������*/
        case FOCUSCODER:    ret = 5;break;   /*<����������*/
        case PANSWINGCODER: ret = 6;break;   /*<ƽҡҡ�۱�����*/
        case TILTSWINGCODER:ret = 7;break;   /*<����ҡ�۱�����*/
        case PANMOTOR:      ret = 8;break;   /*<ƽҡҡ�۵��*/
        case TILTMOTOR:     ret = 9;break;   /*<ƽҡҡ�۵��*/
        case ZOOMMOTOR:     ret = 10;break;  /*<�佹���*/
        case FOCUSMOTOR:    ret = 11;break;  /*<�۽����*/
        case PANSWINGMOTOR: ret = 12;break;  /*<ƽҡҡ�۵��*/
        case TILTSWINGMOTOR:ret = 13;break;  /*<����ҡ�۵��*/
        case NDDEV:         ret = -1;break;
        default:dlp_log(DLP_LOG_ERR,"CCD::Ced2Dnh....");
    }

    return ret;
}

/**
* @brief  Cef2Dnl����ʹ����ʹ�õĹ���ö������Χ��Modbusӳ���ļ��еĵ͵�ַ����modbus��tcpͨ��֡�ĵڣ�λ
* @param  ����ʹ�õĹ���ö�����ͱ���
* @note   Cef2Dnl>>Class enum function (type) to Device int low (address)
* @return �����-1,�����û�и��豸,���򷵻ع������Ӧ��ӳ���ļ��еĵ͵�ַ
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
            case 0x001:  ret = 0x01;break; /*<ϵͳ��������id*/
            case 0x030:  ret = 0x30;break; /*<ϵͳ�Ĳ���ϵͳ��*/
            case 0x031:  ret = 0x31;break; /*<ϵͳ�İ汾��*/
            case 0x032:  ret = 0x32;break; /*<ϵͳ�ĳ���ʱ�� */
            case 0x035:  ret = 0x35;break; /*<ϵͳ���ͺ�*/
            case 0x039:  ret = 0x39;break; /*<ϵͳ�����к�*/

            case 0x200:  ret = 0x00;break; /*<ƽҡ��������id*/
            case 0x201:  ret = 0x01;break; /*<ƽҡ�������Ĳ�����*/
            case 0x203:  ret = 0x03;break; /*<ƽҡ������������*/
            case 0x204:  ret = 0x04;break; /*<ƽҡ���������ͺ�*/
            case 0x205:  ret = 0x05;break; /*<ƽҡ�������ĳ�����*/
            case 0x207:  ret = 0x07;break; /*<ƽҡ��������λ��*/

            case 0x300:  ret = 0x00;break; /*<������������id*/
            case 0x301:  ret = 0x01;break; /*<�����������Ĳ�����*/
            case 0x303:  ret = 0x03;break; /*<����������������*/
            case 0x304:  ret = 0x04;break; /*<�������������ͺ�*/
            case 0x305:  ret = 0x05;break; /*<�����������ĳ�����*/
            case 0x307:  ret = 0x07;break; /*<������������λ��*/

            case 0x400:  ret = 0x00;break; /*<�佹��������id*/
            case 0x401:  ret = 0x01;break; /*<�佹�������Ĳ�����*/
            case 0x403:  ret = 0x03;break; /*<�佹������������*/
            case 0x404:  ret = 0x04;break; /*<�佹���������ͺ�*/
            case 0x405:  ret = 0x05;break; /*<�佹�������ĳ�����*/
            case 0x407:  ret = 0x07;break; /*<�佹��������λ��*/

            case 0x500:  ret = 0x00;break; /*<�۽���������id*/
            case 0x501:  ret = 0x01;break; /*<�۽��������Ĳ�����*/
            case 0x503:  ret = 0x03;break; /*<�۽�������������*/
            case 0x504:  ret = 0x04;break; /*<�۽����������ͺ�*/
            case 0x505:  ret = 0x05;break; /*<�۽��������ĳ�����*/
            case 0x507:  ret = 0x07;break; /*<�۽���������λ��*/


            case 0x800:  ret = 0x00;break; /*<ƽҡ�����������ٶȣ��������ٶ�*/
            case 0x801:  ret = 0x01;break; /*<ƽҡ�����С�����ٶȣ��������ٶ�*/
            case 0x802:  ret = 0x02;break; /*<ƽҡ�����������ʱ�� */
            case 0x803:  ret = 0x03;break; /*<ƽҡ�������ϸ����*/
            case 0x804:  ret = 0x04;break; /*<ƽҡ���������*/
            case 0x806:  ret = 0x06;break; /*<ƽҡ��������㷨*/

            case 0x900:  ret = 0x00;break; /*<���������������ٶȣ��������ٶ�*/
            case 0x901:  ret = 0x01;break; /*<���������С�����ٶȣ��������ٶ�*/
            case 0x902:  ret = 0x02;break; /*<���������������ʱ�� */
            case 0x903:  ret = 0x03;break; /*<�����������ϸ����*/
            case 0x904:  ret = 0x04;break; /*<�������������*/
            case 0x906:  ret = 0x06;break; /*<������������㷨*/

            case 0xA00:  ret = 0x00;break; /*<�佹�����������ٶ�*/
            case 0xA01:  ret = 0x01;break; /*<�佹�����С�����ٶ�*/
            case 0xA04:  ret = 0x04;break; /*<�佹���������*/
            case 0xA0A:  ret = 0x0A;break; /*<�佹��������*/
            case 0xA0C:  ret = 0x0C;break; /*<�佹������ձ�*/
            case 0xA0E:  ret = 0x0E;break; /*<�佹��������*/
            case 0xA0F:  ret = 0x0F;break; /*<�佹����״̬*/

            case 0xB00:  ret = 0x00;break; /*<�۽������������ٶ�*/
            case 0xB01:  ret = 0x01;break; /*<�۽������С�����ٶ�*/
            case 0xB04:  ret = 0x04;break; /*<�۽����������*/
            case 0xB0A:  ret = 0x0A;break; /*<�۽���������*/
            case 0xB0C:  ret = 0x0C;break; /*<�۽�������ձ�*/
            case 0xB0E:  ret = 0x0E;break; /*<�۽���������*/
            case 0xB0F:  ret = 0x0F;break; /*<�۽�����״̬*/

        }
    }
    else if(MODBUS_COILS)
    {
          switch(task_func)
          {
            case 0x300:  ret = 0x10;break; /*<������з���*/
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
