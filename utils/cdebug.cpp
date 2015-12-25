#include "cdebug.h"
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

//dlp_log(DLP_LOG_DEBUG,"");
void dlp_log(const int &severity, const char *msg)
{
#ifdef DLP_DEBUG
	const char *severity_str;
	switch (severity)
	{
	case DLP_LOG_DEBUG:
		severity_str = "debug";
		break;
	case DLP_LOG_MSG:
		severity_str = "msg";
		break;
	case DLP_LOG_WARN:
		severity_str = "warn";
		break;
	case DLP_LOG_ERR:
		severity_str = "err";
		break;
	default:
		severity_str = "???";
		break;
	}
    fprintf(stderr, "[%s] %s\n", severity_str, msg);

#endif // DlP_DEBUG
}

void dlp_log_value(const int &severity ,const char *msg,const int &value)
{
#ifdef DLP_DEBUG
	const char *severity_str;
	switch (severity)
	{
	case DLP_LOG_DEBUG:
		severity_str = "debug";
		break;
	case DLP_LOG_MSG:
		severity_str = "msg";
		break;
	case DLP_LOG_WARN:
		severity_str = "warn";
		break;
	case DLP_LOG_ERR:
		severity_str = "err";
		break;
	case DLP_LOG_INFOS:
		severity_str = " ";
	default:
		severity_str = "???";
		break;
	}
#ifdef WIN32
	printf("[%s",severity_str);
	printf("] %s",msg);
	printf(" : %x\n",value);
#else
	PDEBUG("[%s] %s : %x\n",severity_str, msg,value);
#endif // WIN32


#endif // DlP_DEBUG
}

void dlp_logs(const char *msg,const char *value,const bool &newline)
{
#ifdef DLP_DEBUG
	if(newline)
		fprintf(stdout,"%s:%s\n", msg, value);
	else
		fprintf(stdout,"%s:%s,", msg, value);
#endif // DLP_DEBUG
}

#ifdef __cplusplus
}
#endif
