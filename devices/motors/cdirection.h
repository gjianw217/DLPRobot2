#ifndef DLP_DEVICES_MOTORS_CDIRECTION_H_
#define DLP_DEVICES_MOTORS_CDIRECTION_H_

#include <stdint.h>
#include <string>
#include "../../dlp/dlp.h"
#include "../../drivers/cgpio.h"
class CDirection
{
public:
	CDirection();
	~CDirection();
	void Config(const uint16_t &pin,const uint16_t &direction);
	void SetDirValue(const uint16_t &value);
	uint16_t GetDirValue();
private:
	uint16_t m_value;
	PCGPIO m_pgpio;

};

#endif // DLP_DEVICES_MOTORS_CDIRECTION_H_


