/*
* @file   cpru.h
* @brief  Encapsulation Beaglebone PRU (Programable realtime Unit) module interface
* @author GuoJianwei & gjianw217@163.com
*/

#ifndef DLP_DRIVERS_CPRU_H_
#define DLP_DRIVERS_CPRU_H_

#include <string>
#include "../dlp/dlp.h"
#include "prussdrv/prussdrv.h"
#include "prussdrv/pruss_intc_mapping.h"

class CPRU
{
public:
	explicit CPRU(const std::string &name="pru0");
	virtual ~CPRU();
    virtual void Init();
    virtual void Exit();
	virtual void Run(const uint32_t *pwm);
private:
	std::string m_name;
#ifndef DLP_WINDOW
	tpruss_intc_initdata m_initdata0;
	tpruss_intc_initdata m_initdata1;
#endif
};

#endif //DLP_DRIVERS_CPRU_H_
