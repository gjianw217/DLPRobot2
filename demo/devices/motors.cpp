#include "../../utils/cdebug.h"
#include "../../robot/cconfig.h"
#include "../../network/cdata-mapping.h"
#include "../../robot/crobot.h"
#include "../../devices/encoder/iencoder.h"

#include "../../devices/motors/cstepmotor.h"
#include "../../utils/cdelay.h"

void TestStepMotor(void)
{
	dlp_log(DLP_LOG_DEBUG,"Test StepMotor and T Curve");

    double angle=10;     //degree
    uint32_t time=0;//ms
//    uint32_t time=100000;//ms
    uint16_t dir=0;
    uint8_t curve=2;//T

    DLPMotorAttr attr;
    attr.dlp_algorithm.acc=200;
    attr.dlp_algorithm.division=7;
    attr.dlp_algorithm.gear[0]=1;
    attr.dlp_algorithm.gear[1]=1;
    attr.dlp_algorithm.max_speed=740;
    attr.dlp_algorithm.min_speed=140;
    attr.dlp_algorithm.role=DLP_PAN;
    attr.dlp_curve=DLP_MOTOR_CURVE_T;
    attr.dlp_dir.pin=78;
    attr.dlp_dir.value=0;
    attr.dlp_rotation=DLP_MOTOR_ROTATION_720;

    PIMotor pmotor;
    pmotor=PCStepMotor(new CStepMotor());
    pmotor->SetAttr(attr);
//    while(1)
    {
        static uint32_t times=0;

        pmotor->RunbyAngleTimeDir(angle,time,dir,curve);

        dlp_log_value(DLP_LOG_DEBUG,"TestRobotInit DLP_PAN Motor times",times++);

//        delays(10);

    }

}

