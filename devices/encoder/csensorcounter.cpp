/**
* @file       CSensorCounterh成员函数
* @author     Chengliang &&346166228@qq.com
* @date       2014.12.06
*/

#include <assert.h>
#include <stdlib.h>     /* abs */
#include "csensorcounter.h"
CSensorCounter::CSensorCounter()
{
	m_nMaxValue = 0;
	m_nZeroValue = -1;
	m_nValue = -1;
	m_curValue = -1;
	m_totalValue = 0;
	m_nLoop = 0;
	m_fAngle = 0;
}


CSensorCounter::~CSensorCounter()
{
}

void CSensorCounter::SetMaxCounter(int nMax)
{
	assert(nMax>0);
	m_nMaxValue = nMax;
	m_nZeroValue = -1;
	m_nValue = -1;
	m_curValue = -1;
	m_totalValue = 0;
	m_nLoop = 0;
	m_fAngle = 0;
}

int CSensorCounter::GetMaxCounter()
{
	return m_nMaxValue;
}

void CSensorCounter::ResetZero()
{
	assert(m_nValue>=0);
	m_nZeroValue = m_nValue;

	m_curValue = 0;
	m_totalValue = 0;
	m_nLoop = 0;
	m_fAngle = 0;
}

void CSensorCounter::SetCounter(int nValue)
{
	assert(m_nMaxValue>0 );
	assert(nValue<=m_nMaxValue);
	assert(nValue>=0);

	if(m_nZeroValue >= 0)
	{
		int curValue = transCoord(nValue);
		if(abs((curValue-m_curValue)) >= m_nMaxValue/2)//转过了相对零点
		{
			if(curValue < m_curValue)//顺时针转动
			{
				m_totalValue += curValue+m_nMaxValue-m_curValue;
				m_nLoop++;
			}
			else//逆时针转动
			{
				m_totalValue -= (m_nMaxValue-curValue) + m_curValue;
				m_nLoop--;
			}
		}
		else
		{
			m_totalValue += curValue-m_curValue;
		}
		m_curValue = curValue;
	}

	m_nValue = nValue;
}

int CSensorCounter::GetCounter()
{
	return m_nValue;
}

float CSensorCounter::GetAngle()
{
	m_fAngle = m_totalValue*360.0F/m_nMaxValue;
	return m_fAngle;
}

int CSensorCounter::GetLoop()
{
	return m_nLoop;
}