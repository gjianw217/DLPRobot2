#ifndef DLP_DEVICES_MOTORS_CALGORITHM_H_
#define DLP_DEVICES_MOTORS_CALGORITHM_H_
#include <map>
#include "../../dlp/dlp.h"

class CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();

	void SetAttr(const DLPAlgorithmAttr &attr);
	PIRotation GetRotation(const DLPMotorRotationType &rotation);
	PICurve GetCurve(const DLPMotorCurveType &curve);
protected:
	void Init();
private:
	std::map<DLPMotorRotationType,PIRotation> m_rotations;
	std::map<DLPMotorCurveType,PICurve> m_curves;
	DLPAlgorithmAttr m_attr;

};
#endif //DLP_DEVICES_MOTORS_CALGORITHM_H_
