#ifndef DLP_DLP_DLPMACRO_H_
#define DLP_DLP_DLPMACRO_H_
/**
uncomment DLP_SYNC macro,the system Sync Function will open,
namely the system is to collect the encoder data under the
trigger of synchronizing signal
*/

///Debug Macro
//#define DLP_EXT_SYNC 1             //test-server.cpp
#define DLP_TIMER_SYNC 1           //test-server.cpp
#define DLP_SENSOR 1          //void IEncoder::CounterInit()
#define DLP_CANOPEN_CODER 1 //csystem::CollectSysData()
#define DLP_RS485_CODER 1 //csystem::CollectSysData()

#define DLP_AMEND_MOTOR 1 //csystempwm.cpp                 //CLensParts::CreateCoder
#define DLP_PWM_FEEDBACK_CONTROL 1 //csystem::CollectSysData()

///System Function Macro

#endif //DLP_DLP_DLPMACRO_H_
