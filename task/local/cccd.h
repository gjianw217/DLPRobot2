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
    /*����ʹ�õ��豸÷������ת�������ļ��е��ַ���*/
    std::string Ced2Cs(const DeviceType &device);
    /*����ʹ�õĹ���÷������Χ�������ļ��е��ַ���*/
    std::string Cef2Cs(const DeviceType &dev,const FunctionType &func,const RegisterType &reg);
    /*����ʹ�õ��豸÷������ת��ӳ���ļ��еĸߵ�ַ*/
    int Ced2Dnh(const DeviceType &device);
    /*����ʹ�õĹ���ö������Χ��ӳ���ļ��еĵ͵�ַ*/
    int Cef2Dnl(const DeviceType &dev,const FunctionType &func,const RegisterType &reg);
private:
	void Device2Task(const DeviceType &device,TaskType &task);
};

#endif // DLP_SERIALIZATION_CONFIG_CLASS_DATAMAPPING_H_
