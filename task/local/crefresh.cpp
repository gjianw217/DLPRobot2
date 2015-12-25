#include <cstdlib>
#include <string>
#include "../../robot/cconfig.h"
#include "../../network/cdata-mapping.h"
#include "../../utils/cdebug.h"
#include "cccd.h"
#include "crefresh.h"
CRefresh::CRefresh()
{
	m_pccd=PCCCD(new CCCD());
}
CRefresh::~CRefresh()
{

}
void CRefresh::SetDataMapping(PCDataMapping datamapping)
{
	m_pdatamapping=datamapping;
}
void CRefresh::SetConfig(PCConfig config)
{
	m_pconfig=config;
}

void CRefresh::Update(DLPModbusCmd cmd,const bool &setting)
{
	dlp_log(DLP_LOG_DEBUG,"CRefresh::Update");
   // ������ʼ��
   int ret;
   char suffix[2];/*2λ�����������10��������value���ݶ�Ӧ*/
   std::string strdev,strfunc;
   uint16_t intaddr,intdevaddr,intfuncaddr;
   //ת������
   strdev=m_pccd->Ced2Cs(cmd.dev_type);
   strfunc=m_pccd->Cef2Cs(cmd.dev_type,cmd.dev_func,cmd.reg_type);
   intdevaddr=m_pccd->Ced2Dnh(cmd.dev_type);                  /*���豸����ת�����͵�ֵַ*/
   intfuncaddr=m_pccd->Cef2Dnl(cmd.dev_type,cmd.dev_func,cmd.reg_type);/*����������ת�����͵�ֵַ*/
   intaddr=cmd.dev_type|intfuncaddr;

   std::cout<<"Devices:"<<strdev<<"::Function:"<<strfunc<<"::Data:"<<cmd.cmd_data[0]<<std::endl;
   //��������
   if(true==setting)
   {
		std::cout<<"refresh updating before"<<std::endl;
        ret=m_pconfig->SetValue(strdev,strfunc,cmd.cmd_data[0]);
		std::cout<<"refresh updating after:"<<ret<<std::endl;
        if(2<=cmd.cmd_len&&ret==0)
        {
            for(int i=1;i<cmd.cmd_len;i++)
            {
                ret=strfunc.length()-1;
                sprintf(suffix,"%d",i);
                strfunc=strfunc.substr(0,ret)+suffix;
                m_pconfig->SetValue(strdev,strfunc,cmd.cmd_data[i]);
            }
        }
   }
   else/**/
   {
        uint16_t value[10]={0};//�������5�����֣���bit0,bit1,....,bit9
        value[0]=m_pconfig->GetValue(strdev,strfunc);
        if(2<=cmd.cmd_len)
        {
            for(int i=1;i<cmd.cmd_len;i++)
            {
                ret=strfunc.length()-1;
                sprintf(suffix,"%d",i);
                strfunc=strfunc.substr(0,ret)+suffix;
                value[i]=m_pconfig->GetValue(strdev,strfunc);
            }
        }
        m_pdatamapping->SetHoldRegisters(value,intaddr,cmd.cmd_len);
   }
}
