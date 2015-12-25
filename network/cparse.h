/**
* @file       ͷ�ļ�
* @brief      ��Ҫ�������յ�����λ����������Ϊ�����롢�����롢����������
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


    FunctionType ParseCoderFunction(const uint8_t *receive_cmd);/*<���ر������Ĺ�����*/
    FunctionType ParseMotorFunction(const uint8_t *receive_cmd);/*<���ص���Ĺ�����*/
    FunctionType ParseSysFunction(const uint8_t *receive_cmd);/*<����ϵͳ������*/
private:
    DeviceType m_device;
    FunctionType m_function;

};
#endif//DLP_NETWORK_COMMAND_CPARSEBASE_H_
