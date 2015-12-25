#ifndef DLP_DEVICES_SENSORS_SENSORCOUNTER_H_
#define DLP_DEVICES_SENSORS_SENSORCOUNTER_H_
//类使用条件，在调用SetCounter的间隔不能大于1/2圈。
class CSensorCounter
{
public:
	CSensorCounter();
	~CSensorCounter();
	//设定单圈最大值
	void SetMaxCounter(int nMax);//调用此函数后，需重新设置零点。
	int GetMaxCounter();

	//当前传感器值作为0位
	void ResetZero();//在调用此函数前，至少调用一次SetCounter。调用后角度和圈数都归零。

	//设定传感器值
	void SetCounter(int nValue);//nValue必须小于等于nMax，否则程序终止。
	//每次传入触感器的值便可，若传入的值在增加，则方向为正，否则为负。
	int  GetCounter();

	//得到传感器角度 单位度
	float GetAngle();//得到转动的角度，顺时针为正，逆时针为负。

	//得到圈数
	int  GetLoop();//转动的圈数，为正值。
protected:
	int		m_nMaxValue; //计数器最大值
	int		m_nZeroValue;//0 点计算器值
	int		m_nValue;    //当前计数器值
	int		m_curValue;	//相对于零点的相对角度
	int		m_totalValue;//总的值
	int		m_nLoop;     //圈数,正为顺时针，负为逆时针。
	float	m_fAngle;    //当前角度
private:
	int transCoord(int nValue)
	{
		return nValue>=m_nZeroValue ? (nValue-m_nZeroValue) : (nValue+m_nMaxValue-m_nZeroValue);
	}
};


#endif // DLP_DEVICES_SENSORS_SENSORCOUNTER_H_
