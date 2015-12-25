/**
* @file       config-class-datamapping.h
* @brief      define the transformation among with the configuration file ,the relating class and the data mapping
* @author     GuoJianwei & gjianw217@163.com
* @see        CConfig,CDataMapping
*/

#ifndef DLP_SERIALIZATION_CONFIG_CLASS_DATAMAPPING_H_
#define DLP_SERIALIZATION_CONFIG_CLASS_DATAMAPPING_H_

#include <stdint.h>
#include <string>
#include "../../dlp/dlp.h"

class CCCD
{
public:
    CCCD();
    ~CCCD();
    /*类中使用的设备梅举类型转成配置文件中的字符串*/
    std::string Ced2Cs(const DeviceType &device);
    /*类中使用的功能梅举类型围成配置文件中的字符串*/
    std::string Cef2Cs(const DeviceType &dev,const FunctionType &func,const RegisterType &reg);
    /*类中使用的设备梅举类型转成映射文件中的高地址*/
    int Ced2Dnh(const DeviceType &device);
    /*类中使用的功能枚举类型围成映射文件中的低地址*/
    int Cef2Dnl(const DeviceType &dev,const FunctionType &func,const RegisterType &reg);
private:
	void Device2Task(const DeviceType &device,TaskType &task);
};

#endif // DLP_SERIALIZATION_CONFIG_CLASS_DATAMAPPING_H_
