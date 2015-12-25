/**
* @file       CAsyncTimer成员函数
* @author     GuoJianwei
* @email      gjianw217@163.com
*/
#include"casynctimer.h"

void CAsyncTimer::SetTimer(TimerTask task)
{
    m_task=task;
    m_timer.async_wait(boost::bind(&CAsyncTimer::OnTimer,this,boost::asio::placeholders::error));
}
void CAsyncTimer::OnTimer(const boost::system::error_code &)
{
    if(!m_stop)
    {
		 m_task();

		//m_timer.expires_at(m_timer.expires_at()+boost::posix_time::millisec(m_time));
		//m_timer.expires_at(m_timer.expires_at()+boost::posix_time::seconds(m_time));
		m_timer.expires_from_now(boost::posix_time::millisec(m_time));
        m_timer.async_wait(boost::bind(&CAsyncTimer::OnTimer,this,boost::asio::placeholders::error));
    }
}

void CAsyncTimer::Run()
{
   
    boost::system::error_code errorCode; //运行队列里的任务
    m_io.run(errorCode);
}
void CAsyncTimer::Stop()
{
    m_stop=1;
    m_timer.cancel();
}
