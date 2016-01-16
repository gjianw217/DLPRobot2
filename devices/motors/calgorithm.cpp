#include "calgorithm.h"
#include "algorithm/clcurve.h"
#include "algorithm/ctcurve.h"
#include "algorithm/cscurve.h"
#include "algorithm/cbeziercurve.h"

#include "algorithm/crotation360.h"
#include "algorithm/crotation720.h"
#include "algorithm/crotationany.h"
#include "algorithm/ctestcurve.h"
#include "algorithm/ctestrotation.h"

CAlgorithm::CAlgorithm()
{
	Init();

}
CAlgorithm::~CAlgorithm()
{

}

void CAlgorithm::Init()
{
    m_rotations[DLP_MOTOR_ROTATION_TEST]=PCTestRotation(new CTestRotation());
	m_rotations[DLP_MOTOR_ROTATION_360]=PCRotation360(new CRotation360());
	m_rotations[DLP_MOTOR_ROTATION_720]=PCRotation720(new CRotation720());
	m_rotations[DLP_MOTOR_ROTATION_ANY]=PCRotationAny(new CRotationAny());
	//
	m_curves[DLP_MOTOR_CURVE_TEST]=PCTestCurve(new CTestCurve());
	m_curves[DLP_MOTOR_CURVE_L]=PCLCurve(new CLCurve());
	m_curves[DLP_MOTOR_CURVE_T]=PCTCurve(new CTCurve());
	m_curves[DLP_MOTOR_CURVE_S]=PCSCurve(new CSCurve());
	m_curves[DLP_MOTOR_CURVE_B]=PCBezierCurve(new CBezierCurve());
}

void CAlgorithm::SetAttr(const DLPAlgorithmAttr &attr)
{
	m_attr=attr;
	m_rotations[DLP_MOTOR_ROTATION_TEST]->SetAttr(m_attr);
	m_rotations[DLP_MOTOR_ROTATION_360]->SetAttr(m_attr);
	m_rotations[DLP_MOTOR_ROTATION_720]->SetAttr(m_attr);
	m_rotations[DLP_MOTOR_ROTATION_ANY]->SetAttr(m_attr);

	m_curves[DLP_MOTOR_CURVE_TEST]->SetAttr(m_attr);
	m_curves[DLP_MOTOR_CURVE_L]->SetAttr(m_attr);
	m_curves[DLP_MOTOR_CURVE_T]->SetAttr(m_attr);
	m_curves[DLP_MOTOR_CURVE_S]->SetAttr(m_attr);

}
PIRotation CAlgorithm::GetRotation(const DLPMotorRotationType &rotation)
{
	return m_rotations[rotation];
}

PICurve CAlgorithm::GetCurve(const DLPMotorCurveType &curve)
{
	return m_curves[curve];
}
