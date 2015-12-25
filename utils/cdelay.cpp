#include "cdelay.h"
#include "../dlp/dlpplatform.h"
void delays(const uint32_t s)
{
#ifdef DLP_WINDOW
	Sleep(1000*s);
#else
	sleep(s);
#endif // DLP_WINDOW

}
void delayms(const uint32_t ms)
{
#ifdef DLP_WINDOW
	Sleep(ms);
#else
	usleep(1000*ms);
#endif // DLP_WINDOW
}
void delayus(const uint32_t us)
{
#ifndef DLP_WINDOW
	usleep(us);
#endif // DLP_WINDOW

}
