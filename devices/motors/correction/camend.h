#ifndef DLP_DEVICES_MOTORS_CORRECTION_CAMEND_H_
#define DLP_DEVICES_MOTORS_CORRECTION_CAMEND_H_
#include "../../../dlp/dlp.h"
class CAmend
{
public:
    CAmend();
    ~CAmend();

    /**/
    int IsAmend();
	int IsControl(void);
	int IsDriver(void );

	/**/

private:
    PCControlMotor m_pconnmotor;
    PCAmendMotor   m_pamendmotor;
    PCDriverMotor  m_pdrivermotor;
};
#endif // DLP_DEVICES_MOTORS_CORRECTION_CAMEND_H_
