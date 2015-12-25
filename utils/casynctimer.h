#ifndef DLP_APPLICATION_CASYNCTIMER_H_
#define DLP_APPLICATION_CASYNCTIMER_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>

typedef boost::function< void(void ) > TimerTask;

class CAsyncTimer
{
public:
    //CAsyncTimer(boost::asio::io_service &io,const int &time_interval)
    CAsyncTimer(const int &time_interval)
        :m_stop(0),m_time(time_interval),m_work(m_io),m_timer(m_io,boost::posix_time::millisec(time_interval)){};
    ~CAsyncTimer(){;}

    void SetTimer(TimerTask task);
    void Run();
    void Stop();
private:
    void OnTimer(const boost::system::error_code &);
private:
    int m_stop;
    int m_time;
    boost::asio::io_service m_io;
    boost::asio::io_service::work m_work;
    boost::asio::deadline_timer m_timer;
    TimerTask m_task;

};
#endif //DLP_APPLICATION_CASYNCTIMER_H_
