#ifndef DLP_DLP_DLPBOOST_H_
#define DLP_DLP_DLPBOOST_H_

#include <boost/smart_ptr.hpp>
class CCAN;
class CCANCoder;
class CSerial;
class CRS485Coder;
class IEncoder;
class CSensorCounter;

class CPRU;
class CPWM;
class IMotor;
//class CCustomPWM;//deprecated,recommend CStepMotorbyPRU
//class CSystemPWM;//deprecated,recommend CStepMotorbyPWM
class CGPIO;
class CDirection;
class CAlgorithm;
//class CStepMotorbyPRU;//recommend
//class CStepMotorbyPWM;//recommend
class CStepMotor ;
class CProximitySwitch;

class IRotation;
class CRotation360;
class CRotation720;
class CRotationAny;
class ICurve;
class CLCurve;
class CTCurve;
class CSCurve;
class CTestCurve;
class CTestRotation;

class IPartsFactory; //deprecated
class CPanParts;     //deprecated
class CTiltParts;   //deprecated
class CFocusParts;   //deprecated
class CZoomParts;//deprecated
class CPTZParts;//deprecated
class CLensParts;//deprecated
class IParts;//deprecated
class CAssembly;//deprecated
class CPanPart;//recommend
class CTiltPart;//recommend
class CFocusPart;//recommend
class CZoomPart;//recommend
class CRobot;//recommend

class CConfig;//recommend


class CDataMapping;
class CModbus;
class CSelect;
class CParse;
class CControl;
class CNetwork;

class ITask;
class CFocusTask;
class CZoomTask;
class CPanTask;
class CTiltTask;
class CSysTask;
class CRefresh;
class CCCD;

class CSystem;
class CSynchro;
class CTaskThread;

class CSynchro2;
class CAmend;
class CAmendPwmMotor;
class CPWMFeedbackControl;

class CSysPulses;
class CDevPulses;
class CManagePulse;
class CAmendPulse;

typedef boost::shared_ptr<CCAN> PCCAN;
typedef boost::shared_ptr<CCANCoder> PCCANCoder;
typedef boost::shared_ptr<CSerial>  PCSerial;
typedef boost::shared_ptr<CRS485Coder>   PCRS485Coder;
typedef boost::shared_ptr<IEncoder> PIEncoder;
typedef boost::shared_ptr<CSensorCounter>  PCSensorCounter;

typedef boost::shared_ptr<CPRU> PCPRU;
typedef boost::shared_ptr<CPWM> PCPWM;
typedef boost::shared_ptr<IMotor>  PIMotor;
//typedef boost::shared_ptr<CCustomPWM>  PCCustomPWM;//deprecated,recommend PCStepMotorbyPRU
//typedef boost::shared_ptr<CSystemPWM>  PCSystemPWM;//deprecated,recommend PCStepMotorbyPWM
//typedef boost::shared_ptr<CStepMotorbyPWM>  PCStepMotorbyPWM;
//typedef boost::shared_ptr<CStepMotorbyPRU>  PCStepMotorbyPRU;

typedef boost::shared_ptr<CStepMotor> PCStepMotor;
typedef boost::shared_ptr<CGPIO>  PCGPIO;
typedef boost::shared_ptr<CDirection>  PCDirection;
typedef boost::shared_ptr<CAlgorithm>  PCAlgorithm;
typedef boost::shared_ptr<IRotation> PIRotation;
typedef boost::shared_ptr<CRotation360> PCRotation360;
typedef boost::shared_ptr<CRotation720>  PCRotation720;
typedef boost::shared_ptr<CRotationAny>  PCRotationAny;
typedef boost::shared_ptr<ICurve>  PICurve;
typedef boost::shared_ptr<CLCurve>  PCLCurve;
typedef boost::shared_ptr<CTCurve>  PCTCurve;
typedef boost::shared_ptr<CSCurve>  PCSCurve;
typedef boost::shared_ptr<CTestCurve> PCTestCurve;
typedef boost::shared_ptr<CTestRotation> PCTestRotation;

typedef boost::shared_ptr<CProximitySwitch> PCProximitySwitch;

typedef boost::shared_ptr<IPartsFactory> PIPartsFactory;//deprecated
typedef boost::shared_ptr<CPanParts> PCPanParts;//deprecated
typedef boost::shared_ptr<CTiltParts>  PCTiltParts;//deprecated
typedef boost::shared_ptr<CFocusParts>  PCFocusParts;//deprecated
typedef boost::shared_ptr<CZoomParts>  PCZoomParts;//deprecated
typedef boost::shared_ptr<CPTZParts>  PCPTZParts;//deprecated
typedef boost::shared_ptr<CLensParts>  PCLensParts;//deprecated
typedef boost::shared_ptr<CAssembly>  PCAssembly;//deprecated
typedef boost::shared_ptr<IParts> PIParts;//recommend
typedef boost::shared_ptr<CPanPart> PCPanPart;//recommend
typedef boost::shared_ptr<CTiltPart>  PCTiltPart;//recommend
typedef boost::shared_ptr<CFocusPart>  PCFocusPart;//recommend
typedef boost::shared_ptr<CZoomPart>  PCZoomPart;//recommend
typedef boost::shared_ptr<CRobot>  PCRobot;//recommend
typedef boost::shared_ptr<CConfig>  PCConfig;

typedef boost::shared_ptr<CDataMapping> PCDataMapping;
typedef boost::shared_ptr<CModbus>  PCModbus;
typedef boost::shared_ptr<CSelect>  PCSelect;
typedef boost::shared_ptr<CParse>  PCParse;
typedef boost::shared_ptr<CControl>  PCControl;
typedef boost::shared_ptr<CNetwork>  PCNetwork;

typedef boost::shared_ptr<ITask>  PITask;
typedef boost::shared_ptr<CFocusTask>  PCFocusTask;
typedef boost::shared_ptr<CZoomTask>  PCZoomTask;
typedef boost::shared_ptr<CPanTask>  PCPanTask;
typedef boost::shared_ptr<CTiltTask>  PCTiltTask;
typedef boost::shared_ptr<CSysTask>  PCSysTask;
typedef boost::shared_ptr<CRefresh>  PCRefresh;
typedef boost::shared_ptr<CCCD>  PCCCD;

typedef boost::shared_ptr<CSystem>  PCSystem;
typedef boost::shared_ptr<CSynchro>  PCSynchro;
typedef boost::shared_ptr<CTaskThread>  PCTaskThread;

typedef boost::shared_ptr<CSynchro2> PCSynchro2;
typedef boost::shared_ptr<CAmend> PCAmend;
typedef boost::shared_ptr<CAmendPwmMotor> PCAmendPwmMotor;
typedef boost::shared_ptr<CPWMFeedbackControl> PCPWMFeedbackControl;


typedef boost::shared_ptr<CSysPulses> PCSysPulses;
typedef boost::shared_ptr<CDevPulses> PCDevPulses;
typedef boost::shared_ptr<CManagePulse> PCManagePulse;
typedef boost::shared_ptr<CAmendPulse> PCAmendPulse;

#endif // DLP_DLP_DLPBOOST_H_
