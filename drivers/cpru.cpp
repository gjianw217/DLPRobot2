#include "cpru.h"
#include "../utils/cdebug.h"

#define PRU_NUM0        0
#define PRU_NUM1        1
#define AM33XX

CPRU::CPRU(const std::string &name)
{
	m_name=name;
#ifdef DLP_ARM_LINUX
    Init();
#endif // DLP_ARM_LINUX
}

CPRU::~CPRU()
{
#ifdef DLP_ARM_LINUX
    prussdrv_pru_disable (PRU_NUM0);
    prussdrv_pru_disable (PRU_NUM1);
    prussdrv_exit ();
#endif // DLP_ARM_LINUX

}

void CPRU::Init()
{
#ifdef DLP_ARM_LINUX
    m_initdata0=PRUSS_INTC_INITDATA;//Open PRU0 Interrupt
    prussdrv_init();                //Initialize the data to
    prussdrv_open(PRU_EVTOUT_0);
    prussdrv_open(PRU_EVTOUT_1);
    prussdrv_pruintc_init(&m_initdata0);/* Map PRU's INTC */
//
//    m_initdata1=PRUSS_INTC_INITDATA;
//
//    prussdrv_pruintc_init(&m_initdata1);/* Map PRU's INTC */
#endif // DLP_ARM_LINUX
}

void CPRU::Exit()
{

}

void CPRU::Run(const uint32_t *pwm)
{

#ifdef DLP_ARM_LINUX
    if(!this->m_name.compare("pru1"))
	{
		/* Load and execute binary on PRU */
		prussdrv_pru_write_memory(PRUSS0_PRU1_DATARAM, 0, pwm, sizeof(unsigned int)*(4*10+3));

		prussdrv_exec_program (PRU_NUM1, "./prucode.bin");
	}
	else
	{
		/* Load and execute binary on PRU */
		prussdrv_pru_write_memory(PRUSS0_PRU0_DATARAM, 0, pwm, sizeof(unsigned int)*(4*10+3));
		prussdrv_exec_program (PRU_NUM0, "./pwm0.bin");

	}

    return ;
#endif // DLP_ARM_LINUX

#ifdef DLP_ARM_LINUX1  //putting the following code into the constructor, there will be a segment error??
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;;
	prussdrv_init ();
	prussdrv_open(PRU_EVTOUT_0);//Open PRU Interrupt
	prussdrv_open(PRU_EVTOUT_1);//Open PRU Interrupt
	/* Map PRU's INTC */
	prussdrv_pruintc_init(&pruss_intc_initdata);
	//////////////////////////////////////////////////////////////
	//for(int i=0;i<4*PWM_ORDER+3;i++)
#ifdef DLP_PRINT_PRU
	for(int i=0;i<4*10+3;i++)

	{
		std::cout<<"pwm["<<i<<"]>>>"<<pwm[i]<<std::endl;
	}
#endif // DLP_PRINT_PRU
	if(!this->m_name.compare("pru1"))
	{
		//prussdrv_pru_write_memory(PRUSS0_PRU1_DATARAM, 0, testpwm, sizeof(unsigned int)*(4*PWM_ORDER+3));
		//dlp_log(DLP_LOG_DEBUG,"INFO: prussdrv_pru1_write_memory");
		//prussdrv_pru_write_memory(PRUSS0_PRU1_DATARAM, 0, pwm, sizeof(unsigned int)*(4*PWM_ORDER+3));
		prussdrv_pru_write_memory(PRUSS0_PRU1_DATARAM, 0, pwm, sizeof(unsigned int)*(4*10+3));
		/* Load and execute binary on PRU */
		//dlp_log(DLP_LOG_DEBUG,"INFO: prussdrv1_exec_program");
		prussdrv_exec_program (PRU_NUM1, "./pwm1.bin");
		//dlp_log(DLP_LOG_DEBUG,"INFO: Wait for event completion from PRU1");
		//        prussdrv_pru_wait_event (PRU_EVTOUT_1);
		//        std::cout<<"INFO: PRU1 completed transfer."<<std::endl;
		//        prussdrv_pru_clear_event (PRU_EVTOUT_1,PRU1_ARM_INTERRUPT);
		/* Disable PRU and close memory mappings */
		//        prussdrv_pru_disable (PRU_NUM1);
		//        prussdrv_exit ();
	}
	else
	{
		//        prussdrv_pru_write_memory(PRUSS0_PRU0_DATARAM, 0, testpwm, sizeof(unsigned int)*(4*PWM_ORDER+3));
		//dlp_log(DLP_LOG_DEBUG,"INFO: prussdrv_pru0_write_memory");
		//prussdrv_pru_write_memory(PRUSS0_PRU0_DATARAM, 0, pwm, sizeof(unsigned int)*(4*PWM_ORDER+3));
		prussdrv_pru_write_memory(PRUSS0_PRU0_DATARAM, 0, pwm, sizeof(unsigned int)*(4*10+3));
		/* Load and execute binary on PRU */
		//dlp_log(DLP_LOG_DEBUG,"INFO: prussdrv0_exec_program");
		prussdrv_exec_program (PRU_NUM0, "./pwm0.bin");
		//dlp_log(DLP_LOG_DEBUG,"INFO:Wait for event completion from PRU0");
		//        prussdrv_pru_wait_event (PRU_EVTOUT_0);
		//        std::cout<<"INFO: PRU0 completed transfer."<<std::endl;
		//        prussdrv_pru_clear_event (PRU_EVTOUT_0,PRU0_ARM_INTERRUPT);
		/* Disable PRU and close memory mappings */
		//        prussdrv_pru_disable (PRU_NUM0);
		//        prussdrv_exit ();
	}
#ifdef DLP_PRINT_PRU
	gettimeofday(&end,NULL);
	time_use=(end.tv_sec-start.tv_sec)*1000+(end.tv_usec-start.tv_usec)/1000.0;
	printf("xxxxxxxxxxxxxxtime use is %fms\n",time_use);
#endif //DLP_PRINT_PRU
#endif // DLP_ARM_LINUX
}
