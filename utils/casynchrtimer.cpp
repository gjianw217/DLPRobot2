/**
* @file       CAsyncHRTimer成员函数
* @author     GuoJianwei & gjianw217@163.com
* @date       2014.11.17
*/
#include "casynchrtimer.h"


CAsyncHRTimer::CAsyncHRTimer(const int &time_interval)
      :m_time(time_interval),m_work(m_ioService),m_timer(m_ioService)
        //,m_thread(boost::bind(&CAsyncTimer::Run,this))
{

}
CAsyncHRTimer::~CAsyncHRTimer()
{
;
}

void CAsyncHRTimer::OnTimer()
{
#ifndef DLP_WINDOW
    m_task();
    m_timer.expires_from_now(milliseconds(m_time));
    m_timer.async_wait(boost::bind(&CAsyncHRTimer::OnTimer,this));
#endif //DLP_WINDOW
}

void CAsyncHRTimer::SetTimer(TimerTask task)
{
    m_task=task;
    m_timer.async_wait(boost::bind(&CAsyncHRTimer::OnTimer,this));
}

void CAsyncHRTimer::Run()
{
    boost::system::error_code errorCode;//运行队列里的任务
    m_ioService.run(errorCode);
}

void CAsyncHRTimer::Stop()
{
    m_ioService.stop();
    //m_thread.join();
}