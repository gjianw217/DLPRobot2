#ifndef DLP_ROBOT_CMANAGEPULSE_H_
#define DLP_ROBOT_CMANAGEPULSE_H_

#include "../dlp/dlp.h"
#include <map>

typedef struct
{
    bool     cmd_convert_curve_enable;
    bool     angle_pulse_existence;
    uint32_t angle_pulse_frame_counter;
    uint32_t angle_pulse_frame_sum;
}DLPPulse;

class CManagePulse
{
public:
    CManagePulse();
	~CManagePulse();
	//CAmendPulse
	void SetMotrAttr(const DLPMotorPulse &type,const DLPMotorAttr &mattr,const DLPEncoderAttr &eattr);
	int IsAmend(const DLPMotorPulse &type,const float &coder_angle);
	int IsConvert(const DLPMotorPulse &type);
	int IsPulses(void );
	void GetAmendParameter(const DLPMotorPulse &type,uint16_t *time_angle);
	void SetAmendParameter(const DLPMotorPulse &type,uint16_t *time_angle);
    void UpdateCurveAngle(const DLPMotorPulse &type,const float &coder_angle);
	//CDevPulses
	void UpdateCurvePulse(const DLPMotorPulse &type,const uint8_t &len,const uint32_t *src);  //convert the angle into pulse according to the curve type

	//CSysPulses
	void RunPulseGroup();      //run the step motor

	//Local
	int CheckCurveConvert(const DLPMotorPulse &type);
	void SetConvertDisable(const DLPMotorPulse &type);
	void SetConvertEnable(const DLPMotorPulse &type);

	uint8_t CheckMotorPulse();

	// allls
	void UpdatePulseGroup();  //get the pulse and be ready for running at a frame





protected:
    PCSysPulses m_psys_pulses;
	PCDevPulses m_pdev_pulses;
	PCAmendPulse m_pamend_pulses;

private:
    DLPPulse m_pulse[4];


};


#endif // DLP_ROBOT_CMANAGEPULSE_H_
