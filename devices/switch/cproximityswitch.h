#ifndef DLP_DEVICES_SWITCH_PROXIMITYSWITCH_H_
#define DLP_DEVICES_SWITCH_PROXIMITYSWITCH_H_

#include "../../dlp/dlp.h"

class CProximitySwitch
{
public:
	CProximitySwitch();
	~CProximitySwitch();
	void Config(const uint16_t &pin);
	bool IsProximity();
private:
    PCGPIO m_pgpio;

};
#endif // DLP_DEVICES_SWITCH_PROXIMITYSWITCH_H_


