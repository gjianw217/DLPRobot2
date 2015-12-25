
#ifndef DLP_COMMON_DLPGPIO_H_
#define DLP_COMMON_DLPGPIO_H_


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

#endif // DLP_COMMON_DLPGPIO_H_
