#include "crs485coder.h"
#include "../../drivers/cserial.h"
#include "../../drivers/cgpio.h"

CRS485Coder::CRS485Coder():IEncoder()
{
	m_pserial=PCSerial(new CSerial());
	//m_preadwrite=PCGPIO(new CGPIO());
}

CRS485Coder::CRS485Coder(std::string dev_name):IEncoder()//iparts calling this construction function
{
    m_dev_name=dev_name;
    m_pserial=PCSerial(new CSerial());
	//m_preadwrite=PCGPIO(new CGPIO());

}
CRS485Coder::CRS485Coder(PCSerial pserial):IEncoder()
{
	m_pserial=pserial;
	//m_preadwrite=PCGPIO(new CGPIO());
}
CRS485Coder::~CRS485Coder()
{

}

void CRS485Coder::Config(const DLPEncoderAttr &attr)
{
	m_attr=attr;

	if (DLP_FOCUS==m_attr.dlp_role)
	{
		m_pserial->Open(m_dev_name.c_str());
	}
	else
	{
		m_pserial->Open(m_dev_name.c_str());
	}
	m_pserial->Config(m_attr.dlp_serial.baudrate,m_attr.dlp_serial.databit,m_attr.dlp_serial.parity,m_attr.dlp_serial.stop);
#ifdef Cansel_This_Macro_To_Using
#endif // 0


}

int CRS485Coder::GetData(uint16_t *data)
{
	uint16_t ret=0;
	uint8_t cmd[8]={0};

    ret=m_pserial->Read(cmd,5);///////
    data[0]=cmd[0];
    data[1]=cmd[1];
    data[2]=cmd[2];
    data[3]=cmd[3];
    data[4]=cmd[4];
    return ret;

    ///////////////////////////////////////////////////////////////////////////////////
//
//	cmd[0]=m_attr.dlp_id;//////////
//	cmd[1]=0x03;
//	cmd[2]=0x00;
//	cmd[3]=0x00;
//	cmd[4]=0x00;
//	cmd[5]=0x01;
//
//	ret=GetCRC(cmd,6);
//	cmd[6]=(ret&0x0FF00)>>8;
//	cmd[7]=ret&0x0FF;
//
////	m_preadwrite->SetValue(PINHIGH);
////    delays(2);
//	//////ret=m_pserial->Write(cmd,8);
//
//	//////printf("CRS485Coder::GetData:Write:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);
//	if (8)//////
//	{
//
////        m_preadwrite->SetValue(PINLOW);
////        delays(2);
//        memset(cmd,0,8);
//		ret=m_pserial->Read(cmd,4);///////
//		if (4==ret)/////////////////////////
//		{
//			printf("CRS485Coder::GetData:Read:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);
//			data[0]=cmd[4];
//			data[1]=cmd[3];
//			this->m_pcounter->SetCounter(data[0]);
//			m_angle=this->m_pcounter->GetAngle();          /*Save the encoder turned Angle*/
//			m_angle=m_angle*m_attr.dlp_gear[1]/m_attr.dlp_gear[0];
//			ret= 0;
//		}
//		else
//		{
//            printf("CRS485Coder::GetData Read Failure: %d\n",ret);
//            printf("CRS485Coder::GetData:Read:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);
//			ret= -1;
//		}
//
//	}
//	else
//	{
//		data[0]=0;
//		data[1]=0;
//		printf("CRS485Coder::GetData Write Failure %d \n",ret);
//		printf("CRS485Coder::GetData:Write:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);
//
//		ret=-1;
//	}
//
//	return ret;
}

int CRS485Coder::PollID(uint16_t *id)
{
    uint16_t ret;
	uint8_t cmd[8]={0};
	cmd[0]=0xff;//////////
	cmd[1]=0xa0;
	cmd[2]=0x40;
	cmd[3]=0x38;
	//m_preadwrite->SetValue(PINHIGH);
	ret=m_pserial->Write(cmd,4);
	printf("CRS485Coder::GetData:Write:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);
	if (4==ret)
	{
        memset(cmd,0,8);
        ////m_preadwrite->SetValue(PINLOW);
		ret=m_pserial->Read(cmd,5);
		if (5==ret)
		{
			printf("CRS485Coder::GetData:Read:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);
			id[0]=cmd[3];
			ret=0;
		}
		else
		{
            printf("CRS485Coder::GetData Read Failure: %d\n",ret);
            printf("CRS485Coder::GetData:Read:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);

            ret=-1;
		}

	}
	else
	{
		id[0]=0;
		printf("CRS485Coder::GetData Write Failure %d \n",ret);
        printf("CRS485Coder::GetData:Write:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",cmd[0],cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7]);

		ret=-1;
	}
	return ret;
}

int CRS485Coder::SetBaudrate(const uint16_t &high_rate,const uint16_t &low_rate)
{

	return 0;
}

int CRS485Coder::SetID(const uint16_t &id)
{

	return 0;
}

uint16_t CRS485Coder::GetCRC(uint8_t *cmd,uint8_t cmd_len)
{
	uint16_t crcreg=0x0FFFF;
	uint8_t leastbit;
	uint8_t high8,low8;
	for (int i=0;i<cmd_len;i++)
	{
		crcreg=cmd[i]^crcreg;

		for (int j=0;j<8;j++)
		{
			leastbit=crcreg&0x01;
			crcreg=crcreg>>1;
			if (leastbit==0)
			{
				continue;
			}
			else
			{
				crcreg=crcreg^0xA001;
			}
		}
	}

	high8=crcreg;
	low8=crcreg>>8;
	crcreg=high8;
	crcreg=crcreg<<8;
	crcreg=crcreg|low8;
	return crcreg;
}




