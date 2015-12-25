
#include "cdirection.h"
#include "calgorithm.h"
#include "imotor.h"

IMotor::IMotor()
{
	m_pdirection=PCDirection(new CDirection());
	m_palgorithm=PCAlgorithm(new CAlgorithm());
}

IMotor::~IMotor()
{

}

void IMotor::SetCoder(PIEncoder pcoder)
{
	m_pcoder=pcoder;
}

int IMotor::SetAttr(const DLPMotorAttr &attr)
{
    dlp_log(DLP_LOG_DEBUG,"IMotor::SetAttr(const DLPMotorAttr &attr)");

	m_attr=attr;
	m_pdirection->Config(m_attr.dlp_dir.pin,m_attr.dlp_dir.value);
	m_palgorithm->SetAttr(attr.dlp_algorithm);

	m_pcurve=m_palgorithm->GetCurve(m_attr.dlp_curve);
	m_protation=m_palgorithm->GetRotation(m_attr.dlp_rotation);
	return 0;
}

void IMotor::ModifyCurve(const DLPMotorCurveType &curve)
{
	m_attr.dlp_curve=curve;
	m_pcurve=m_palgorithm->GetCurve(m_attr.dlp_curve);
}

void IMotor::ModifyRotation(const DLPMotorRotationType &roation)
{
	m_attr.dlp_rotation=roation;
	m_protation=m_palgorithm->GetRotation(m_attr.dlp_rotation);
}
