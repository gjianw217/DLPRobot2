/*
* @file   ͷ�ļ�
* @brief  �Զ�����λ������λ��ʹ��Modbusͨ�ţ�ʹ�õ������
* @author GuoJianwei & gjianw217@163.com
*/
#ifndef DLP_COMMON_DLPROBOT_H_
#define DLP_COMMON_DLPROBOT_H_

/*
enum {
	POS_CLOCKWISE=0,     //�������򣬼�˳ʱ�뷽��
	NEG_ANTI_CLOCKWISE=1
};*/

/*�����豸ö������*/
typedef enum{
            SYSTEM           =0x000,    /*<����ϵͳ���豸������ϵͳ�����Ϣ�� */
            LENS             =0x100,    /*<��ͷ*/
            PANCODER         =0x200,    /*<�佹������*/
            TILTCODER        =0x300,    /*<�۽�������*/
            ZOOMCODER        =0x400,      /*<ƽҡ������*/
            FOCUSCODER       =0x500,    /*<����������*/
            PANSWINGCODER    =0x600,    /*<����������*/
            TILTSWINGCODER   =0x700,    /*<����������*/
            PANMOTOR         =0x800,    /*<ƽҡ���*/
            TILTMOTOR        =0x900,    /*<�������*/
            ZOOMMOTOR        =0xA00,    /*<�佹���*/
            FOCUSMOTOR       =0xB00,    /*<�۽����*/
            PANSWINGMOTOR    =0xC00,
            TILTSWINGMOTOR   =0xD00,
            NDDEV=-1
}DeviceType;

typedef enum{
            /*����ϵͳ��������*/
            /*Coils*/
            S_SET_CONTROL           =0x00, /*<ʹ��λ����bbb�п���д��Ȩ��*/
            S_SCAN_CODER            =0x01, /*<ɨ���������id*/
            S_CHECK_STATUS          =0x02, /*<�����豸��״̬ *///��ʱ���豸��״�滻
            S_COLLECT_DATA          =0x03, /*<�ɼ���������������*/
            S_RETURN_REF            =0x04, /*<ϵͳ���زο�ԭ��*/
            S_STOP                  =0x05, /*<ϵͳ����ֹͣ*/
 /*deprecated*/  S_SERVER_EXIT           =0x06, /*<ϵͳ�˳���������*/
            /*Input Register*/
            S_GET_CONTROL_IP        =0x01,
            S_GET_SENSORS_ID        =0x06,
            S_GET_DEVICES_STATUS    =0x0E,
            S_GET_DATAS             =0x10,
            S_GET_MAC               =0x30, /*<��̨������MAC��ַ 20150610*/
            S_GET_SERVER_IP         =0x36,  /*<��̨������IP     20150610*/
            /*Holding Register*/
            S_SET_ID                =0x01, /*<���ÿ�������id*/
            S_CUR_REF               =0x02, /*<ϵͳ���õ�ǰλ��Ϊ�ο�ԭ��*/
            S_SWITCH_DEVICE         =0x03, /*<ϵͳ�л��豸����*/
            S_OS                    =0x30, /*<ϵͳ�Ĳ���ϵͳ��*/
            S_VERSION               =0x31, /*<ϵͳ�İ汾��*/
            S_PRODUCTION_TIME       =0x32, /*<ϵͳ�ĳ���ʱ�� */
            S_MODEL                 =0x35, /*<ϵͳ���ͺ�*/
            S_SN                    =0x39, /*<ϵͳ�����к�*/

            /*Testing*/
            //S_SYN_TIME                   , /*<����λ������ʱ��ͬ��*/
            //S_HEARTBEATS                 ,/*<������*/

            /*�����������������*/
            /*Coils*/
            C_COLLECT               =0x00, /*<�ɼ���������ֵ*/
 /*deprecated*/   C_SET_CUR_ORIGIN        =0x01, /*<���õ�ǰλ��Ϊ�������Ĳο�ԭ��*/
            C_SCAN_ID               =0x02, /*<��ѯ��������id*/
            /*Input Register*/
            C_GET_DATA              =0x00,
            C_GET_ORGIN             =0x04,
/*deprecated */  C_GET_ID                =0x06,
            C_GET_DATABITS          =0x06, /*<20150610*/
            C_GET_PARITYBITS        =0x07, /*<20150610*/
            C_GET_STOPBITS          =0x08,/*<20150610*/
            C_GET_FLOWBITS          =0x09,/*<20150610*/
            /*Holding Register*/
            C_SET_ID                =0x00, /*<���ñ�������id*/
            C_SET_BAUD              =0x01, /*<���ñ������Ĳ�����*/
            C_SET_TYPE              =0x03, /*<���ñ�����������*/
            C_SET_MODEL             =0x04, /*<���ñ��������ͺ�*/
            C_SET_GEAR              =0x05, /*<���ñ������ĳ�����*/
            C_SET_BITS              =0x07,  /*<*������λ��*/
            /*Testing*/
            //C_SET_ORIGIN                  ,  /*<���ñ������Ĳο���*/

            /*��������������*/
            /*Coils*/
 /*deprecated*/  M_DIR                   =0x00, /*���õ��ת������ */
            M_RETURN_ORIGIN         =0x01, /*<���ص�ǰ�ο�λ*/
            M_ESTOP                 =0x02, /*<�����ƶ�*/
 /*deprecated*/  M_SET_CUR_ORIGIN        =0x03, /*<���õ�ǰλ��Ϊ�ο�λ*/
            /*Input Register*/
            M_GET_ORIGIN            =0x00,
 /*deprecated*/M_GET_REF_OFFSET        =0x05, /*<���������ת���ĽǶ�*/
             /*Holding Register*/
            M_SET_MAXSPEED          =0x00, /*<�����������ٶȣ��������ٶ�*/
            M_SET_MINSPEED          =0x01, /*<�����С�����ٶȣ��������ٶ�*/
            M_SET_ATIME             =0x02, /*<�����������ʱ�� */
            M_SET_FACTOR            =0x03, /*<�������ϸ����*/
            M_SET_GEAR              =0x04, /*<���������*/
/*deprecated*/M_SET_ALGORITHM            , /*<��������㷨       20150609*/
			M_SET_CURVE             =0x06,  /*<��������㷨 ���� 20150609*/
			M_SET_ROTATION          = 0x07, /*<��������㷨 ��ת 20150609*/
			M_SET_PERIOD            =0x0A, /*<PWM��������  */
			M_SET_DUTY              =0x0C, /*<PWM����ռ�ձ�*/
			M_SET_POLARIT           =0x0E, /*<PWM���м���*/
			M_SET_RUN               =0x0F, /*<PWM����״̬*/

            M_RUNNING_TIME          =0x10, /*<�������ʱ��*/
            M_RUNNING_ANGLE         =0x12, /*<���������̨ƫ�ƽǶ�*/
            M_RUNNING_DIRECTION     =0x14, /*<���������̨���з���*/
            /*Testing*/
            //M_SET_ORIGIN                 ,     /*<���õ���ο�λ*/

            /*���徵ͷ��������*/
            /*Coils*/
            L_CONNECTION            =0x00,/*<��ͷ��������*/
            L_RESET                 =0x01,/*<��ͷ����*/
            L_GET_IRIS              =0x02,/*<��ȡ��Ȧλ��*/
            L_GET_ZOOM              =0x03,/*<��ȡ����λ��*/
            L_GET_FOCUS             =0x04,/*<��ȡ�۽�λ��*/

            /*Input Registers*/
            L_IRIS_POSITION         =0x00,/*<��Ȧλ��*/
            L_ZOOM_POSITION         =0x01,/*<����λ��*/
            L_FOCUS_POSITION        =0x02,/*<����λ��*/
            /*Holding Registers*/
            L_BAUDRATE              =0x01,/*<��ͷ������*/
            L_UART                  =0x02,/*<��ͷͨ�ű�׼*/
            L_MODEL                 =0x03,/*<��ͷ�ͺ�*/

            L_IRIS_CONTROL          =0x11,/*<���ƹ�Ȧλ��*/
            L_ZOOM_CONTROL          =0x12,/*<��������λ��*/
            L_FOCUS_CONTROL         =0x13,/*<���ƾ۽�λ��*/

            NDFUN                  =-1
}FunctionType;

/**-------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
/*����ϵͳ��������*/
namespace Sys
{
	namespace Coils
	{
		enum _Coils
		{
			Permission		= SYSTEM|S_SET_CONTROL,   /*<ʹ��λ����bbb��д��Ȩ��*/
			ID			= SYSTEM|S_SCAN_CODER,    /*<ɨ���������id*/
			Status		= SYSTEM|S_CHECK_STATUS,  /*<�����豸��״̬ */
			Data		= SYSTEM|S_COLLECT_DATA,  /*<�ɼ���������������*/
			ToZero		= SYSTEM|S_RETURN_REF,    /*<ϵͳ���زο�ԭ��*/
			Stop		= SYSTEM|S_STOP,          /*<ϵͳ����ֹͣ*/
			Exit		= SYSTEM|S_SERVER_EXIT ,  /*<ϵͳ�������˳���������*/
			Heartbeat	= NDFUN,
		};
	};

	namespace InReg
	{
		enum _InReg
		{
			Control		= SYSTEM|S_GET_CONTROL_IP,     /*<����Ȩ�޼�IP*/
			ID			= SYSTEM|S_GET_SENSORS_ID,     /*<������ID*/
			Status		= SYSTEM|S_GET_DEVICES_STATUS, /*<�豸״̬*/
			TimesTamp   = SYSTEM|S_GET_DATAS,          /*<����������*/
            Mac         = SYSTEM|S_GET_MAC,            /*<��̨������MAC��ַ 20150610*/
            ServerIP    = SYSTEM|S_GET_SERVER_IP ,     /*<��̨������IP     20150610*/
			SynTime		= NDFUN//ͬ��ʱ��
		};
	};

	namespace HoldReg
	{
		enum _HoldReg
		{
			ID			= SYSTEM|S_SET_ID,          /*<��������id*/
			Zero		= SYSTEM|S_CUR_REF,         /*<��ǰλ��Ϊ�ο�ԭ��*/
			Facility	= SYSTEM|S_SWITCH_DEVICE,   /*<ϵͳ�л��豸����*/
			OSVer		= SYSTEM|S_OS,              /*<ϵͳ�Ĳ���ϵͳ��*/
			SoftVer		= SYSTEM|S_VERSION,         /*<ϵͳ�İ汾��*/
			ProDuctDate	= SYSTEM|S_PRODUCTION_TIME, /*<ϵͳ�ĳ���ʱ�� */
			Model		= SYSTEM|S_MODEL,           /*<ϵͳ���ͺ�*/
			SerialNo	= SYSTEM|S_SN,              /*<ϵͳ�����к�*/
		};
	};

};

/*���徵ͷ��������*/
namespace Lens
{
	namespace Coils
	{
		enum _Coils
		{
            Connection       = L_CONNECTION,             /*<��ͷ��������*/
            Reset            = L_RESET,                  /*<��ͷ����*/
            GetIrisPosition  = L_GET_IRIS,               /*<��ȡ��Ȧλ��*/
            GetZoomPosition  = L_GET_ZOOM ,              /*<��ȡ����λ��*/
            GetFocusPosition = L_GET_FOCUS,              /*<��ȡ�۽�λ��*/
		};
	};

	namespace InReg
	{
		enum _InReg
		{
            IrisPosition     = L_IRIS_POSITION,           /*<��Ȧλ��*/
            ZoomPosition     = L_ZOOM_POSITION,           /*<����λ��*/
            FocusPosition    = L_FOCUS_POSITION,          /*<����λ��*/
		};
	};

	namespace HoldReg
	{
		enum _HoldReg
		{
            Baudrate         = L_BAUDRATE,                /*<��ͷ������*/
            CommStandard     = L_UART,                    /*<��ͷͨ�ű�׼*/
            Model            = L_MODEL,                   /*<��ͷ�ͺ�*/

            IrisControl      = L_IRIS_CONTROL,            /*<���ƹ�Ȧλ��*/
            ZoomControl      = L_ZOOM_CONTROL,            /*<��������λ��*/
            FocusControl     = L_FOCUS_CONTROL,           /*<���ƾ۽�λ��*/
		};
	};

};

/*�����������������*/
namespace Sensor
{
	namespace Prefix
	{
		enum _Prefix
		{
			Yaw        = PANCODER,        /*<ƽҡ������*/
			Pitch      = TILTCODER,       /*<����������*/
			CraneYaw   = PANSWINGCODER,   /*<ƽҡҡ�۱�����*/
			CranePitch = TILTSWINGCODER,  /*<����ҡ�۱�����*/
			Zoom       = ZOOMCODER,       /*<�佹������*/
			Focus      = FOCUSCODER,      /*<�۽�������*/
		};
	};

	namespace Coils
	{
		enum _Coils
		{
			Data		= C_COLLECT,         /*<�ɼ���������ֵ*/
			Zero		= C_SET_CUR_ORIGIN,  /*<���õ�ǰλ��Ϊ�������Ĳο�ԭ��*/
			ID			= C_SCAN_ID,         /*<��ѯ��������id*/
		};
	}

	namespace InReg
	{
		enum _InReg
		{
			Data	    = C_GET_DATA,   /*<��������ֵ*/
			Zero		= C_GET_ORGIN,  /*<�ο�ԭ��*/
  /*deprecated */   ID			= C_GET_ID,     /*<��ѯID*/
            DataBits    = C_GET_DATABITS , /*<20150610*/
            ParityBits  = C_GET_PARITYBITS  , /*<20150610*/
            StopBits    = C_GET_STOPBITS ,/*<20150610*/
            FlowBits    = C_GET_FLOWBITS ,/*<20150610*/
		};
	}

	namespace HoldReg
	{
		enum _HoldReg
		{
			ID			= C_SET_ID,    /*<��������id*/
			Baud		= C_SET_BAUD,  /*<�������Ĳ�����*/
			Model		= C_SET_TYPE,  /*<������������*/
			TypeNo		= C_SET_MODEL, /*<���������ͺ�*/
			GearRatio	= C_SET_GEAR,  /*<�������ĳ�����*/
			BITS        = C_SET_BITS,  /*<��������λ��*/
		};
	}
};

/*��������������*/
namespace Motor
{
	namespace Prefix
	{
		enum _Prefix
		{
			Yaw        = PANMOTOR,         /*<��̨ƽҡ���*/
			Pitch      = TILTMOTOR,        /*<��̨�������*/
			CraneYaw   = PANSWINGMOTOR,   /*<ƽҡҡ�۵��*/
			CranePitch = TILTSWINGMOTOR,   /*<����ҡ�۵��*/
			Zoom       =ZOOMMOTOR,         /*<��ͷ�佹���*/
			Focus      =FOCUSMOTOR,        /*<��ͷ�۽����*/
		};
	}

	namespace Coils
	{
		enum _Coils
		{
			Direction		= M_DIR,             /*<���ת������*/
			ToZero			= M_RETURN_ORIGIN,  /*<���ص��ο�ԭ��*/
			Stop			= M_ESTOP,          /*<�����ƶ�*/
			Zero			= M_SET_CUR_ORIGIN, /*<���õ�ǰλ��Ϊ�ο�λ*/
		};
	}

	namespace InReg
	{
		enum _InReg
		{
			Zero			= M_GET_ORIGIN, /*<����Ĳο�ԭ��λ��*/
			ReferenceNo		= NDFUN,
			Alias			= NDFUN,
			RefAngle        = M_GET_REF_OFFSET,/*<���������ת���ĽǶ�*/
		};
	}

	namespace HoldReg
	{
		enum _HoldReg
		{
			MaxSpeed		= M_SET_MAXSPEED,      /*<�����������ٶȣ��������ٶ�*/
			MinSpeed		= M_SET_MINSPEED,      /*<�����С�����ٶȣ��������ٶ�*/
			AccTime			= M_SET_ATIME,         /*<�����������ʱ�� */
			Divider			= M_SET_FACTOR,        /*<�������ϸ����*/
			GearRatio		= M_SET_GEAR,          /*<���������*/
			MoveArithmetic	= M_SET_ALGORITHM,     /*<��������㷨  ����ʹ��20150609*/
			MoveCurve       = M_SET_CURVE,         /*<������������㷨      20150609*/
			MoveRotation    = M_SET_ROTATION,      /*<���������ת�㷨      20150609*/
			MovePeriod      = M_SET_PERIOD,         /*<PWM��������  */
			MoveDuty        = M_SET_DUTY,           /*<PWM����ռ�ձ�*/
			MovePolarity    = M_SET_POLARIT,        /*<PWM���м���*/
			MoveRunStatus   = M_SET_RUN,            /*<PWM����״̬*/
			MoveTime		= M_RUNNING_TIME,      /*<�������ʱ��*/
			MoveAngle		= M_RUNNING_ANGLE,     /*<���������̨���нǶ�*/
			MoveDir		    = M_RUNNING_DIRECTION, /*<���������̨���з���*/
		};
	}
};


#endif // DLP_COMMON_DLPROBOT_H_
