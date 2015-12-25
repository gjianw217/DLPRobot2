
/**
* @file       头文件
* @brief      主要封装select相关函数
* @author     GuoJianwei & gjianw217@163.com
* @note       select（）函数有点问题，待彻底解决
* @copyright  Copyright 2014 dlp Inc.
*/

#ifndef DLP_NETWORK_CSELECT_H_
#define DLP_NETWORK_CSELECT_H_

#include <iostream>
#include <cstring> //memset()
#include <cstdio>
#include "../dlp/dlp.h"

class CSelect
{
public:
    CSelect();
    virtual ~CSelect();
    void fdZero(fd_set *set);
    void fdSet(int fd,fd_set*set);
    bool fdIsset(int fd,fd_set *set);
    void fdClr(int fd,fd_set* set);
    void newConnections();
    int newclient(std::string &ip);
    int select(int n,fd_set * readfds,fd_set * writefds,fd_set * exceptfds,
          struct timeval * timeout);/*timeout=NULL,阻塞；0非阻塞；其他，时间阻塞*/

    void set_server_sock(int);
    void set_fdmax(int);
    void set_curset(fd_set);
    void set_refset(fd_set);
    int get_server_sock(void)const;
    int get_fdmax() const;
    fd_set get_curset()const;
    fd_set get_refset()const;

    int server_sock;
    int fdmax;
    fd_set curset;
    fd_set refset;
private:
};
#endif //DLP_NETWORK_CSELECT_H_
