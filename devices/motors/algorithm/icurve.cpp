#include "icurve.h"

ICurve::ICurve()
{

}

ICurve::~ICurve()
{

}

void ICurve::SetAttr(const DLPAlgorithmAttr &attr)
{
	m_attr=attr;
}

void ICurve::SetMaxSpeed(const uint16_t &max_speed)
{
    m_attr.max_speed=max_speed;

}

uint16_t ICurve::GetMaxSpeed(void )
{
    return m_attr.max_speed;
}
