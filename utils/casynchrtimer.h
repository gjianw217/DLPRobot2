#ifndef DLP_APPLICATION_CASYNCHRTIMER_H_
#define DLP_APPLICATION_CASYNCHRTIMER_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

typedef boost::function< void () > TimerTask;
typedef boost::chrono::duration<long long, boost::milli> milliseconds;

class CAsyncHRTimer
{
public:
    CAsyncHRTimer(const int &time_interval);
    ~CAsyncHRTimer();

    void OnTimer();
    void SetTimer(TimerTask task);
    void Run();
    void Stop();
private:
    /*以下顺序很重要(与构造函数对应），不然会导致编译错误*/
    int m_time;
    boost::asio::io_service m_ioService;
    boost::asio::io_service::work m_work;
    boost::asio::high_resolution_timer m_timer;
    //boost::thread m_thread;
    TimerTask m_task;

};

#endif // DLP_APPLICATION_CASYNCHRTIMER_H_
