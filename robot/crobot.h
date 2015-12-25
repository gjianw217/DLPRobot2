#ifndef DLP_ROBOT_CROBOT_H_
#define DLP_ROBOT_CROBOT_H_

#include "../dlp/dlp.h"
#include <map>
class CRobot
{
public:
	explicit CRobot(PCDataMapping datamapping);
	~CRobot();

	PIEncoder GetCoder( DLPRole &role);
	PIMotor   GetMotor( DLPRole &role);
	PCProximitySwitch GetSwitch(DLPRole &role);
    void Init();
    void CreateParts();
protected:

private:
	std::map<DLPRole,PIMotor> m_motors;
	std::map<DLPRole,PIEncoder> m_coders;
	std::map<DLPRole,PCProximitySwitch> m_switchs;
	PIParts m_ppan;
	PIParts m_ptilt;
	PIParts m_pfocus;
	PIParts m_pzoom;

	PCDataMapping  m_pdatamapping;
};


#endif // DLP_ROBOT_CROBOT_H_
