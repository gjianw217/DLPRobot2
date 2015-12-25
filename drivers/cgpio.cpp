
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
* @brief �������ż��䷽��
* @param ����1Ϊ���õ����ŵ�ֵַ����26ΪP8_13��
* @param ����2Ϊ���ø�����Ϊ��������룬��0��ʾ���
* @return �޷���ֵ
*/
void CGPIO::SetPort(const std::string &pin,const uint8_t &direction)
{

	m_pin=pin;
	m_direction_path= m_direction_path.append(m_pin).append("/direction");
	m_value_path    = m_value_path.append(m_pin).append("/value");

#ifdef DLP_ARM_LINUX

	//�򿪶˿�
	fp = fopen("/sys/class/gpio/export","w");
	fprintf(fp,"%d",atoi(m_pin.c_str()));
	fclose(fp);	//���ö˿ڷ���
	fp = fopen(m_direction_path.c_str(),"w");
	if(fp==NULL)
        printf("error ��d %s\n",errno,strerror(errno));
	if (PINOUT==direction)                             /*<�������Ϊ���*/
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
* @brief �������������ֵ��
* @param 0��ʾ�͵�ƽ��1��ʾ�ߵ�ƽ
* @return �޷���ֵ
*/
void CGPIO::SetValue(const uint8_t &value)
{

#ifdef DLP_ARM_LINUX
    printf("CGPIO::SetValue");
	if(PINLOW==value)                                /*<�������͵�ƽ*/
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

