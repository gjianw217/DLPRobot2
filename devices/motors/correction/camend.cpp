#include "camend.h"
#include "camendmotor.h"
#include "ccontrolmotor.h"
#include "cdrivermotor.h"

#include <cmath>
#include <iostream>

CAmend::CAmend()
{
    m_pamendmotor = PCAmendMotor(new CAmendMotor());
    m_pconnmotor  = PCControlMotor(new CControlMotor());
    m_pdrivermotor= PCDriverMotor (new CDriverMotor());

}

CAmend::~CAmend()
{

}


int CAmend::IsAmend()
{

    return 0;
}
int CAmend::IsControl()
{
    return 0;
}
int CAmend::IsDriver(void )
{
    return 0;
}


