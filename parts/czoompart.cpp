#include "../devices/encoder/ccancoder.h"
#include "../devices/encoder/crs485coder.h"
#include "../devices/motors/cstepmotorbypwm.h"
#include "../devices/motors/cstepmotorbypru.h"
#include "../devices/switch/cproximityswitch.h"
#include "../network/cdata-mapping.h"
#include "../utils/cdebug.h"
#include "../utils/cprintattr.h"
#include "czoompart.h"

CZoomPart::CZoomPart(PCDataMapping datamapping):IParts(datamapping)
{

}

CZoomPart::~CZoomPart()
{

}

void CZoomPart::Init()
{
    DLPEncoderAttr cattr;
    DLPMotorAttr mattr;
    /*Whether encoder conditions are satisfied*/
    if (m_pdatamapping.use_count()!=0&&m_pcoder.use_count()==0)
    {
        dlp_log(DLP_LOG_DEBUG,"CZoomPart Create Coder");
        IParts::CreateCoder(RS485_CODER_BOCHEN,DLP_ZOOM);
        /*Parsing the encoder configuration file attributes*/
        parseCoderAttr(cattr);
        m_pcoder->Config(cattr);
        m_pcoder->CounterInit(false);///////////////////////////
    }

    /*Whether motor conditions are satisfied*/
    if (m_pdatamapping.use_count()!=0&&m_pcoder.use_count()!=0&&m_pmotor.use_count()==0)
    {
        dlp_log(DLP_LOG_DEBUG,"CZoomPart Create Motor");
        IParts::CreateMotor(STEP_MOTOR_BY_PWM,DLP_ZOOM);
        /*Parsing the motor configuration file attributes*/
        m_pmotor->SetCoder(m_pcoder);
        parseMotorAttr(mattr);
        m_pmotor->SetAttr(mattr);
    }
}

void CZoomPart::parseCoderAttr(DLPEncoderAttr &attr)
{
    uint16_t data[10]={0};
    //m_pdatamapping->GetHoldRegisters(0x500,8,data);
    m_pdatamapping->GetHoldRegisters(ZOOMCODER,8,data);//FOCUSCODER==0x400
    attr.dlp_id=data[0];
    attr.dlp_serial.baudrate=0;//convert()baudrate to num
    attr.dlp_type=data[3];
    attr.dlp_model=data[4];
    attr.dlp_gear[0]=data[5];
    attr.dlp_gear[1]=data[6];
    attr.dlp_bits=data[7];
    attr.dlp_role=DLP_ZOOM;
    m_pdatamapping->GetInputRegisters(0x506,4,data);
    attr.dlp_serial.databit=data[0];
    attr.dlp_serial.stop=data[1];
    attr.dlp_serial.flow=data[2];
    attr.dlp_serial.parity=data[3];
    PrintCoderAttr(attr);

}

void CZoomPart::parseMotorAttr(DLPMotorAttr &attr)
{
//    uint16_t data[10]={0};
//    m_pdatamapping->GetHoldRegisters(ZOOMMOTOR,12,data);//ZOOMMOTOR==0xB00
//
//    attr.dlp_algorithm.max_speed=data[0];
//    attr.dlp_algorithm.min_speed=data[1];
//    attr.dlp_algorithm.acc=data[2];
//    attr.dlp_algorithm.division=data[3];
//
//
//    attr.dlp_algorithm.gear[0]=data[4];
//    attr.dlp_algorithm.gear[1]=data[5];
//    attr.dlp_curve=static_cast<DLPMotorCurveType>(data[6]);
//    attr.dlp_rotation=static_cast<DLPMotorRotationType>(data[7]);
//    attr.dlp_type=data[8];
//    attr.dlp_algorithm.role=static_cast<DLPRole>(data[8]);
//    attr.dlp_model=data[9];
//
//    attr.dlp_pwm.dutyNs=data[11]<<8|data[10];
//    attr.dlp_pwm.periodNs=data[13]<<8|data[12];;
//    attr.dlp_pwm.polarity=data[14];
//    attr.dlp_pwm.runStatus=data[15];
//
//    m_pdatamapping->GetInputRegisters(ZOOMMOTOR+5,4,data);
//    attr.dlp_pwm.pwmpin=data[0];
//    attr.dlp_pwm.pwmvalue=data[1];
//    attr.dlp_dir.pin=data[2];
//    attr.dlp_dir.value=data[3];
//
//    PrintMotorAttr(attr);

}
