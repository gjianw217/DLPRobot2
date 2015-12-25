/*
* @file   头文件
* @brief  自定义Debug函数
* @author GuoJianwei & gjianw217@163.com
*/
#ifndef DLP_UTILS_CDEBUG_H_
#define DLP_UTILS_CDEBUG_H_
/************************************************************************/
/* 返回值                                                               */
/************************************************************************/


/************************************************************************/
/*     调试部分                                                        */
/************************************************************************/
enum{
	DLP_LOG_DEBUG,
	DLP_LOG_MSG,
	DLP_LOG_WARN,
	DLP_LOG_ERR,
	DLP_LOG_INFOS,

};
#ifdef __cplusplus
extern "C" {
#endif
/*向终端输出调试信息，默认每调用一次，函数自动换行*/
void dlp_log(const int &severity, const char *msg);
/*向终端输出给定变量的信息*/
void dlp_log_value(const int &severity ,const char *msg,const int &value);

/*向终端一次输出多个信息*/
void dlp_logs(const char *msg,const char *value,const bool &newline=false);

#undef PDEBUG            /* undef it, just in case */
#ifndef WIN32
//#define PDEBUG(fmt, args...)    printf("cmmb_inno: line %d - %s():"fmt, __LINE__, __FUNCTION__, ##args)
#define PDEBUG(fmt, args...)    fprintf(stderr, fmt, ## args)
#endif

#ifdef __cplusplus
}
#endif



/************************************************************************/
/*    错误部分                                                                  */
/************************************************************************/
/* Random number to avoid errno conflicts */
#define BBB_ENOBASE 12345678
/* Protocol exceptions */
enum {
    BBB_ILLEGAL_FUNCTION = 0x01,/*<返回0表示正确运行*/
    BBB_ILLEGAL_DATA_ADDRESS,
    BBB_ILLEGAL_DATA_VALUE,

    BBB_FILE_NOT_OPEN,
    BBB_SOCKET_NOT_CREATE,
    BBB_TARGET_NOT_RESPOND

};

#define EBBBIFUN      (BBB_ENOBASE + BBB_ILLEGAL_FUNCTION)
#define EBBBIADDRESS  (BBB_ENOBASE + BBB_ILLEGAL_DATA_ADDRESS)
#define EBBBIVALUE    (BBB_ENOBASE + BBB_ILLEGAL_DATA_VALUE)
#define EBBBNOPEN     (BBB_ENOBASE + BBB_FILE_NOT_OPEN)
#define EBBBNCREATE   (BBB_ENOBASE + BBB_SOCKET_NOT_CREATE)
#define EBBBNRESPOND  (BBB_ENOBASE + BBB_TARGET_NOT_RESPOND)

#endif // DLP_UTILS_CDEBUG_H_
