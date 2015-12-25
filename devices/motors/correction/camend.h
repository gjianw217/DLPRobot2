#ifndef DLP_UTILS_CAMEND_H_
#define DlP_UTILS_CAMEND_H_
#include "../../../dlp/dlpdevices.h"

class CAmend
{
public:
    CAmend();
    ~CAmend();
    void ConfigAttr(AmendAttr &attr);
    void Ready(const float &coder_angle,const long &timing_time);
    long GetAmendTime(const float &cur_coder_angle);
    void Reset(void);
private:
    float m_last_coder_angle;//startup task 's coder angle
    long m_last_timing_time;//task timer time
    long m_amendment_time_internal;//amend timer time
    AmendAttr m_attr;
};

#endif //DlP_UTILS_CAMEND_H_
