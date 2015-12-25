/*
* @file   头文件
* @brief  自定义上位机与下位机使用Modbus通信，使用的命令集合
* @author GuoJianwei & gjianw217@163.com
*/
#ifndef DLP_COMMON_DLPROBOT_H_
#define DLP_COMMON_DLPROBOT_H_

/*
enum {
	POS_CLOCKWISE=0,     //代表正向，即顺时针方向
	NEG_ANTI_CLOCKWISE=1
};*/

/*定义设备枚举类型*/
typedef enum{
            SYSTEM           =0x000,    /*<控制系统各设备联动、系统软件信息等 */
            LENS             =0x100,    /*<镜头*/
            PANCODER         =0x200,    /*<变焦编码器*/
            TILTCODER        =0x300,    /*<聚焦编码器*/
            ZOOMCODER        =0x400,      /*<平摇编码器*/
            FOCUSCODER       =0x500,    /*<俯仰编码器*/
            PANSWINGCODER    =0x600,    /*<待定编码器*/
            TILTSWINGCODER   =0x700,    /*<待定编码器*/
            PANMOTOR         =0x800,    /*<平摇电机*/
            TILTMOTOR        =0x900,    /*<俯仰电机*/
            ZOOMMOTOR        =0xA00,    /*<变焦电机*/
            FOCUSMOTOR       =0xB00,    /*<聚焦电机*/
            PANSWINGMOTOR    =0xC00,
            TILTSWINGMOTOR   =0xD00,
            NDDEV=-1
}DeviceType;

typedef enum{
            /*定义系统命令类型*/
            /*Coils*/
            S_SET_CONTROL           =0x00, /*<使上位机对bbb有控制写的权利*/
            S_SCAN_CODER            =0x01, /*<扫描编码器的id*/
            S_CHECK_STATUS          =0x02, /*<检查各设备的状态 *///暂时用设备形状替换
            S_COLLECT_DATA          =0x03, /*<采集各传感器的数据*/
            S_RETURN_REF            =0x04, /*<系统返回参考原点*/
            S_STOP                  =0x05, /*<系统立即停止*/
 /*deprecated*/  S_SERVER_EXIT           =0x06, /*<系统退出网络连接*/
            /*Input Register*/
            S_GET_CONTROL_IP        =0x01,
            S_GET_SENSORS_ID        =0x06,
            S_GET_DEVICES_STATUS    =0x0E,
            S_GET_DATAS             =0x10,
            S_GET_MAC               =0x30, /*<云台控制器MAC地址 20150610*/
            S_GET_SERVER_IP         =0x36,  /*<云台控制器IP     20150610*/
            /*Holding Register*/
            S_SET_ID                =0x01, /*<设置控制器的id*/
            S_CUR_REF               =0x02, /*<系统设置当前位置为参考原点*/
            S_SWITCH_DEVICE         =0x03, /*<系统切换设备开关*/
            S_OS                    =0x30, /*<系统的操作系统号*/
            S_VERSION               =0x31, /*<系统的版本号*/
            S_PRODUCTION_TIME       =0x32, /*<系统的出厂时间 */
            S_MODEL                 =0x35, /*<系统的型号*/
            S_SN                    =0x39, /*<系统的序列号*/

            /*Testing*/
            //S_SYN_TIME                   , /*<与上位机进行时间同步*/
            //S_HEARTBEATS                 ,/*<心跳数*/

            /*定义编码器命令类型*/
            /*Coils*/
            C_COLLECT               =0x00, /*<采集编码器的值*/
 /*deprecated*/   C_SET_CUR_ORIGIN        =0x01, /*<设置当前位置为编码器的参考原点*/
            C_SCAN_ID               =0x02, /*<轮询编码器的id*/
            /*Input Register*/
            C_GET_DATA              =0x00,
            C_GET_ORGIN             =0x04,
/*deprecated */  C_GET_ID                =0x06,
            C_GET_DATABITS          =0x06, /*<20150610*/
            C_GET_PARITYBITS        =0x07, /*<20150610*/
            C_GET_STOPBITS          =0x08,/*<20150610*/
            C_GET_FLOWBITS          =0x09,/*<20150610*/
            /*Holding Register*/
            C_SET_ID                =0x00, /*<设置编码器的id*/
            C_SET_BAUD              =0x01, /*<设置编码器的波特率*/
            C_SET_TYPE              =0x03, /*<设置编码器的类型*/
            C_SET_MODEL             =0x04, /*<设置编码器的型号*/
            C_SET_GEAR              =0x05, /*<设置编码器的齿数比*/
            C_SET_BITS              =0x07,  /*<*编码器位数*/
            /*Testing*/
            //C_SET_ORIGIN                  ,  /*<设置编码器的参考点*/

            /*定义电机命令类型*/
            /*Coils*/
 /*deprecated*/  M_DIR                   =0x00, /*设置电机转动方向 */
            M_RETURN_ORIGIN         =0x01, /*<返回当前参考位*/
            M_ESTOP                 =0x02, /*<紧急制动*/
 /*deprecated*/  M_SET_CUR_ORIGIN        =0x03, /*<设置当前位置为参考位*/
            /*Input Register*/
            M_GET_ORIGIN            =0x00,
 /*deprecated*/M_GET_REF_OFFSET        =0x05, /*<保存编码器转过的角度*/
             /*Holding Register*/
            M_SET_MAXSPEED          =0x00, /*<电机最大运行速度，即正常速度*/
            M_SET_MINSPEED          =0x01, /*<电机最小运行速度，即启动速度*/
            M_SET_ATIME             =0x02, /*<电机启动加速时间 */
            M_SET_FACTOR            =0x03, /*<电机驱动细分数*/
            M_SET_GEAR              =0x04, /*<电机齿数比*/
/*deprecated*/M_SET_ALGORITHM            , /*<电机运行算法       20150609*/
			M_SET_CURVE             =0x06,  /*<电机运行算法 曲线 20150609*/
			M_SET_ROTATION          = 0x07, /*<电机运行算法 旋转 20150609*/
			M_SET_PERIOD            =0x0A, /*<PWM运行周期  */
			M_SET_DUTY              =0x0C, /*<PWM运行占空比*/
			M_SET_POLARIT           =0x0E, /*<PWM运行极性*/
			M_SET_RUN               =0x0F, /*<PWM运行状态*/

            M_RUNNING_TIME          =0x10, /*<电机运行时间*/
            M_RUNNING_ANGLE         =0x12, /*<电机控制云台偏移角度*/
            M_RUNNING_DIRECTION     =0x14, /*<电机控制云台运行方向*/
            /*Testing*/
            //M_SET_ORIGIN                 ,     /*<设置电机参考位*/

            /*定义镜头命令类型*/
            /*Coils*/
            L_CONNECTION            =0x00,/*<镜头启动连接*/
            L_RESET                 =0x01,/*<镜头重启*/
            L_GET_IRIS              =0x02,/*<获取光圈位置*/
            L_GET_ZOOM              =0x03,/*<获取缩放位置*/
            L_GET_FOCUS             =0x04,/*<获取聚焦位置*/

            /*Input Registers*/
            L_IRIS_POSITION         =0x00,/*<光圈位置*/
            L_ZOOM_POSITION         =0x01,/*<缩放位置*/
            L_FOCUS_POSITION        =0x02,/*<缩放位置*/
            /*Holding Registers*/
            L_BAUDRATE              =0x01,/*<镜头波特率*/
            L_UART                  =0x02,/*<镜头通信标准*/
            L_MODEL                 =0x03,/*<镜头型号*/

            L_IRIS_CONTROL          =0x11,/*<控制光圈位置*/
            L_ZOOM_CONTROL          =0x12,/*<控制缩放位置*/
            L_FOCUS_CONTROL         =0x13,/*<控制聚焦位置*/

            NDFUN                  =-1
}FunctionType;

/**-------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
/*定义系统命令类型*/
namespace Sys
{
	namespace Coils
	{
		enum _Coils
		{
			Permission		= SYSTEM|S_SET_CONTROL,   /*<使上位机对bbb有写的权利*/
			ID			= SYSTEM|S_SCAN_CODER,    /*<扫描编码器的id*/
			Status		= SYSTEM|S_CHECK_STATUS,  /*<检查各设备的状态 */
			Data		= SYSTEM|S_COLLECT_DATA,  /*<采集各传感器的数据*/
			ToZero		= SYSTEM|S_RETURN_REF,    /*<系统返回参考原点*/
			Stop		= SYSTEM|S_STOP,          /*<系统立即停止*/
			Exit		= SYSTEM|S_SERVER_EXIT ,  /*<系统服务器退出网络连接*/
			Heartbeat	= NDFUN,
		};
	};

	namespace InReg
	{
		enum _InReg
		{
			Control		= SYSTEM|S_GET_CONTROL_IP,     /*<控制权限及IP*/
			ID			= SYSTEM|S_GET_SENSORS_ID,     /*<传感器ID*/
			Status		= SYSTEM|S_GET_DEVICES_STATUS, /*<设备状态*/
			TimesTamp   = SYSTEM|S_GET_DATAS,          /*<传感器数据*/
            Mac         = SYSTEM|S_GET_MAC,            /*<云台控制器MAC地址 20150610*/
            ServerIP    = SYSTEM|S_GET_SERVER_IP ,     /*<云台控制器IP     20150610*/
			SynTime		= NDFUN//同步时间
		};
	};

	namespace HoldReg
	{
		enum _HoldReg
		{
			ID			= SYSTEM|S_SET_ID,          /*<控制器的id*/
			Zero		= SYSTEM|S_CUR_REF,         /*<当前位置为参考原点*/
			Facility	= SYSTEM|S_SWITCH_DEVICE,   /*<系统切换设备开关*/
			OSVer		= SYSTEM|S_OS,              /*<系统的操作系统号*/
			SoftVer		= SYSTEM|S_VERSION,         /*<系统的版本号*/
			ProDuctDate	= SYSTEM|S_PRODUCTION_TIME, /*<系统的出厂时间 */
			Model		= SYSTEM|S_MODEL,           /*<系统的型号*/
			SerialNo	= SYSTEM|S_SN,              /*<系统的序列号*/
		};
	};

};

/*定义镜头命令类型*/
namespace Lens
{
	namespace Coils
	{
		enum _Coils
		{
            Connection       = L_CONNECTION,             /*<镜头启动连接*/
            Reset            = L_RESET,                  /*<镜头重启*/
            GetIrisPosition  = L_GET_IRIS,               /*<获取光圈位置*/
            GetZoomPosition  = L_GET_ZOOM ,              /*<获取缩放位置*/
            GetFocusPosition = L_GET_FOCUS,              /*<获取聚焦位置*/
		};
	};

	namespace InReg
	{
		enum _InReg
		{
            IrisPosition     = L_IRIS_POSITION,           /*<光圈位置*/
            ZoomPosition     = L_ZOOM_POSITION,           /*<缩放位置*/
            FocusPosition    = L_FOCUS_POSITION,          /*<缩放位置*/
		};
	};

	namespace HoldReg
	{
		enum _HoldReg
		{
            Baudrate         = L_BAUDRATE,                /*<镜头波特率*/
            CommStandard     = L_UART,                    /*<镜头通信标准*/
            Model            = L_MODEL,                   /*<镜头型号*/

            IrisControl      = L_IRIS_CONTROL,            /*<控制光圈位置*/
            ZoomControl      = L_ZOOM_CONTROL,            /*<控制缩放位置*/
            FocusControl     = L_FOCUS_CONTROL,           /*<控制聚焦位置*/
		};
	};

};

/*定义编码器命令类型*/
namespace Sensor
{
	namespace Prefix
	{
		enum _Prefix
		{
			Yaw        = PANCODER,        /*<平摇编码器*/
			Pitch      = TILTCODER,       /*<俯仰编码器*/
			CraneYaw   = PANSWINGCODER,   /*<平摇摇臂编码器*/
			CranePitch = TILTSWINGCODER,  /*<俯仰摇臂编码器*/
			Zoom       = ZOOMCODER,       /*<变焦编码器*/
			Focus      = FOCUSCODER,      /*<聚焦编码器*/
		};
	};

	namespace Coils
	{
		enum _Coils
		{
			Data		= C_COLLECT,         /*<采集编码器的值*/
			Zero		= C_SET_CUR_ORIGIN,  /*<设置当前位置为编码器的参考原点*/
			ID			= C_SCAN_ID,         /*<轮询编码器的id*/
		};
	}

	namespace InReg
	{
		enum _InReg
		{
			Data	    = C_GET_DATA,   /*<编码器的值*/
			Zero		= C_GET_ORGIN,  /*<参考原点*/
  /*deprecated */   ID			= C_GET_ID,     /*<轮询ID*/
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
			ID			= C_SET_ID,    /*<编码器的id*/
			Baud		= C_SET_BAUD,  /*<编码器的波特率*/
			Model		= C_SET_TYPE,  /*<编码器的类型*/
			TypeNo		= C_SET_MODEL, /*<编码器的型号*/
			GearRatio	= C_SET_GEAR,  /*<编码器的齿数比*/
			BITS        = C_SET_BITS,  /*<编码器的位数*/
		};
	}
};

/*定义电机命令类型*/
namespace Motor
{
	namespace Prefix
	{
		enum _Prefix
		{
			Yaw        = PANMOTOR,         /*<云台平摇电机*/
			Pitch      = TILTMOTOR,        /*<云台俯仰电机*/
			CraneYaw   = PANSWINGMOTOR,   /*<平摇摇臂电机*/
			CranePitch = TILTSWINGMOTOR,   /*<俯仰摇臂电机*/
			Zoom       =ZOOMMOTOR,         /*<镜头变焦电机*/
			Focus      =FOCUSMOTOR,        /*<镜头聚焦电机*/
		};
	}

	namespace Coils
	{
		enum _Coils
		{
			Direction		= M_DIR,             /*<电机转动方向*/
			ToZero			= M_RETURN_ORIGIN,  /*<返回到参考原点*/
			Stop			= M_ESTOP,          /*<紧急制动*/
			Zero			= M_SET_CUR_ORIGIN, /*<设置当前位置为参考位*/
		};
	}

	namespace InReg
	{
		enum _InReg
		{
			Zero			= M_GET_ORIGIN, /*<电机的参考原点位置*/
			ReferenceNo		= NDFUN,
			Alias			= NDFUN,
			RefAngle        = M_GET_REF_OFFSET,/*<保存编码器转过的角度*/
		};
	}

	namespace HoldReg
	{
		enum _HoldReg
		{
			MaxSpeed		= M_SET_MAXSPEED,      /*<电机最大运行速度，即正常速度*/
			MinSpeed		= M_SET_MINSPEED,      /*<电机最小运行速度，即启动速度*/
			AccTime			= M_SET_ATIME,         /*<电机启动加速时间 */
			Divider			= M_SET_FACTOR,        /*<电机驱动细分数*/
			GearRatio		= M_SET_GEAR,          /*<电机齿数比*/
			MoveArithmetic	= M_SET_ALGORITHM,     /*<电机运行算法  不再使用20150609*/
			MoveCurve       = M_SET_CURVE,         /*<电机运行曲线算法      20150609*/
			MoveRotation    = M_SET_ROTATION,      /*<电机运行旋转算法      20150609*/
			MovePeriod      = M_SET_PERIOD,         /*<PWM运行周期  */
			MoveDuty        = M_SET_DUTY,           /*<PWM运行占空比*/
			MovePolarity    = M_SET_POLARIT,        /*<PWM运行极性*/
			MoveRunStatus   = M_SET_RUN,            /*<PWM运行状态*/
			MoveTime		= M_RUNNING_TIME,      /*<电机运行时间*/
			MoveAngle		= M_RUNNING_ANGLE,     /*<电机控制云台运行角度*/
			MoveDir		    = M_RUNNING_DIRECTION, /*<电机控制云台运行方向*/
		};
	}
};


#endif // DLP_COMMON_DLPROBOT_H_
