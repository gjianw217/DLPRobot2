/**
* @file       CTaskThread成员函数
* @author     WenGong && 2211739@qq.com
* @date       2014.11.06
*/
#include "ctaskthread.h"
CTaskThread::CTaskThread(void):m_bExit(false),m_thread(boost::bind(&CTaskThread::doTask,this))
{
}

CTaskThread::~CTaskThread(void)
{
	Close();
}

void CTaskThread::SetTask(ThreadFunc f)
{
	boost::mutex::scoped_lock lock(m_mutex);
	m_task = f;
}

void CTaskThread::doTask()
{
	while(!m_bExit)
	{
		{
			boost::unique_lock<boost::mutex>lock(m_mutex);
 			this->m_cond.wait(lock);
		}

		boost::mutex::scoped_lock lock(m_mutex);
    	if(!m_bExit && !m_task.empty() )
			m_task();
	}
}

void CTaskThread::SigTask()
{

	//boost::unique_lock<boost::mutex>lock(m_mutex);
	//m_cond.notify_all();
	this->m_cond.notify_one();
}

void CTaskThread::Close()
{
	{
		m_bExit=true;
		boost::mutex::scoped_lock lock(m_mutex);
		m_cond.notify_all();
	}
	m_thread.join();
}

//------------------------------------------------------------------------
CSuspendThread::CSuspendThread()
{
}

CSuspendThread::~CSuspendThread(void)
{
    Wake();
}

void CSuspendThread::Wait()
{
	boost::unique_lock<boost::mutex>lock(m_mutex);
 	m_cond.wait(lock);
}

void CSuspendThread::Wake()
{
    m_cond.notify_one();
}



