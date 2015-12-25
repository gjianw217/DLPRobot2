#include "../network/cdata-mapping.h"
#include "cmodbus.h"

CModbus::CModbus(PCDataMapping datamapping,const char *ip_address, const int &port)
{
	m_pdatamapping=datamapping;
	this->m_pmb=m_pdatamapping->GetUnit();
    char ip[20]={'\0'};
    uint16_t dest[4]={0};
    uint16_t pport=0;
    dest[0]=this->m_pmb->tab_registers[0x08];
    dest[1]=this->m_pmb->tab_registers[0x07];
    dest[2]=this->m_pmb->tab_registers[0x06];
    dest[3]=this->m_pmb->tab_registers[0x05];
    pport=this->m_pmb->tab_registers[0x004];

	Array2IP(dest,ip);
    std::cout<<"modbus tcp server::"<<ip<<":"<<pport<<std::endl;
    this->m_pctx = modbus_new_tcp(ip, pport);

}

CModbus::~CModbus()
{
    if(NULL!=this->m_pctx)
        modbus_free(this->m_pctx);
    if(NULL!=this->m_pctx)  /*该空间的释放，由类CDataMapping完成*/
        this->m_pmb =NULL;

     std::cout<<"~CModbus()"<<std::endl;

}
/************************************************************************/
/* 以下函数主要是封装Modbus协议中的关键函数，以完成通信        */
/************************************************************************/
int CModbus::Receive(uint8_t *req)
{
    assert(NULL!=req);
    return modbus_receive(this->m_pctx, req);
}

int CModbus::Reply(const uint8_t *req,const int &req_length)
{
    assert(NULL!=req);
    assert(req_length>0);

    return modbus_reply(this->m_pctx, req, req_length, this->m_pmb);
}

int CModbus::ListenNum(const int &nb_connection)
{
    assert(nb_connection>0);

    return modbus_tcp_listen(this->m_pctx, nb_connection);
}

int CModbus::Accept(int *socket)
{
    assert(NULL!=socket);

    return modbus_tcp_accept(this->m_pctx,socket);
}

int CModbus::SetSocket(const int &socket)
{
    assert(socket>0);

    modbus_set_socket(this->m_pctx,socket);
    return 0 ;
}

int CModbus::SetSlave(const int &slave)
{
    assert(slave>0);
    return modbus_set_slave(this->m_pctx,slave);/*<默认为 MODBUS_TCP_SLAVE=0xFF*/
}

PCDataMapping CModbus::GetDataMapping()
{
	return m_pdatamapping;
}
/**
* @brief 显示Modbus数据单元中的数据
* @note  主要在调试中调用
*/
void CModbus::Show(const int &device,const int &tab)
{
    int i=device,i_max;
    i_max=i+0xFF;
    switch(tab)
    {
        case MODBUS_COILS:
        {
            for(;i<i_max;i++)
            {
                std::cout<<"modbus register[" <<std::hex<<i<<"]:"
                <<std::dec<<m_pmb->tab_bits[i]<<std::endl;
            }
            break;
        }
        case MODBUS_DISCRETE_INPUT:
        {
            for(;i<i_max;i++)
            {
                std::cout<<"modbus register[" <<std::hex<<i<<"]:"
                <<std::dec<<m_pmb->tab_input_bits[i]<<std::endl;
            }
            break;
        }
        case MODBUS_INPUT_REGISTERS:
        {
            for(;i<i_max;i++)
            {
                std::cout<<"modbus register[" <<std::hex<<i<<"]:"
                <<std::dec<<m_pmb->tab_input_registers[i]<<std::endl;
            }
            break;

        }
        case MODBUS_HOLDING_REGISTERS:
        {
            for(;i<i_max;i++)
            {
                std::cout<<"modbus register[" <<std::hex<<i<<"]:"
                <<std::dec<<m_pmb->tab_registers[i]<<std::endl;
            }
            break;
        }
        default:
        {
            std::cout<<"please select the tab properly"<<std::endl;
        }
    }
}



void CModbus::Array2IP(const uint16_t *ip_array,char *ip)
{
	char dot='.';
	//sprintf(ip,"%d%c%d%c%d%c%d",ip_array[3],dot,ip_array[2],dot,ip_array[1],dot,ip_array[0]);
	sprintf(ip,"%d%c%d%c%d%c%d",ip_array[0],dot,ip_array[1],dot,ip_array[2],dot,ip_array[3]);
}
