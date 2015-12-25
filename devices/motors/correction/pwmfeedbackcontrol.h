#ifndef DLP_UTILS_PWM_FEEDBACK_CONTROL_H_
#define DLP_UTILS_PWM_FEEDBACK_CONTROL_H_

#include "../../../dlp/dlp.h"//dlpdevices

#include  <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>

#define TIMER_MAX_TASK_SIZE 4
//typedef  void (*StopRunning)(void); //函数指针
typedef boost::function< void () > StopRunning;
typedef struct
{
    bool runing_mark;
    uint32_t running_time;
    StopRunning stop; //函数指针
}TimerTaskPara;


typedef enum
{
Pwm_Pan_Device=0,
Pwm_Tilt_Device=1,
Pwm_Focus_Device=2,
Pwm_Zoom_Device=3
}PWMDevice;

class CPWMFeedbackControl
{
public:
   CPWMFeedbackControl();
   ~CPWMFeedbackControl();
   void Run(const long &task_internal_ms);
   void Update(const PWMDevice &dev,const uint64_t &delay_ms,StopRunning stop);
  // void Update(const PWMDevice &dev,const uint64_t &delay);
   void SetAttr(AmendAttr attr);
   void SetCoder(PIEncoder coder);
private:
    void pwmtask(const boost::system::error_code& e,const long &task_internal_ms);
    void Check(const long &task_internal_ms);
private:
    TimerTaskPara m_timer_task[TIMER_MAX_TASK_SIZE];
    boost::asio::io_service m_io;
    boost::asio::deadline_timer m_task_timer;

    PIEncoder m_pcoder;
    PCAmend   m_pamend;
};

#endif //DLP_UTILS_PWM_FEEDBACK_CONTROL_H_
