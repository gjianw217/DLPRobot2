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
	m_curves[DLP_MOTOR_CURVE_B]->SetAttr(m_attr);

}
PIRotation CAlgorithm::GetRotation(const DLPMotorRotationType &rotation)
{
	return m_rotations[rotation];
}

PICurve CAlgorithm::GetCurve(const DLPMotorCurveType &curve)
{
	return m_curves[curve];
}


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <mc9s12xs128.h>
//定义PID参数
#define VV_KPVALUE 3       //比例
#define VV_KIVALUE 40     //积分
#define VV_KDVALUE 3     //微分
#define VV_MAX 10000       //返回的最大值,是pwm的周期值
#define VV_MIN 0
#define VV_DEADLINE 0X08   //速度PID，设置死区范围
typedef struct PID       //定义数法核心数据
{
signed int vi_Ref;      //速度PID，速度设定值
signed int vi_FeedBack;  //速度PID，速度反馈值


signed long vi_PreError;  //速度PID，前一次，速度误差,,vi_Ref - vi_FeedBack
signed long vi_PreDerror; //速度PID，前一次，速度误差之差，d_error-PreDerror;


unsigned int v_Kp;      //速度PID，Ka = Kp
unsigned int v_Ki;      //速度PID，Kb = Kp * ( T / Ti )
unsigned int v_Kd;      //速度PID，

signed long vl_PreU;    //电机控制输出值

}PID;
PID  sPID;                //  PID Control Structure

void PIDInit(void)
{
sPID.vi_Ref = 0 ;        //速度设定值
sPID.vi_FeedBack = 0 ;  //速度反馈值

sPID.vi_PreError = 0 ;   //前一次，速度误差,,vi_Ref - vi_FeedBack
sPID.vi_PreDerror = 0 ;   //前一次，速度误差之差，d_error-PreDerror;

sPID.v_Kp = VV_KPVALUE;
sPID.v_Ki = VV_KIVALUE;
sPID.v_Kd = VV_KDVALUE;

sPID.vl_PreU = 0 ;      //电机控制输出值
}
unsigned int v_PIDCalc( PID *pp )
{
signed long  error,d_error,dd_error;

  error = (signed long)(pp->vi_Ref - pp->vi_FeedBack); // 偏差计算
  d_error = error - pp->vi_PreError;
  dd_error = d_error - pp->vi_PreDerror;
  pp->vi_PreError = error; //存储当前偏差
pp->vi_PreDerror = d_error;
if( ( error < VV_DEADLINE ) && ( error > -VV_DEADLINE ) ); //设置调节死区
              //速度PID计算
  pp->vl_PreU += (signed long)(  pp -> v_Kp * d_error + pp -> v_Ki * error  + pp->v_Kd*dd_error);

else if( pp->vl_PreU >= VV_MAX )   //速度PID，防止调节最高溢出
  pp->vl_PreU = VV_MAX;

else if( pp->vl_PreU <= VV_MIN ) //速度PID，防止调节最低溢出
  pp->vl_PreU = VV_MIN;
else
;
   return ( pp->vl_PreU  );  // 返回预调节占空比

}



void main(void) {
  /* put your own code here */

   InitMCu();
    IncPIDInit();
int g_CurrentVelocity=0;   //全局变量也初始化
int g_Flag=0;                //全局变量也初始化

EnableInterrupts;
  While(1)
{
   if (g_Flag&&vi_FeedBack)
      {
          PWMOUT+=  v_PIDCalc( PID *pp );
            g_Flag&=~ vi_FeedBack;
}
}
}
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}



