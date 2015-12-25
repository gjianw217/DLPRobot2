#include "../../drivers/cgpio.h"
#include "../../utils/cdelay.h"
#include <iostream>

void TestGPIOOut(void)
{
    CGPIO gpio;
    std::cout<<"Set Pin and Value"<<std::endl;
    gpio.SetPort("9",0);//P
    std::cout<<"Ready Flash"<<std::endl;
    while(1)
    {
        std::cout<<"Value >> 0"<<std::endl;
        gpio.SetValue(0);
        delays(1);
        std::cout<<"Value >> 1"<<std::endl;
        gpio.SetValue(1);
        delays(1);

    }

}

#include "../../drivers/ccan.h"
#include "../../drivers/cpwm.h"
#define division 128
#define DIR_MODE 1;
#define SPEED_MODE 2;
#define GPIO_PIN 26 //P8_14


int Division=128;
int Driver2Deceleration=1;
int Deceleration2Motor=1;



void TestPWMCAN(void)
{
    int mode;

    int pps;
    int period;
    int duty;
    int speed=1;
    int dir=0;

    int data[8]={0};

    PCPWM ppwm(new CPWM("P8_34.11",20000,11111));
    PCCAN pcan(new CCAN(0x21));
    PCGPIO pgpio(new CGPIO());
    pgpio->SetPort("9",0);//P833

    //pps=speed*200*division/60;
    pps=Driver2Deceleration*Deceleration2Motor*speed*Division*200;
    period=1000000000/pps;
    // duty=period/2;
	duty=period*3/4;
	ppwm->SetDuty(0);
	ppwm->SetPeriod(period);
	ppwm->SetDuty(duty);
	ppwm->SetPolarity(1);
	ppwm->SetRun(1);

    do
    {
        printf("speed:%d,pps:%d,period:%d,duty:%d\n",speed,pps,period,duty);
        printf("dir  :%d\n",dir);
        printf("Plase input control mode:1-->directon \n");
        printf("                         2-->speed\n");
        scanf("%d",&mode);

        if(1==mode)
        {
            printf("plase input direction\n");
            scanf("%d",&dir);
            if(0==dir)
            {
               pgpio->SetValue(0);
            }
            else

            {
                pgpio->SetValue(1);
            }

        }
        else if(2==mode)
        {
            printf("plase input motor speed(rpm)\n");
            scanf("%d",&speed);
            if(0==speed)break;

            ppwm->SetRun(0);
            ppwm->SetDuty(0);

            //pps=speed*200*Division/60;
            //pps=Driver2Deceleration*Deceleration2Motor*speed*Division*200;
            pps=Driver2Deceleration*Deceleration2Motor*speed*Division*200/1000;//1/1000rps
            period=1000000000/pps;
            duty=period/2;

            ppwm->SetPeriod(period);
            ppwm->SetDuty(duty);
            ppwm->SetPolarity(1);
            ppwm->SetRun(1);

        }
        else
        {
            printf("plase reinput again\n");
        }

    }
    while(1);

    ppwm->SetRun(0);
    ppwm->SetDuty(0);

    return ;

}
