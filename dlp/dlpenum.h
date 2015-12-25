#ifndef DLP_DLP_DLPENUM_H_
#define DLP_DLP_DLPENUM_H_
enum{BR2400=0,BR4800,BR9600,BR19200,BR38400,BR57600,BR115200,BR_NB= -1};

enum LedType
{
    LED_Lens,LED_PAN,LED_Tilt,LED_Sync,LED_IP,
};
enum LedStatus
{
    LED_Off,LED_On,
};

//gpio pin settings
enum
{
	PINOUT             = 0,      //pin output
	PININ              = 1,
	PINLOW             = 0,      // output high level
	PINHIGH            = 1,
	POS_CLOCKWISE      = 1,     //
	NEG_ANTI_CLOCKWISE = 0
};

enum {
	MOTOR_POS_CLOCKWISE=0,     //代表正向，即顺时针方向
	MOTOR_NEG_CounterCLOCKWISE=1
};

enum {
	Modbus_TCP_Network_DisConnection=-1,//Ctrl +C
	Modbus_TCP_Network_No

};



#endif // DLP_DLP_DLPENUM_H_
