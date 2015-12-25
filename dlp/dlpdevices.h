#ifndef DLP_DLP_DLPDEVICES_H_
#define DLP_DLP_DLPDEVICES_H_
#include <stdint.h>

typedef struct
{
	uint8_t baudrate;
	uint8_t databit;
	uint8_t parity;
	uint8_t stop;
	uint8_t flow;

}DLPSerialAttr;

typedef enum
{
	DLP_PAN=1,
	DLP_TILT=2,
	DLP_ZOOM=3,
	DLP_FOCUS=4,

	DLP_NO=-1
}DLPRole;
typedef struct
{
	uint16_t dlp_id;
	uint16_t dlp_type;
	uint16_t dlp_model;
	uint16_t dlp_bits;
	uint16_t dlp_gear[2];
	DLPRole  dlp_role;
	DLPSerialAttr dlp_serial;
}DLPEncoderAttr;

typedef enum
{
    DLP_MOTOR_ROTATION_TEST  =0,
	DLP_MOTOR_ROTATION_360=1,
	DLP_MOTOR_ROTATION_720=2,
	DLP_MOTOR_ROTATION_ANY=3,
	DLP_MOTOR_ROTATION_NO=-1
}DLPMotorRotationType;

typedef enum
{
    DLP_MOTOR_CURVE_TEST  =0,
	DLP_MOTOR_CURVE_L=1,
	DLP_MOTOR_CURVE_T=2,
	DLP_MOTOR_CURVE_S=3,
	DLP_MOTOR_CURVE_NO=-1
}DLPMotorCurveType;

typedef struct
{
 	uint32_t periodNs;
	uint32_t dutyNs;
	uint16_t polarity;
	uint16_t runStatus;

	uint16_t pwmpin;
	uint16_t pwmvalue;
}DLPPWMAttr;

typedef struct
{
	uint16_t pin;
	uint16_t value;
}DLPDirAttr;
typedef struct
{
	uint16_t max_speed;
	uint16_t min_speed;
	uint16_t gear[2];
	uint16_t acc;
	uint8_t division;
	DLPRole  role;

}DLPAlgorithmAttr;

typedef struct
{
	DLPDirAttr dlp_dir;
	DLPAlgorithmAttr dlp_algorithm;
	DLPPWMAttr dlp_pwm;
	DLPMotorCurveType dlp_curve;
	DLPMotorRotationType dlp_rotation;
	uint16_t dlp_type;
	uint16_t dlp_model;

}DLPMotorAttr;

typedef struct
{
    long pwm_period_ns;
    float step_angle;
    float coder_gear_rate;//Coder to PTZ
    float motor_gear_rate;//Motor to PTZ
    int motor_speed;
    float coder_unit_angle;//The angle that the coder rotates a step
    float coder_unit_pulse;//the pusle that the coder rotates a coder_unit_angle
}AmendAttr;





typedef enum
{
    CAN_CODER_BOCHEN=1,
    RS485_CODER_BOCHEN=2,
}DLPCoderType;

typedef enum
{
    STEP_MOTOR_BY_PWM=1,
    STEP_MOTOR_BY_PRU=2,
}DLPMotorType;

typedef enum
{
    Proximity_Switch=1
}DLPSwitchType;

typedef enum
{

    DLP_PULSE_NO=-1,
    DLP_PULSE_PAN=0,
    DLP_PULSE_TILT=1,
    DLP_PULSE_ZOOM=2,
    DLP_PULSE_FOCUS=3,
    DLP_PULSE_MAX=4

}DLPMotorPulse;
#endif //DLP_DLP_DLPDEVICES_H_
