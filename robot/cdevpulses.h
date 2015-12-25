#ifndef DLP_ROBOT_CDEVPULSE_H_
#define DLP_ROBOT_CDEVPULSE_H_

#include "../dlp/dlp.h"
#include <map>

#define DLP_MAX_PULSES 100
/*Save all the equipment of pulse*/
class CDevPulses
{
public:
    CDevPulses();
	~CDevPulses();

	int ReadDevPulse(const DLPMotorPulse &type,const uint8_t &pos);
	void     WriteDevPulse(const DLPMotorPulse &type,const uint8_t &pos,const uint32_t &value);
	void     ReadDevPulsesCurve(const DLPMotorPulse &type,const uint8_t &len,uint32_t *des);
	void     WriteDevPulsesCurve(const DLPMotorPulse &type,const uint8_t &len,const uint32_t *src);

    void  ReadPulseGroup(const uint8_t &pos,uint32_t *des);

protected:
    int check_para(const DLPMotorPulse &type,const uint8_t pos_or_len=0);
private:
    //std::map<uint8_t,uint32_t> m_motor_counter;
//    uint32_t m_pan_pulses[DLP_MAX_PULSES];
//    uint32_t m_tilt_pulses[DLP_MAX_PULSES];
//    uint32_t m_focus_pulses[DLP_MAX_PULSES];
//    uint32_t m_zoom_pulses[DLP_MAX_PULSES];
    uint32_t m_dev_pulses[4][DLP_MAX_PULSES];
    uint16_t m_counter;

};


#endif // DLP_ROBOT_CDEVPULSE_H_
