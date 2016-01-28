
#include "../devices/encoder/iencoder.h"
#include "../devices/motors/imotor.h"
#include "cpanpart.h"
#include "../utils/cdebug.h"
#include "../utils/cprintattr.h"
#include "../network/cdata-mapping.h"
CPanPart::CPanPart(PCDataMapping datamapping):IParts(datamapping)
{

}

CPanPart::~CPanPart()
{

}

void CPanPart::Init()
{
    DLPEncoderAttr cattr;
    DLPMotorAttr mattr;
    /*Whether encoder conditions are satisfied*/
    if (m_pdatamapping.use_count()!=0&&m_pcoder.use_count()==0)
    {
        dlp_log(DLP_LOG_DEBUG,"CPanPart Create Coder");
        IParts::CreateCoder(CAN_CODER_BOCHEN,DLP_PAN);
        /*Parsing the encoder configuration file attributes*/
        parseCoderAttr(cattr);
        m_pcoder->Config(cattr);
		m_pcoder->CounterInit(true);///////////////////////////
    }

    /*Whether motor conditions are satisfied*/
    if (m_pdatamapping.use_count()!=0&&m_pcoder.use_count()!=0&&m_pmotor.use_count()==0)
    {
        dlp_log(DLP_LOG_DEBUG,"CPanPart Create Motor");
        IParts::CreateMotor(STEP_MOTOR_BY_PRU,DLP_FOCUS);
        /*Parsing the motor configuration file attributes*/
        m_pmotor->SetCoder(m_pcoder);
        parseMotorAttr(mattr);
        m_pmotor->SetAttr(mattr);
    }
    /*Whether switch conditions are satisfied*/
    if (m_pdatamapping.use_count()!=0&&m_pcoder.use_count()!=0&&m_pmotor.use_count()!=0&&m_pswitch.use_count()==0)
    {
        dlp_log(DLP_LOG_DEBUG,"CPanPart Create Switch");
        IParts::CreateSwitch(Proximity_Switch,DLP_PAN);
        /*Parsing the motor configuration file attributes*/
        //m_pswitch->Config("pin");
    }
}


void CPanPart::parseCoderAttr(DLPEncoderAttr &attr)
{
    uint16_t data[10]={0};
    m_pdatamapping->GetHoldRegisters(PANCODER,8,data);//PANCODER==0x200

    attr.dlp_id=data[0];
    attr.dlp_serial.baudrate=0;//convert()baudrate to num
    attr.dlp_type=data[3];
    attr.dlp_model=data[4];
    attr.dlp_gear[0]=data[5];
    attr.dlp_gear[1]=data[6];
    attr.dlp_bits=data[7];
    attr.dlp_role=DLP_PAN;

    PrintCoderAttr(attr);

}

void CPanPart::parseMotorAttr(DLPMotorAttr &attr)
{
    uint16_t data[10]={0};
    m_pdatamapping->GetHoldRegisters(PANMOTOR,10,data);//PANMOTOR==0x800

//    attr.dlp_algorithm.max_speed=data[0];
//    attr.dlp_algorithm.min_speed=data[1];
//    attr.dlp_algorithm.acc=data[2];
//    attr.dlp_algorithm.division=data[3];
//    attr.dlp_algorithm.gear[0]=data[4];
//    attr.dlp_algorithm.gear[1]=data[5];

    attr.dlp_algorithm.g.max_speed=data[0];
    attr.dlp_algorithm.g.min_speed=data[1];
    attr.dlp_algorithm.g.division=data[2];
    attr.dlp_algorithm.g.gear[0]=data[4];
    attr.dlp_algorithm.g.gear[1]=data[5];
    attr.dlp_algorithm.t.acc=data[3];
    attr.dlp_algorithm.s.amax=20;
    attr.dlp_algorithm.s.hmax=2;
    attr.dlp_algorithm.b.inc=1/BORDERNUM;

    attr.dlp_curve=static_cast<DLPMotorCurveType>(data[6]);
    attr.dlp_rotation=static_cast<DLPMotorRotationType>(data[7]);

    //attr.dlp_algorithm.role=static_cast<DLPRole>(data[8]);
    attr.dlp_algorithm.role=DLP_PAN;
    attr.dlp_type=data[8];
    attr.dlp_model=data[9];

    m_pdatamapping->GetInputRegisters(PANMOTOR+5,4,data);//PANMOTOR==0x800

    attr.dlp_pwm.pwmpin=data[0];
    attr.dlp_pwm.pwmvalue=data[1];
    attr.dlp_dir.pin=data[2];
    attr.dlp_dir.value=data[3];

    PrintMotorAttr(attr);
}
