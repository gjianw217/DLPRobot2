#ifndef DLP_UTILS_CTASKTHREAD_H_
#define DLP_UTILS_CTASKTHREAD_H_
/**
* @file       ͷ�ļ�
* @brief      ��װboost����̣߳�����֧��ϵͳ�Ķ��߳�����
* @author     Mr Wen
* @date       2014.11.6
*/
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

typedef boost::function< void () > ThreadFunc;

class CTaskThread
{
public:
	CTaskThread();
	~CTaskThread(void);

	void SetTask(ThreadFunc f);

	void SigTask();
	void Close();
protected:
	void doTask();
	bool          m_bExit;
	boost::mutex  m_mutex;
	boost::thread m_thread;
	boost::condition_variable m_cond;
	ThreadFunc    m_task;
private:
    int m_num;
};


class CSuspendThread
{
public:
	CSuspendThread();
	~CSuspendThread(void);

    void Wait();
    void Wake();
protected:
	boost::mutex  m_mutex;
	boost::condition_variable m_cond;
};
#endif //DLP_UTILS_CTASKTHREAD_H_
