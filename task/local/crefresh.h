/*
* @file   头文件
* @brief  用于更新配置文件
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
	PCDataMapping m_pdatamapping; /*<对当前系统内存数据的操作*/
	PCConfig      m_pconfig;      /*<对本地配置文件操作*/
	PCCCD         m_pccd;         /*<数值与名称的映射*/
};
#endif // DLP_SERILIZATION_REFRESH_H_
