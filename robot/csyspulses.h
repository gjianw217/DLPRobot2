#ifndef DLP_ROBOT_CSYSPULSES_H_
#define DLP_ROBOT_CSYSPULSES_H_

#include "../dlp/dlp.h"
#include <map>


class CSysPulses
{
public:
    CSysPulses();
	~CSysPulses();
	uint32_t ReadPulse(const uint8_t &pos);
	void     WritePulse(const uint8_t &pos,const uint32_t &value);
	void     ReadPulseGroup(uint32_t *des,const uint8_t &len);
    void     WritePulseGroup(const uint32_t *src,const uint8_t &len=8);
    void RunPulseGroups();

protected:
    PCPRU m_ppru;
    PCPWM m_ppwm;
private:
    uint32_t m_pulses[8];
    //std::map<uint8_t,uint32_t> m_motor_counter;

};


#endif // DLP_ROBOT_CSYSPULSES_H_
