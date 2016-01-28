/*
* @file   头文件
* @brief  封装用于控制系统的类，该类控制云台各部分协调工作
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
    //Setting Default Attribute
    void SetAmendAttr(const DLPMotorPulse &type,const DLPMotorAttr &mattr,const DLPEncoderAttr &eattr);
    //Command Pulses Update
    void SetDevCurvePulse(const DLPMotorPulse &type,const uint8_t &len,const uint32_t *src);
    void SetDevCoderAngle(const DLPMotorPulse &type,const float &coder_angle);
    //Judge the Amendment
    int IsAmend(const DLPMotorPulse &type,const float &coder_angle);
    uint32_t Frames2Pulses(const DLPMotorPulse &type);
    uint32_t Angle2Pulses(const DLPMotorPulse &type,const float &coder_angle);
    int32_t GetAmendError(const uint32_t &theory_pulses,const uint32_t &real_pulses);
    //Amend the Angle
    void ComputeAmendTime(const DLPMotorPulse &type,const int16_t &amend_error);//not implement
    void ComputeAmendAngle(const DLPMotorPulse &type,const int16_t &amend_error);
    void GetAmendParameter(const DLPMotorPulse &type,uint16_t *pcoder_data);

private:
//    uint32_t Frames2Pulses(const DLPMotorPulse &type);
//    uint32_t Angle2Pulses(const DLPMotorPulse &type,const float &coder_angle);
//    int32_t GetAmendError(const uint32_t &theory_pulses,const uint32_t &real_pulses);
//    void ComputeAmendTime(const DLPMotorPulse &type,const int16_t &amend_error);
//    void ComputeAmendAngle(const DLPMotorPulse &type,const int16_t &amend_error);

    DLPAmendAttr m_amend_attr[4];//Set Attribute by calling the SetAmendAttr
    float m_init_time[4];
    float m_init_angle[4];
    uint32_t m_dev_pulses[4][DLP_PULSE_MAX_FRAME];
    uint32_t m_frame_index[4];
    uint32_t m_frame_counter[4];


    uint16_t m_amend_time[4][2];
    uint16_t m_amend_angle[4][2];



};


#endif // DLP_ROBOT_CAMEND_PULSE_H_
