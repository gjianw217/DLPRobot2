#ifndef DLP_DEVICES_SENSORS_SENSORCOUNTER_H_
#define DLP_DEVICES_SENSORS_SENSORCOUNTER_H_
//��ʹ���������ڵ���SetCounter�ļ�����ܴ���1/2Ȧ��
class CSensorCounter
{
public:
	CSensorCounter();
	~CSensorCounter();
	//�趨��Ȧ���ֵ
	void SetMaxCounter(int nMax);//���ô˺�����������������㡣
	int GetMaxCounter();

	//��ǰ������ֵ��Ϊ0λ
	void ResetZero();//�ڵ��ô˺���ǰ�����ٵ���һ��SetCounter�����ú�ǶȺ�Ȧ�������㡣

	//�趨������ֵ
	void SetCounter(int nValue);//nValue����С�ڵ���nMax�����������ֹ��
	//ÿ�δ��봥������ֵ��ɣ��������ֵ�����ӣ�����Ϊ��������Ϊ����
	int  GetCounter();

	//�õ��������Ƕ� ��λ��
	float GetAngle();//�õ�ת���ĽǶȣ�˳ʱ��Ϊ������ʱ��Ϊ����

	//�õ�Ȧ��
	int  GetLoop();//ת����Ȧ����Ϊ��ֵ��
protected:
	int		m_nMaxValue; //���������ֵ
	int		m_nZeroValue;//0 �������ֵ
	int		m_nValue;    //��ǰ������ֵ
	int		m_curValue;	//�����������ԽǶ�
	int		m_totalValue;//�ܵ�ֵ
	int		m_nLoop;     //Ȧ��,��Ϊ˳ʱ�룬��Ϊ��ʱ�롣
	float	m_fAngle;    //��ǰ�Ƕ�
private:
	int transCoord(int nValue)
	{
		return nValue>=m_nZeroValue ? (nValue-m_nZeroValue) : (nValue+m_nMaxValue-m_nZeroValue);
	}
};


#endif // DLP_DEVICES_SENSORS_SENSORCOUNTER_H_
