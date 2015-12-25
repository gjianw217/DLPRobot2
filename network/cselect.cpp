/**
* @file       CSelect��Ա����
* @author     GuoJianwei & gjianw217@163.com
* @date       2014.11.21
*/


#include <ctime>
#include "cselect.h"
#include "../utils/cdebug.h"

CSelect::CSelect(){}

 CSelect::~CSelect()
 {
    close(server_sock);

 }

 void  CSelect::fdZero(fd_set *fset)
 {
    FD_ZERO(fset);
 }

void CSelect::fdSet(int fd,fd_set *fset)
{
    FD_SET(fd,fset);
}
bool  CSelect::fdIsset(int fd,fd_set *fset)
{
    return FD_ISSET(fd,fset);
}

void  CSelect::fdClr(int fd,fd_set *fset)
{
    FD_CLR(fd,fset);
}

/**
* @brief  ���г�Ա��������Ҫ��ʾ����ʾ������������
* @note   �ú����Ѿ�����Ա����newclientȡ��
*/
void CSelect::newConnections()
{
    socklen_t addrlen;
    struct sockaddr_in clientaddr;
    int new_sock;

    addrlen=sizeof(clientaddr);
    memset(&clientaddr,0,sizeof(clientaddr));
    new_sock= accept(this->server_sock,(struct sockaddr *)&clientaddr,&addrlen);

    if(-1==new_sock)
    {
        dlp_log(DLP_LOG_DEBUG,"Server acccpet() error");
    }
    else
    {
        fdSet(new_sock,&this->refset);
        if(new_sock>this->fdmax)
        {
            this->fdmax=new_sock;
#ifdef DLP_DEBUG
            std::cout<<"New Connection from "<<inet_ntoa(clientaddr.sin_addr)<<":"<<clientaddr.sin_port<<" on socket "<<new_sock<<std::endl;
#endif
        }
    }

}
/**
* @brief  ���г�Ա��������Ҫ�����µĿͻ��ˣ����ṩ�ͻ��˵�IP�Ͷ˿�
* @param  ����������������������ӵĿͻ��˵�IP
* @return ���������ӵĿͻ��˵Ķ˿ں�
*/
int CSelect::newclient(std::string &ip)
{
    socklen_t addrlen;
    struct sockaddr_in clientaddr;
    int new_sock;
    time_t client_time;
    addrlen=sizeof(clientaddr);
    memset(&clientaddr,0,sizeof(clientaddr));
    new_sock= accept(this->server_sock,(struct sockaddr *)&clientaddr,&addrlen);

    if(new_sock==-1)
    {
        dlp_log(DLP_LOG_DEBUG,"Server acccpet() error");
    }
    else
    {
        fdSet(new_sock,&this->refset);
        if(new_sock>this->fdmax)/*<Ĭ�ϵ����ֵ�Ƿ�������socket*/
        {
            this->fdmax=new_sock;
            ip=inet_ntoa(clientaddr.sin_addr);
            time(&client_time);

            dlp_log(DLP_LOG_DEBUG,"New Client");
			dlp_logs(" IP:",ip.c_str());
			//dlp_log_value("Port",clientaddr.sin_port);
			//dlp_log_value("Socket",new_sock);
			dlp_logs("Time",ctime(&client_time),true);
        }
    }

    return new_sock;
}


int  CSelect::select(int n,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,struct timeval * timeout)
{
    //std::cout<<"CSelect :: select"<<std::endl;
    return select(n,readfds,writefds,exceptfds,timeout);

}

void  CSelect::set_server_sock(int socket)
{
    this->server_sock=socket;
}

void  CSelect::set_fdmax(int cursocket)
{
    if(fdmax<cursocket)
        this->fdmax=cursocket;
}

void  CSelect::set_curset( fd_set fset)
{
    this->curset=fset;
}

void  CSelect::set_refset(fd_set fset)
{
    this->refset=fset;
}

int  CSelect::get_server_sock(void)const
{
    return this->server_sock;
}

int  CSelect::get_fdmax() const
{
    return this->fdmax;
}

fd_set  CSelect::get_curset()const
{
    return this->curset;
}

fd_set  CSelect::get_refset()const
{
    return this->refset;
}
