
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "cgpio.h"
CGPIO::CGPIO()
{
	m_direction_path=GPIO_DIR;
	m_value_path    =GPIO_DIR;
	fp=NULL;
}
CGPIO::~CGPIO()
{
#ifdef DLP_ARM_LINUX
	fp = fopen("/sys/class/gpio/unexport","w");
	fprintf(fp,"%d",atoi(m_pin.c_str()));
	fclose(fp);
#endif // DLP_ARM_LINUX
	fp=NULL;
}

/**
* @brief 配置引脚及其方向
* @param 参数1为设置的引脚地址值，如26为P8_13　
* @param 参数2为设置该引脚为输出或输入，如0表示输出
* @return 无返回值
*/
void CGPIO::SetPort(const std::string &pin,const uint8_t &direction)
{

	m_pin=pin;
	m_direction_path= m_direction_path.append(m_pin).append("/direction");
	m_value_path    = m_value_path.append(m_pin).append("/value");

#ifdef DLP_ARM_LINUX

	//打开端口
	fp = fopen("/sys/class/gpio/export","w");
	fprintf(fp,"%d",atoi(m_pin.c_str()));
	fclose(fp);	//设置端口方向
	fp = fopen(m_direction_path.c_str(),"w");
	if(fp==NULL)
        printf("error ％d %s\n",errno,strerror(errno));
	if (PINOUT==direction)                             /*<如果设置为输出*/
	{
        fprintf(fp,"out");
	}
	else
	{
		fprintf(fp,"in");///
	}
	fclose(fp);


#endif //DLP_ARM_LINUX
}

/**
* @brief 设置引脚输出的值，
* @param 0表示低电平，1表示高电平
* @return 无返回值
*/
void CGPIO::SetValue(const uint8_t &value)
{

#ifdef DLP_ARM_LINUX
    printf("CGPIO::SetValue");
	if(PINLOW==value)                                /*<如果输出低电平*/
	{
		fp = fopen(this->m_value_path.c_str(),"w");
		fprintf(fp,"%d",PINLOW);
		fclose(fp);
	}
	else
	{
		fp = fopen(this->m_value_path.c_str(),"w");
		fprintf(fp,"%d",PINHIGH);
		fclose(fp);
	}

#endif // DLP_ARM_LINUX
}
uint8_t CGPIO::GetValue()
{

	return 0;
}

