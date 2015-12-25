/**
* @file       头文件
* @brief      主要解析接收到的上位机命令，将其分为外设码、功能码、具体命令码
* @author     GuoJianwei & gjianw217@163.com
* @see        CModbus,CTask
*/

#ifndef DLP_NETWORK_COMMAND_CPARSEBASE_H_
#define DLP_NETWORK_COMMAND_CPARSEBASE_H_

#include <stdint.h>
#include "../dlp/dlp.h"

class CParse
{
public:
    CParse();
    virtual ~CParse();
    int Parse(const uint8_t *receive_cmd,DLPModbusCmd &cmd);

private:
    int ParseTask(const uint8_t *receive_cmd,DLPModbusCmd &cmd);
    int ParseDeviceFunction(const uint8_t *receive_cmd,DLPModbusCmd &cmd);
    int ParseRegister(const uint8_t *receive_cmd,DLPModbusCmd &cmd);
    int ParseCommand(const uint8_t *receive_cmd,DLPModbusCmd &cmd);


    FunctionType ParseCoderFunction(const uint8_t *receive_cmd);/*<返回编码器的功能码*/
    FunctionType ParseMotorFunction(const uint8_t *receive_cmd);/*<返回电机的功能码*/
    FunctionType ParseSysFunction(const uint8_t *receive_cmd);/*<返回系统功能码*/
private:
    DeviceType m_device;
    FunctionType m_function;

};
#endif//DLP_NETWORK_COMMAND_CPARSEBASE_H_
