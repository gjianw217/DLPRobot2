#include "pwmfeedbackcontrol.h"
#include "camend.h"
#include "../../encoder/iencoder.h"
#include "../../encoder/crs485coder.h"
#include <iostream>

CPWMFeedbackControl::CPWMFeedbackControl():m_task_timer(m_io)
{
    m_pamend=PCAmend(new CAmend());
    m_pcoder.reset();

    for(int i=0;i<TIMER_MAX_TASK_SIZE;i++)
    {
        m_timer_task[i].runing_mark=false;
        m_timer_task[i].running_time=0;
    }


}
CPWMFeedbackControl::~CPWMFeedbackControl()
{

}
void CPWMFeedbackControl::Run(const long &task_internal_ms)
{
     //m_task_timer.expires_from_now(boost::posix_time::microseconds(task_internal_ms));
    m_task_timer.expires_from_now(boost::posix_time::milliseconds(task_internal_ms));
     // m_task_timer.expires_at(m_task_timer.expires_at()+ boost::posix_time::milliseconds(task_internal_ms));
     m_task_timer.async_wait(boost::bind(&CPWMFeedbackControl::pwmtask,this,boost::asio::placeholders::error,task_internal_ms));
     m_io.run();
}

void CPWMFeedbackControl::pwmtask(const boost::system::error_code& e,const long &task_internal_ms)
{
    static int timers=0;
    std::cout<<++timers<<std::endl;

    if(!e)//timeout
    {
        std::cout<< "amend timer is timeout"<<std::endl;
        //std::cout<<"CPWMFeedbackControl::Check :"<<m_pcoder->GetCoderAngle()<<std::endl;
        printf("CPWMFeedbackControl::Check : %f\n",m_pcoder->GetCoderAngle());
//       m_task_timer.expires_at(m_task_timer.expires_at()+ boost::posix_time::seconds(task_internal_ms));
       m_task_timer.expires_at(m_task_timer.expires_at()+ boost::posix_time::milliseconds(task_internal_ms));
       m_task_timer.async_wait(boost::bind(&CPWMFeedbackControl::pwmtask,this,boost::asio::placeholders::error,task_internal_ms));

        Check(task_internal_ms);

    }
    else if(e== boost::asio::error::operation_aborted) //cancel
    {
        std::cout<<"task timer is canceled"<<std::endl;
    }
    else
    {
        std::cout<<"task timer other"<<std::endl;

    }
}

void CPWMFeedbackControl::Check(const long &task_internal_ms)
{
    static float curcoderangle=0.0;
    static long timelength=0;
    std::cout<<"CPWMFeedbackControl::Check"<<std::endl;
    for(int i=0;i<TIMER_MAX_TASK_SIZE;i++)
    {
        if(m_timer_task[i].runing_mark)
        {
            //to amend the pwm running time
            if(m_pcoder.use_count()>0)
            {
                curcoderangle=m_pcoder->GetCoderAngle();
            }
            timelength=m_pamend->GetAmendTime(curcoderangle);
            m_timer_task[i].running_time=timelength;
            std::cout<<"CPWMFeedbackControl::Check :"<<timelength<<std::endl;

        }
        if((m_timer_task[i].runing_mark)&&(!m_timer_task[i].running_time<task_internal_ms*1000))//judge stop or not
        {

          //  m_timer_task[i].stop();                        //to stop the pwm running
            m_timer_task[i].runing_mark=false;
        }

    }
}

void CPWMFeedbackControl::Update(const PWMDevice &dev,const uint64_t &delay_ms,StopRunning stop)
//void CPWMFeedbackControl::Update(const PWMDevice &dev,const uint64_t &delay)
{
    m_timer_task[dev].stop=stop;
    if(m_timer_task[dev].runing_mark==true) //if running currently,and to stop
    {
        m_timer_task[dev].stop();
    }
    m_timer_task[dev].runing_mark=true;     //setting running parameter
    m_timer_task[dev].running_time=delay_ms;
    if(m_pcoder.use_count()>0)
    {

        m_pamend->Ready(m_pcoder->GetCoderAngle(),delay_ms);
    }
}

void CPWMFeedbackControl::SetAttr(AmendAttr attr)
{
    m_pamend->ConfigAttr(attr);
}

void CPWMFeedbackControl::SetCoder(PIEncoder coder)
{
    m_pcoder=coder;
}

