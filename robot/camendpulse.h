/*
* @file   ͷ�ļ�
* @brief  ��װ���ڿ���ϵͳ���࣬���������̨������Э������
* @author GuoJianwei & gjianw217@163.com
* @see
*/

#ifndef DLP_ROBOT_CAMEND_PULSE_H_
#define DLP_ROBOT_CAMEND_PULSE_H_

#include "../dlp/dlp.h"

class CAmendPulse
{
 public:
    CAmendPulse();
    ~CAmendPulse();
    int IsAmend(const DLPMotorPulse &type,const float &coder_angle);
    void GetAmendParameter(const DLPMotorPulse &type,uint16_t *pcoder_data);
    void SetAmendParameter(const DLPMotorPulse &type,uint16_t *time_angle);
    void SetAmendAttr(const DLPMotorPulse &type,const DLPMotorAttr &mattr,const DLPEncoderAttr &eattr);
    void GetAmendTime(const DLPMotorPulse &type,const int16_t &amend_error);
    void GetAmendAngle(const DLPMotorPulse &type,const int16_t &amend_error);

private:
    uint32_t Frames2Pulses(const DLPMotorPulse &type);

    uint32_t Angle2Pulses(const DLPMotorPulse &type,const float &coder_angle);
    int32_t GetAmendError(const uint32_t &theory_pulses,const uint32_t &real_pulses);
    uint32_t m_counter[4];
    DLPAmendAttr m_amend_attr[4];
    uint16_t m_amend_time[4][2];
    float m_init_time[4];
    uint16_t m_amend_angle[4][2];
    float m_init_angle[4];
    uint32_t m_dev_pulses[4][DLP_PULSE_MAX];

};


#endif // DLP_ROBOT_CAMEND_PULSE_H_