/*
* @file   头文件
* @brief  配置类，根据功能需求，封装rapidxml类库
* @author GuoJianwei & gjianw217@163.com
* @see
*/
#ifndef DLP_ROBOT_CCONFIG_H_
#define DLP_ROBOT_CCONFIG_H_

#include <stdint.h>

//#include <cstdlib> //sprintf
#include <string>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"


class CConfig
{
public:
	CConfig();
	~CConfig();
	void Init();
	uint16_t GetValue(const std::string &device_node,const std::string &sub_node);
	int SetValue(const std::string &device_node,const std::string &sub_node,const uint16_t &value);
	void PrintXml(const std::string &file_name="config.xml");
private:
	void PrintInfo(const std::string &file_name="config.xml");
	int Str2Hex(char *num_str);
};
#endif // DLP_ROBOT_CCONFIG_H_



