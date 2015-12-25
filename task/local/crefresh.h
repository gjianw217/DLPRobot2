/*
* @file   ͷ�ļ�
* @brief  ���ڸ��������ļ�
* @author GuoJianwei & gjianw217@163.com
* @see
*/
#ifndef DLP_SERILIZATION_REFRESH_H_
#define DLP_SERILIZATION_REFRESH_H_
#include "../../dlp/dlp.h"

class CRefresh
{
public:
	CRefresh();
	~CRefresh();
	void SetDataMapping(PCDataMapping datamapping);
	void SetConfig(PCConfig config);

	void Update(DLPModbusCmd cmd,const bool &setting);

private:
	PCDataMapping m_pdatamapping; /*<�Ե�ǰϵͳ�ڴ����ݵĲ���*/
	PCConfig      m_pconfig;      /*<�Ա��������ļ�����*/
	PCCCD         m_pccd;         /*<��ֵ�����Ƶ�ӳ��*/
};
#endif // DLP_SERILIZATION_REFRESH_H_
