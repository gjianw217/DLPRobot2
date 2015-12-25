#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

#include "../../network/modbus/modbus.h"

#define G_MSEC_PER_SEC 1000

uint32_t gettime_ms(void)
{
    struct timeval tv;
    gettimeofday (&tv, NULL);

    return (uint32_t) tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

uint32_t gettime_us(void)
{
     struct timeval tv;
     gettimeofday(&tv,NULL);
     return (uint32_t) tv.tv_usec;
}
enum {
    TCP,
    RTU
};

/* Tests based on PI-MBUS-300 documentation */
int main(int argc, char *argv[])
{
    uint8_t *tab_bit;
    uint8_t *tab_input_bit;
    uint16_t *tab_reg;
    uint16_t *tab_input_reg;
    uint8_t *tab_send_bit;
    uint16_t *tab_send_reg;

    modbus_t *ctx;
    int i;
    int nb_points;
    double elapsed;
    uint32_t start;
    uint32_t end;
    uint32_t bytes;
    uint32_t rate;

	struct timeval mystart;
	struct timeval myend;
    int rc;
    int n_loop;
    int use_backend;

    if (argc > 1)
    {
        if (strcmp(argv[1], "tcp") == 0) {
            use_backend = TCP;
            n_loop = 100000;
        } else if (strcmp(argv[1], "rtu") == 0) {
            use_backend = RTU;
            n_loop = 100;
        } else {
            printf("Usage:\n  %s [tcp|rtu] - Modbus client to measure data bandwith\n\n", argv[0]);
            exit(1);
        }
    }
    else
    {
        /* By default */
        use_backend = TCP;
        n_loop = 100000;
    }

    if (use_backend == TCP)
    {
//   ctx = modbus_new_tcp("127.0.0.1", 1502);
//     ctx = modbus_new_tcp("192.168.1.103", 1502);
//    ctx = modbus_new_tcp("192.168.7.10", 1502);
//    ctx = modbus_new_tcp("192.168.21.141", 1502);
   ctx = modbus_new_tcp("192.168.0.10", 1502);
 //    ctx = modbus_new_tcp("192.168.0.217", 1502);
    //

//ctx = modbus_new_tcp("192.168.0.10", 1502);
/*
#ifndef DLP_ARM_LINUX
	ctx = modbus_new_tcp("192.168.0.10", 1502);
printf(" 192.168.0.10,modbus new TCP or RTU\n");
#else
	ctx = modbus_new_tcp("192.168.0.217", 1502);
printf(" 192.168.0.217 ,modbus new TCP or RTU\n");
#endif //DLP_ARM_LINUX
*/  
	//ctx = modbus_new_tcp("192.168.0.217", 1502);
        i=modbus_set_slave(ctx,3);
        printf("modbus_set_slave set sucess %s\n",i==0?"sucess":"failure");
        modbus_set_debug(ctx,TRUE);
    }
    else
    {
        //ctx = modbus_new_rtu("/dev/ttyUSB1", 115200, 'N', 8, 1);
        //modbus_set_slave(ctx, 1);
        printf(" error ,modbus new TCP or RTU\n");
    }
    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connexion failed: %s\n",
                modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    /* Allocate and initialize the memory to store the status */
    tab_bit = (uint8_t *) malloc(MODBUS_MAX_READ_BITS * sizeof(uint8_t));
    memset(tab_bit, 0, MODBUS_MAX_READ_BITS * sizeof(uint8_t));
    tab_input_bit = (uint8_t *) malloc(MODBUS_MAX_READ_BITS * sizeof(uint8_t));
    memset(tab_input_bit, 0, MODBUS_MAX_READ_BITS * sizeof(uint8_t));
    tab_send_bit=(uint8_t*)malloc(MODBUS_MAX_READ_BITS*sizeof(uint8_t));
    memset(tab_send_bit,1,MODBUS_MAX_READ_BITS*sizeof(uint8_t));
    /* Allocate and initialize the memory to store the registers */
    tab_reg = (uint16_t *) malloc(MODBUS_MAX_READ_REGISTERS * sizeof(uint16_t));
    memset(tab_reg, 0, MODBUS_MAX_READ_REGISTERS * sizeof(uint16_t));

    tab_input_reg = (uint16_t *) malloc(MODBUS_MAX_READ_REGISTERS * sizeof(uint16_t));
    memset(tab_input_reg, 0, MODBUS_MAX_READ_REGISTERS * sizeof(uint16_t));
    tab_send_reg=(uint16_t*)malloc(MODBUS_MAX_READ_REGISTERS*sizeof(uint16_t));
    memset(tab_send_reg,1,MODBUS_MAX_READ_REGISTERS*sizeof(uint16_t));



 /*****************************************/
/**0000000000000000000000000000000000系统功能测试 */
/******************************************/

	uint16_t device=0XFF,operation=0xff,value=0xff;
	uint16_t array[6]={0};
        modbus_write_bit(ctx,0,1);
	while (1)
	{
		printf("last  command:device>>%d,operatio>>%d,value>>%d\n",device,operation,value);
		printf("input command:data data data>>");
		scanf("%d%d%d",&device,&operation,&value);
		printf("exectue command:device>>%d,operatio>>%d,value>>%d\n",device,operation,value);
		//////////////////////////////////////////////////////////////
		//read data
		switch(device)
		{

            case 0:
            {
                if(0==operation)
                {
                    printf("\t\nget Controler right\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x000,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
                }
                else if(1==operation)
                {
                    printf("\t\nScanning the coders id\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x001,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");

                }
                else if(2==operation)
                {
                    printf("\t\nCheck device status\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x002,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");

                }
                else if(3==operation)
                {
                    printf("\t\nColloect the Coders value\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x003,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");

                }
                else if(4==operation)
                {
                    printf("The Sytstem Return origin\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x004,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
                }
                else if(5==operation)
                {
                    printf("enable the motors stop\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x005,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");

                }
		else if(6==operation)
                {
                    printf("set Controler id\n");
                    printf("-----------------------------\n");
                    /*array[3]=127;
                    array[2]=0;
                    array[1]=0;
                    array[0]=value;*/
                    rc=modbus_write_registers(ctx,0x001,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
                }
                else if(7==operation)
                {

                    printf("set current position reference\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x002,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");

                }

                else if(8==operation)
                {
                    printf("set system os\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x030,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
                }
                else if(9==operation)
                {

                    printf("set system version\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x031,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
                }
                else if(10==operation)
                {
                    printf("set system factory time\n");
                    printf("-----------------------------\n");
                    array[2]=0xFF;
                    array[1]=0xFF;
                    array[0]=value;
                    rc=modbus_write_registers(ctx,0x032,3,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
                }
                else if(11==operation)
                {
                    printf("set system model\n");
                    printf("-----------------------------\n");
                    array[3]=0xFF;
                    array[2]=0xFF;
                    array[1]=0xFF;
                    array[0]=value;
                    rc=modbus_write_registers(ctx,0x035,4,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");

                }
                else if(12==operation)
                {
                    printf("set system sn\n");
                    printf("-----------------------------\n");
					array[1]=0xFF;
                    array[0]=value;
                    rc=modbus_write_registers(ctx,0x039,2,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
                }
				 else if(13==operation)
                {
                    printf("enable the server mode\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x006,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");

                }
                else if(20==operation)
                {
                    printf("get system ip and control right\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_input_registers(ctx,0x001,5,array);
                    if(rc==-1)
                        exit(0);
                    else
                    {
                        printf("R:IP: %d,%d,%d,%d,%d\n",array[4],array[3],array[2],array[1],array[0]);
                    }
                    printf("-----------------------------\n");
                }
                else if(21==operation)
                {
                    printf("get id by scanned :\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_input_registers(ctx,0x006,5,array);
                    if(rc==-1)
                        exit(0);
                    else
                    {
                        printf("id: %d,%d,%d,%d,%d\n",array[4],array[3],array[2],array[1],array[0]);
                    }
                    printf("-----------------------------\n");
                }
                else if(23==operation)
                {
                    printf("\nget sensor value\n\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_input_registers(ctx,0x010,4,array);
                    if(rc==-1)
					   exit(0);
                    else
                    {
					    printf("data: %d,%x,%x,%x,%x\n",rc,array[3],array[2],array[1],array[0]);
                    }
                    printf("-----------------------------\n");

                }

                else if(26==operation)
                {
                    printf("\nget bbb id value\n\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x001,1,array);
                    if(rc==-1)
					   exit(0);
                    else
                    {
					    printf("data: %d\n",array[0]);
                    }
                    printf("-----------------------------\n");

                }

                 else if(28==operation)
                {
                    printf("\nget system os\n\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x030,1,array);
                    if(rc==-1)
					   exit(0);
                    else
                    {
					    printf("data: %d\n",array[0]);
                    }
                    printf("-----------------------------\n");

                }
                else if(29==operation)
                {
                    printf("\nget system version\n\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x031,1,array);
                    if(rc==-1)
					   exit(0);
                    else
                    {
					    printf("data: %d\n",array[0]);
                    }
                    printf("-----------------------------\n");

                }
                else if(30==operation)
                {
                    printf("get system factory time\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x032,3,array);
                    if(rc==-1)
                        exit(0);
                    else
                    {
                        printf("time %d,%d,%d\n",array[2],array[1],array[0]);
                    }
                    printf("-----------------------------\n");
                }
                else if(31==operation)
                {
                    printf("get system model\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x035,4,array);
                    if(rc==-1)
                        exit(0);
                    else
                    {
					   printf("model %c,%c,%c,%d\n",array[0],array[1],array[2],array[3]);
                    }
                    printf("-----------------------------\n");
                }
                else if(32==operation)
                {
                    printf("get system sn\n\n");
                    printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x039,4,array);
                    if(rc==-1)
					   exit(0);
                    else
                    {
					    printf("sn %d,%d,%d,%d,%d\n",rc,array[0],array[1],array[2],array[3]);
                    }
                    printf("-----------------------------\n");

                }
                break;

            }//end case0
            //operation pitch coder
			case 1:
			{
				if(0==operation)
				{
                    printf("\nxxxxxxlens connection xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0100,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(1==operation)
				{
                    printf("\nxxxxxxlens reset xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0101,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(2==operation)
				{
                    printf("\nxxxxxxlens irils position xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0102,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(3==operation)
				{
                    printf("\nxxxxxxlens zoom position xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0103,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(4==operation)
				{
                    printf("\nxxxxxxlens focuns position xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0104,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(5==operation)
				{
                    printf("\nxxxxxx lens bitrate xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0101,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(6==operation)
				{
                    printf("\nxxxxxx lens comm standard xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0102,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(7==operation)
				{
                    printf("\nxxxxxx lens model xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0103,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(8==operation)
				{
                    printf("\nxxxxxx irils control xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0111,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(9==operation)
				{
                    printf("\nxxxxxx zoom contro xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0112,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(10==operation)
				{
                    printf("\nxxxxxx focus control xxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0113,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				break;
            }
			//operation panning coder
			case 2:
			{
				 if(0==operation)
				{
                    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                    printf("-----------------------------\n");
                    array[4]=value;
                    array[3]=270;
					array[2]=0;
                    array[1]=10;
					array[0]=0;
                    rc=modbus_write_registers(ctx,0x0910,5,array);
					rc=modbus_write_registers(ctx,0x0910,5,array);
                    rc=modbus_write_registers(ctx,0x0910,5,array);
                   // rc=modbus_write_registers(ctx,0x0812,2,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(1==operation)
				{
					printf("panning move 90\n");
					printf("-----------------------------\n");
					array[4]=value;
                    array[3]=90;
					array[2]=0;
                    array[1]=10;
					array[0]=0;
                    rc=modbus_write_registers(ctx,0x0810,5,array);
					//rc=modbus_write_registers(ctx,0x0910,5,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				}
                else if(2==operation)
				{
					printf("pitch move 90\n");
					printf("-----------------------------\n");
					array[4]=value;
                    array[3]=90;
					array[2]=0;
                    array[1]=10;
					array[0]=0;
                    rc=modbus_write_registers(ctx,0x0910,5,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				}
				else if(3==operation)
				{
					printf("panning move 90\n");
					printf("-----------------------------\n");
					array[2]=value;
                    array[1]=90;
					array[0]=0;
                    rc=modbus_write_registers(ctx,0x0812,3,array);
					//rc=modbus_write_registers(ctx,0x0810,5,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				}
				else if(4==operation)
				{
					printf("pitch move 90\n");
					printf("-----------------------------\n");
					array[2]=value;
                    array[1]=90;
					array[0]=0;
                    rc=modbus_write_registers(ctx,0x0912,3,array);
//					rc=modbus_write_registers(ctx,0x0910,5,array);
//                    rc=modbus_write_registers(ctx,0x0910,5,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				}
                else if(5==operation)
				{
					printf("panning move 180\n");
					printf("-----------------------------\n");
					array[2]=value;
                    array[1]=180;
					array[0]=0;
                    rc=modbus_write_registers(ctx,0x0812,3,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				}
				else if(6==operation)
				{
					printf("pitch move 180\n");
					printf("-----------------------------\n");
					array[2]=value;
                    array[1]=180;
					array[0]=0;
                    rc=modbus_write_registers(ctx,0x0912,3,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				}
                else if(7==operation)
				{
					printf("get coder move angle\n");
                    modbus_read_input_registers(ctx,0x805,3,array);
					printf("coder move angle %d %d.%d\n",array[2],array[1],array[0]);
                    printf("-----------------------------\n");
				}
				else
				{
					printf("input error1,please input again!\n");
				}
				break;
			}
			//operation pitch motor
			case 3:
			 {
				 if(0==operation)
				 {
					printf("\t\nset pitch motor direction\n");
					printf("-----------------------------\n");
     				rc=modbus_write_registers(ctx,0x0300,1,&value);
				    if(rc==-1)
					   exit(0);
				    printf("-----------------------------\n");
				 }
				 else if(1==operation)
				 {
					printf("\t\nset pitch motor running by time\n");
					printf("-----------------------------\n");
     				rc=modbus_write_registers(ctx,0x0301,1,&value);
				    if(rc==-1)
					   exit(0);
				    printf("-----------------------------\n");
				 }
				 else if(2==operation)
				 {
					printf("\t\nset pitch motor running by angle\n");
					printf("-----------------------------\n");
     				rc=modbus_write_registers(ctx,0x0302,1,&value);
				    if(rc==-1)
					   exit(0);
				    printf("-----------------------------\n");
				 }
				  else if(3==operation)
				 {
					printf("\t\nset pitch motor running maxspeed\n");
					printf("-----------------------------\n");
     				rc=modbus_write_registers(ctx,0x0303,1,&value);
				    if(rc==-1)
					   exit(0);
				    printf("-----------------------------\n");
				 }
				  else if(4==operation)
				 {
					printf("\t\nset pitch motor running minspeed\n");
					printf("-----------------------------\n");
     				rc=modbus_write_registers(ctx,0x0304,1,&value);
				    if(rc==-1)
					   exit(0);
				    printf("-----------------------------\n");
				 }
				  else if(5==operation)
				 {
					printf("\t\nset pitch motor running acceleration time\n");
					printf("-----------------------------\n");
     				rc=modbus_write_registers(ctx,0x0305,1,&value);
				    if(rc==-1)
					   exit(0);
				    printf("-----------------------------\n");
				 }
				  else if(6==operation)
				 {
					printf("\t\nset pitch motor running factor\n");
					printf("-----------------------------\n");
     				rc=modbus_write_registers(ctx,0x0306,1,&value);
				    if(rc==-1)
					   exit(0);
				    printf("-----------------------------\n");
				 }
				 else
				 {
					 printf("\ninput error4,please input again!\n");
				}
				 break;
			 }//end case 3
            /**平摇编码器功能测试*/
			case 4:
			{
				if(0==operation)
				 {
					printf("\t\nset panning coder id\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0400,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
				 else if(1==operation)
				 {
					printf("\t\nset panning coder baud\n");
					printf("-----------------------------\n");
					array[0]=value;
					array[1]=0xff;
                    rc=modbus_write_registers(ctx,0x0401,2,array);
				   	 if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
                else if(2==operation)
				 {
					printf("\t\ncollecting the coder\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0400,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
				 else if(3==operation)
				 {
					printf("\t\nset panning coder model\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0403,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
 				else if(4==operation)
				 {
					printf("\t\nset panning coder type\n");
					printf("-----------------------------\n");
					rc=modbus_write_register(ctx,0x0404,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
 				else if(5==operation)
				 {

					printf("\t\nset panning coder gear\n");
					printf("-----------------------------\n");
					array[0]=1;
					array[1]=value;
                    rc=modbus_write_registers(ctx,0x0405,2,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
                else if(6==operation)
				 {
					printf("\t\nsetting current pos for the coder reference \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0401,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
                else if(7==operation)
				 {
					printf("\t\nscanning coder id \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0402,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
				else if(10==operation)
				 {
					printf("\t\nget panning coder id\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0400,1,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0400]%d\n",array[0]);
                    printf("-----------------------------\n");
				 }
				 else if(11==operation)
				 {
					printf("\t\nget panning coder baud\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0401,2,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0401]%d\ntab_register[0x0402]%d\n",array[0],array[1]);
                    printf("-----------------------------\n");
				 }
                  else if(12==operation)
				 {
					printf("\t\nget panning coder data\n");
					printf("-----------------------------\n");
                    rc=modbus_read_input_registers(ctx,0x0400,4,array);
				   	 if(rc==-1)
					   exit(0);
				   	 for(i=0;i<4;i++)
					   {
                        printf("tab_input_register[0x04%02d]:%x\n",i,array[i]);
					   }
                    printf("-----------------------------\n");
				 }
				 else if(13==operation)
				 {
					printf("\t\nget panning coder model\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0403,1,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0403]%d\n",array[0]);
                    printf("-----------------------------\n");
				 }
 				else if(14==operation)
				 {
					printf("\t\nget panning coder type\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0404,1,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0404]%d\n",array[0]);
                    printf("-----------------------------\n");
				 }
 				else if(15==operation)
				 {
					printf("\t\nget panning coder gear\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0405,2,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0405]%d\ntab_register[0x0406]%d\n",array[0],array[1]);
                    printf("-----------------------------\n");
				 }
				else if(16==operation)
				 {
					printf("\t\ngetting the coder origin value\n");
					printf("-----------------------------\n");
					array[0]=value;
                    rc=modbus_read_input_registers(ctx,0x0404,2,array);
                    if(rc==-1)
					   exit(0);
		printf("tab_input_register[0x0405]%d\ntab_input_register[0x0404]%d\n",array[1],array[0]);
                    printf("-----------------------------\n");
				 }
				break;

			}//case 4
			/**俯仰编码器功能测试*/
			case 5:
			{
				if(0==operation)
				 {
					printf("\t\nset panning coder id\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0500,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
				 else if(1==operation)
				 {
					printf("\t\nset panning coder baud\n");
					printf("-----------------------------\n");
					array[0]=value;
					array[1]=0xff;
                    rc=modbus_write_registers(ctx,0x0501,2,array);
				   	 if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
                else if(2==operation)
				 {
					printf("\t\ncollecting the coder\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0500,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
				 else if(3==operation)
				 {
					printf("\t\nset panning coder model\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0503,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
 				else if(4==operation)
				 {
					printf("\t\nset panning coder type\n");
					printf("-----------------------------\n");
					rc=modbus_write_register(ctx,0x0504,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
 				else if(5==operation)
				 {

					printf("\t\nset panning coder gear\n");
					printf("-----------------------------\n");
					array[0]=1;
					array[1]=value;
                    rc=modbus_write_registers(ctx,0x0505,2,array);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
                else if(6==operation)
				 {
					printf("\t\nsetting current pos for the coder reference \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bit(ctx,0x0501,value);
                    if(rc==-1)
					   exit(0);
                    printf("-----------------------------\n");
				 }
				else if(10==operation)
				 {
					printf("\t\nget panning coder id\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0500,1,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0500]%d\n",array[0]);
                    printf("-----------------------------\n");
				 }
				 else if(11==operation)
				 {
					printf("\t\nget panning coder baud\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0501,2,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0501]%d\ntab_register[0x0502]%d\n",array[0],array[1]);
                    printf("-----------------------------\n");
				 }
                  else if(12==operation)
				 {
					printf("\t\nget panning coder data\n");
					printf("-----------------------------\n");
                    rc=modbus_read_input_registers(ctx,0x0500,4,array);
				   	 if(rc==-1)
					   exit(0);
					printf("tab_register[0x0500]:%d\ntab_register[0x0501]:%d\n",array[0],array[1]);
                    printf("tab_register[0x0502]:%d\ntab_register[0x0503]:%d\n",array[2],array[3]);
                    printf("-----------------------------\n");
				 }
				 else if(13==operation)
				 {
					printf("\t\nget panning coder model\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0503,1,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0503]%d\n",array[0]);
                    printf("-----------------------------\n");
				 }
 				else if(14==operation)
				 {
					printf("\t\nget panning coder type\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0504,1,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0504]%d\n",array[0]);
                    printf("-----------------------------\n");
				 }
 				else if(15==operation)
				 {
					printf("\t\nget panning coder gear\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0505,2,array);
                    if(rc==-1)
					   exit(0);
					printf("tab_register[0x0505]%d\ntab_register[0x0506]%d\n",array[0],array[1]);
                    printf("-----------------------------\n");
				 }
				else if(16==operation)
				 {
					printf("\t\ngetting the coder origin value\n");
					printf("-----------------------------\n");
					array[0]=value;
                    rc=modbus_read_input_registers(ctx,0x0504,2,array);
                    if(rc==-1)
					   exit(0);
		printf("tab_input_register[0x0505]%d\ntab_input_register[0x0504]%d\n",array[1],array[0]);
                    printf("-----------------------------\n");
				 }
				break;

			}//case 5

			//operation panning motor
			/**平摇电机功能测试*/
			case 8:
			{
				if(0==operation)
				{
					printf("\t\nset panning motor max running speed\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0800,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(1==operation)
				{
					printf("\t\nset panning motor min running speed\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0801,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(2==operation)
				{
					printf("\t\nset panning motor acceleration time\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0802,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(3==operation)
				{
					printf("\t\nset panning motor subdivision\n");
					printf("-----------------------------\n");
					if(!(value==1||value==2||value==4||value==8||value==16))
					{
					    printf("input error ,please 1 2 4 8 or 16\n");
					    break;
                    }
                    rc=modbus_write_registers(ctx,0x0803,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(4==operation)
				{
					printf("\t\nset panning motor gear\n");
					printf("-----------------------------\n");
					array[0]=1;
					array[1]=value;
                    rc=modbus_write_registers(ctx,0x0804,2,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(5==operation)
				{
					printf("\t\nset panning motor direction\n");
					printf("-----------------------------\n");
					rc=modbus_write_bits(ctx,0x0800,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(6==operation)
				{
					printf("\t\nset panning motor algorithm\n");
					printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0806,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(7==operation)
				{
					printf("\t\nenable the Panning motor reset\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0801,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(8==operation)
				{
					printf("\t\nEmergence stop the panning Motor \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0802,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(9==operation)
				{
					printf("\t\nSetting the current pos for renfence point \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0803,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(10==operation)
				{
					printf("\t\nRunning the Panning Motor by time\n");
					printf("-----------------------------\n");
					array[0]=1;
					array[1]=value;
					array[2]=0;
					array[3]=180;
					array[4]=1;

                    rc=modbus_write_registers(ctx,0x0810,5,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(12==operation)
				{
					printf("\t\nRunning the Panning Motor by Angle\n");
					printf("-----------------------------\n");
					array[0]=0;
					array[1]=value;
					array[2]=0;
                    rc=modbus_write_registers(ctx,0x0812,3,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}

				else if(20==operation)
				{
					printf("\t\nget panning motor max running speed\n");
					printf("-----------------------------\n");
					start = gettime_us();
                    rc=modbus_read_registers(ctx,0x0800,1,array);
					printf("max running speed >>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    end = gettime_us();
                    printf("Reading Times %d us:\n",end-start);
                    printf("-----------------------------\n");
				}
				else if(21==operation)
				{
					printf("\t\nget panning motor min running speed\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0801,1,array);
					printf("motor min running speed>>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(22==operation)
				{
					printf("\t\nget panning motor acceleration time\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0802,1,array);
					printf("motor acceleration time>>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(23==operation)
				{
					printf("\t\nget panning motor subdivision\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0803,1,array);
                    printf("motor subdivision>>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(24==operation)
				{
					printf("\t\nget panning motor gear\n");
					printf("-----------------------------\n");

                    rc=modbus_read_registers(ctx,0x0804,2,array);
                    printf("get panning motor gear>>%d,%d\n",array[1],array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(25==operation)
				{
					printf("\t\nget panning motor direction\n");
					printf("-----------------------------\n");
                    rc= modbus_read_bits(ctx,0x0800,1,&value);
                    printf("get panning motor direction>>%d\n",value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(26==operation)
				{
					printf("\t\nget panning motor algorithm\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0806,1,&value);
                    printf("get panning motor algorithm>>%d\n",value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(29==operation)
				{
					printf("\t\ngetting the current pos for renfence point \n");
					printf("-----------------------------\n");
                    rc=modbus_read_input_registers(ctx,0x0800,2,array);
                    printf("getting renfence point array[1],array[0]>>%d,>%d\n",array[1],array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}

                else if(30==operation)
                {
                    printf("\t\nTest...\n");
					printf("-----------------------------\n");
					array[0]=value;
					array[1]=0;
					array[2]=1;
                    rc=modbus_write_registers(ctx,0x0812,3,array);
                }
                else
				{
					printf("input error 0,please input again!\n");
				}
				break;
			}//end case 8
            //operation the pitch motor
			/**俯仰电机功能测试*/
			case 9:
			{
				if(0==operation)
				{
					printf("\t\nset panning motor max running speed\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0900,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(1==operation)
				{
					printf("\t\nset panning motor min running speed\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0901,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(2==operation)
				{
					printf("\t\nset panning motor acceleration time\n");
					printf("-----------------------------\n");
                    rc=modbus_write_register(ctx,0x0902,value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(3==operation)
				{
					printf("\t\nset panning motor subdivision\n");
					printf("-----------------------------\n");
					if(!(value==1||value==2||value==4||value==8||value==16))
					{
					    printf("input error ,please 1 2 4 8 or 16\n");break;
                    }
                    rc=modbus_write_registers(ctx,0x0903,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(4==operation)
				{
					printf("\t\nset panning motor gear\n");
					printf("-----------------------------\n");
					array[0]=1;
					array[1]=value;
                    rc=modbus_write_registers(ctx,0x0904,2,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(5==operation)
				{
					printf("\t\nset panning motor direction\n");
					printf("-----------------------------\n");
                    rc= modbus_write_registers(ctx,0x914,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(6==operation)
				{
					printf("\t\nset panning motor algorithm\n");
					printf("-----------------------------\n");
                    rc=modbus_write_registers(ctx,0x0906,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(7==operation)
				{
					printf("\t\nenable the Panning motor reset\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0901,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(8==operation)
				{
					printf("\t\nEmergence stop the panning Motor \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0902,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(9==operation)
				{
					printf("\t\nSetting the current pos for renfence point \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0903,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(10==operation)
				{
					printf("\t\nRunning the Panning Motor by time\n");
					printf("-----------------------------\n");
					array[0]=0;
					array[1]=value;
                    rc=modbus_write_registers(ctx,0x0910,2,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(12==operation)
				{
					printf("\t\nRunning the Panning Motor by Angle\n");
					printf("-----------------------------\n");
					array[0]=0;
					array[1]=value;
					array[2]=0;
                    rc=modbus_write_registers(ctx,0x0912,3,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(20==operation)
				{
					printf("\t\nget panning motor max running speed\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0900,1,array);
					printf("max running speed >>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(21==operation)
				{
					printf("\t\nget panning motor min running speed\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0901,1,array);
					printf("motor min running speed>>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(22==operation)
				{
					printf("\t\nget panning motor acceleration time\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0902,1,array);
					printf("motor acceleration time>>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(23==operation)
				{
					printf("\t\nget panning motor subdivision\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0903,1,array);
                    printf("motor subdivision>>%d\n",array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(24==operation)
				{
					printf("\t\nget panning motor gear\n");
					printf("-----------------------------\n");

                    rc=modbus_read_registers(ctx,0x0904,2,array);
                    printf("get panning motor gear>>%d,%d\n",array[1],array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(25==operation)
				{
					printf("\t\nget panning motor direction\n");
					printf("-----------------------------\n");
                    rc= modbus_read_bits(ctx,0x0900,1,&value);
                    printf("get panning motor direction>>%d\n",value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
                else if(26==operation)
				{
					printf("\t\nget panning motor algorithm\n");
					printf("-----------------------------\n");
                    rc=modbus_read_registers(ctx,0x0906,1,&value);
                    printf("get panning motor algorithm>>%d\n",value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(29==operation)
				{
					printf("\t\ngetting the current pos for renfence point \n");
					printf("-----------------------------\n");
                    rc=modbus_read_input_registers(ctx,0x0900,2,array);
                    printf("getting renfence point>>%d,>%d\n",array[0],array[0]);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}

                else
				{
					printf("input error 0,please input again!\n");
				}
				break;
			}//end case 9
			 case 10:
		    {

				if(7==operation)
				{
					printf("\t\nenable the Zoom motor reset\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0A01,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(8==operation)
				{
					printf("\t\nEmergence stop the zoom Motor \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0A02,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(9==operation)
				{
					printf("\t\nSetting the current pos for renfence point \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0A03,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}

                else if(12==operation)
				{
					printf("\t\nRunning the Zoom Motor by Angle\n");
					printf("-----------------------------\n");
					array[0]=0;
					array[1]=value;
					array[2]=0;
                    rc=modbus_write_registers(ctx,0x0A12,3,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else
				{
                    printf("input error 0,please input again!\n");
				}
				break;


		     }//end case 10
		     /*BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB*/
		    case 11:
		    {

				if(7==operation)
				{
					printf("\t\nenable the Focus motor reset\n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0B01,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(8==operation)
				{
					printf("\t\nEmergence stop the Focus Motor \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0B02,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else if(9==operation)
				{
					printf("\t\nSetting the current pos for renfence point \n");
					printf("-----------------------------\n");
                    rc=modbus_write_bits(ctx,0x0B03,1,&value);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}

                else if(12==operation)
				{
					printf("\t\nRunning the Focus Motor by Angle\n");
					printf("-----------------------------\n");
					array[0]=0;
					array[1]=value;
					array[2]=0;
                    rc=modbus_write_registers(ctx,0x0B12,3,array);
                    if(rc==-1)
                        exit(0);
                    printf("-----------------------------\n");
				}
				else
				{
                    printf("input error 0,please input again!\n");
				}
				break;


		     }//end case 11

			//read data
			default:
			{
				printf(" default read data \n");
				printf("-------------------------------------\n");
				rc=modbus_read_input_registers(ctx,00,10,tab_input_reg);
                if(rc==-1)
				   exit(0);

                for(i=0;i<10;i++)
                {
				    printf("tab_input_register[%d]:%02x\n",i,tab_input_reg[i]);
				}

			     printf("-----------------------------------\n");
			}
		}//switch
	}//while








/**********************************/
/*1111111111111111111111111111111111111111111111111*/
/***********************************/
/* Reads the boolean status of bits and sets the array elements
   in the destination to TRUE or FALSE (single bits).
int modbus_read_bits(modbus_t *ctx, int addr, int nb, uint8_t *dest);
//----->read_io_status( _FC_READ_COILS)   01 */

/*

  {  printf("***Modbus_read_bits()***\n");

     rc=modbus_read_bits(ctx,00,30,tab_bit);
     if(rc==-1)
        exit(0);

     for(i=0;i<30;i++)
     {
        printf("tab_bits[%d]:%02d\n",i,tab_bit[i]);
        }

     printf("\n\n");
   }

*/

/**************************************************/
/*222222222222222222222222222222222222222222222222*/
/**************************************************/
/* Same as modbus_read_bits but reads the remote device input table
int modbus_read_input_bits(modbus_t *ctx, int addr, int nb, uint8_t *dest);
//----->read_io_status( _FC_READ_DISCRETE_INPUTS )02 */

/*

 {
     int value;
     printf("***Modbus_input_read_bits()***\n");

     rc=modbus_read_input_bits(ctx,00,30,tab_input_bit);
     if(rc==-1)
        exit(0);

     for(i=0;i<30;i++)
     {
        printf("tab_input_bit[%d]:%02d\n",i,tab_input_bit[i]);
        }


     value=modbus_get_byte_from_bits(tab_input_bit,0,8);
     printf("value:%d\n",value);

     printf("\n\n");
   }

*/


/**************************************************/
/*333333333333333333333333333333333333333333333333*/
/**************************************************/
/* Reads the holding registers of remote device and put the data into an
   array
int modbus_read_registers(modbus_t *ctx, int addr, int nb, uint16_t *dest);
//------>read_registers(_FC_READ_HOLDING_REGISTERS)03   */

/*

 {
     printf("***Modbus_read_registers()***\n");

     rc=modbus_read_registers(ctx,00,60,tab_reg);
     if(rc==-1)
        exit(0);

     for(i=0;i<60;i++)
     {
        printf("tab_register[%d]:%02d\n",i,tab_reg[i]);
        }

     printf("\n\n");
   }


*/

/**************************************************/
/*4444444444444444444444444444444444444444444444444*/
/**************************************************/
/* Reads the input registers of remote device and put the data into an array
int modbus_read_input_registers(modbus_t *ctx, int addr, int nb, uint16_t *dest);
//------>read_registers(_FC_READ_INPUT_REGISTERS)04   */


/*
{
     printf("***Modbus_read_input_registers()***\n");

     rc=modbus_read_input_registers(ctx,00,30,tab_input_reg);
     if(rc==-1)
        exit(0);

     for(i=0;i<30;i++)
     {
        printf("tab_input_register[%d]:%02d\n",i,tab_input_reg[i]);
        }

     printf("\n\n");
   }
*/



/**************************************************/
/*55555555555555555555555555555555555555555555555555*/
/**************************************************/
/* Turns ON or OFF a single bit of the remote device
int modbus_write_bit(modbus_t *ctx, int coil_addr, int status);
//----->write_single(_FC_WRITE_SINGLE_COIL )05   */

/*

{
     printf("***modbus_write_bit()***\n");

     rc=modbus_write_bit(ctx,00,1);
     if(rc==-1)
        exit(0);

     rc=modbus_read_bits(ctx,00,1,tab_bit);
     if(rc==-1)
        exit(0);
     printf("**after writing the value 1,read the value is %d***\n",tab_bit[0]);

     rc=modbus_write_bit(ctx,00,0);
     if(rc==-1)
        exit(0);

     rc=modbus_read_bits(ctx,00,1,tab_bit);
     if(rc==-1)
        exit(0);
     printf("**after writing the value 0 again,read the value is %d***\n",tab_bit[0]);

     printf("\n\n");

}


*/


/**************************************************/
/*6666666666666666666666666666666666666666666666*/
/**************************************************/
/* Writes a value in one register of the remote device
int modbus_write_register(modbus_t *ctx, int reg_addr, int value);
//----->write_single( _FC_WRITE_SINGLE_REGISTER)06*/

/*

{
     printf("***modbus_write_register()***\n");

     rc=modbus_write_register(ctx,0x1111,0x1234); //65536=0xffff
     if(rc==-1)
        exit(0);
     printf("***modbus read the value after write***\n");
     rc=modbus_read_registers(ctx,00,1,tab_reg);
     if(rc==-1)
        exit(0);
     printf("**after writing the value ,read the value is 0x%2x**\n",tab_reg[0]);




     rc=modbus_write_register(ctx,00,0x12);
     if(rc==-1)
        exit(0);

     rc=modbus_read_registers(ctx,00,1,tab_reg);
     if(rc==-1)
        exit(0);
     printf("**after writing the value x4312 again,read the value is 0x%x***\n",tab_reg[0]);

     printf("\n\n");

}
*/

/**************************************************/
/*fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff*/
/**************************************************/
/* Write the bits of the array in the remote device
int modbus_write_bits(modbus_t *ctx, int addr, int nb, const uint8_t *data);
//-------------->ctx->backend->build_request_basis(_FC_WRITE_MULTIPLE_COILS)0f

*/
/*
{
     printf("***modbus_write_bits()***\n");

     rc=modbus_write_bits(ctx,00,6,tab_send_bit);
     if(rc==-1)
        exit(0);

     rc=modbus_read_bits(ctx,00,6,tab_input_bit);
     if(rc==-1)
        exit(0);
     printf("**after writing the value 1,read the value is %d***\n",modbus_get_byte_from_bits(tab_input_bit,0,5));

	 tab_send_bit[0]=2;
	 tab_send_bit[1]=0;
	 tab_send_bit[2]=3;
	 tab_send_bit[3]=0;
	 tab_send_bit[4]=4;
	 tab_send_bit[5]=0;
	 tab_send_bit[6]=6;
	 tab_send_bit[7]=0;
	 tab_send_bit[8]=5;
	 tab_send_bit[9]=0;
	 tab_send_bit[10]=7;

     rc=modbus_write_bits(ctx,00,16,tab_send_bit);
     if(rc==-1)
        exit(0);

     rc=modbus_read_bits(ctx,00,16,tab_input_bit);
     if(rc==-1)
        exit(0);
     printf("**after writing the value 0 again,read the value is %d***\n",modbus_get_byte_from_bits(tab_input_bit,0,6));

     printf("\n\n");

}

*/

/**************************************************/
/*101010101010101010101010101010101010101010101010*/
/**************************************************/
/* Write the values from the array to the registers of the remote device
int modbus_write_registers(modbus_t *ctx, int addr, int nb, const uint16_t *data);
//---------->ctx->backend->build_request_basis(_FC_WRITE_MULTIPLE_REGISTERS)10  */
/*
{

     printf("***modbus_write_registers()***\n");
     tab_send_reg[0]=0x01;
	 tab_send_reg[1]=0x1234;
     rc=modbus_write_registers(ctx,0x0101,2,tab_send_reg);
     if(rc==-1)
         exit(0);
	printf("write after\n");
     usleep(10000);
	printf("read before\n");
     rc=modbus_read_registers(ctx,256,2,tab_reg);
     if(rc==-1)
        exit(0);
     for(i=0;i<5;i++)
         printf("****read the value tab_reg[%d]:%x\n**",i,tab_reg[i]);
     printf("\n\n");

}


*/

/**************************************************/
/*99999999999999999999999999999999999999999999999*/
/**************************************************/
/* Write multiple registers from src array to remote device and read multiple
   registers from remote device to dest array.
int modbus_write_and_read_registers(modbus_t *ctx, int write_addr, int write_nb,const uint16_t *src, int read_addr, int read_nb, uint16_t *dest);   */
 /*

 {
    printf("***modbus_write_and_read_registers***\n");
    rc = modbus_write_and_read_registers(ctx,00,8,tab_send_reg,00,8,tab_reg);
    for(i=0;i<8;i++)
         printf("****read the value tab_reg[%d]:0x%04x****\n",i,tab_reg[i]);

     printf("\n\n");

  }

  */
/**************************************************/
/**************************************************/
/**************************************************/

/*****************************************************/
/*    printf("READ BITS\n\n");

    nb_points = MODBUS_MAX_READ_BITS;
    start = gettime_ms();

   // for (i=0; i<n_loop; i++) {
   //        rc = modbus_read_bits(ctx, 0, nb_points, tab_bit);
    for (i=0; i<5; i++) {
        rc = modbus_read_bits(ctx, 112,42, tab_bit);
	sleep(2);
        if (rc == -1) {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            return -1;
        }
    }

    rc = modbus_read_bits(ctx, 0,14, tab_bit);
    for(i=0;i<44;i++){
        printf("tab_bit[%d] value: %x\n",i,tab_bit[i]);
        }
    end = gettime_ms();
    elapsed = end - start;

    rate = (n_loop * nb_points) * G_MSEC_PER_SEC / (end - start);
    printf("Transfert rate in points/seconds:\n");
    printf("* %d points/s\n", rate);
    printf("\n");

    bytes = n_loop * (nb_points / 8) + ((nb_points % 8) ? 1 : 0);
    rate = bytes / 1024 * G_MSEC_PER_SEC / (end - start);
    printf("Values:\n");
    printf("* %d x %d values\n", n_loop, nb_points);
    printf("* %.3f ms for %d bytes\n", elapsed, bytes);
    printf("* %d KiB/s\n", rate);
    printf("\n");

    // TCP: Query and reponse header and values
    bytes = 12 + 9 + (nb_points / 8) + ((nb_points % 8) ? 1 : 0);
    printf("Values and TCP Modbus overhead:\n");
    printf("* %d x %d bytes\n", n_loop, bytes);
    bytes = n_loop * bytes;
    rate = bytes / 1024 * G_MSEC_PER_SEC / (end - start);
    printf("* %.3f ms for %d bytes\n", elapsed, bytes);
    printf("* %d KiB/s\n", rate);
    printf("\n\n");
*/
 /***************************************************/
/*	printf("READ INPUT REGISTER\n\n");
	rc = modbus_read_input_bits(ctx,0x00,24,tab_input_bit);
	if(rc == -1)
	{
		printf("dddddddd\n");
           fprintf(stderr, "%s\n", modbus_strerror(errno));
	   printf("error can not read input bits\n");
            return -1;

	}
*/
/*
    printf("READ REGISTERS\n\n");

    nb_points = MODBUS_MAX_READ_REGISTERS;
    //start = gettime_ms();
    for (i=0; i<100; i++) {

    gettimeofday(&mystart,NULL);
        rc = modbus_read_registers(ctx, 0, 2, tab_reg);
        if (rc == -1) {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            return -1;
        }
    gettimeofday(&myend,NULL);
    printf("Can Response Time:\n");
    printf("The elapse time\\ms :%d\n", myend.tv_sec-mystart.tv_sec);
    printf("The elapse time\\us :%d\n",myend.tv_usec-mystart.tv_usec);
    }
    //end = gettime_ms();
    //elapsed = end - start;
    //printf("Can Response Time:%d\n",elapsed);
    rate = (n_loop * nb_points) * G_MSEC_PER_SEC / (end - start);
    printf("Transfert rate in points/seconds:\n");
    printf("* %d registers/s\n", rate);
    printf("\n");

    bytes = n_loop * nb_points * sizeof(uint16_t);
    rate = bytes / 1024 * G_MSEC_PER_SEC / (end - start);
    printf("Values:\n");
    printf("* %d x %d values\n", n_loop, nb_points);
    printf("* %.3f ms for %d bytes\n", elapsed, bytes);
    printf("* %d KiB/s\n", rate);
    printf("\n");

    // TCP:Query and reponse header and values
    bytes = 12 + 9 + (nb_points * sizeof(uint16_t));
    printf("Values and TCP Modbus overhead:\n");
    printf("* %d x %d bytes\n", n_loop, bytes);
    bytes = n_loop * bytes;
    rate = bytes / 1024 * G_MSEC_PER_SEC / (end - start);
    printf("* %.3f ms for %d bytes\n", elapsed, bytes);
    printf("* %d KiB/s\n", rate);
    printf("\n\n");

*/
/***********************************************/
/*
    printf("READ AND WRITE REGISTERS\n\n");

    nb_points = MODBUS_MAX_RW_WRITE_REGISTERS;
    start = gettime_ms();
    for (i=0; i<n_loop; i++) {
        rc = modbus_write_and_read_registers(ctx,
                                             0, nb_points, tab_reg,
                                             0, nb_points, tab_reg);
        if (rc == -1) {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            return -1;
        }
    }
    end = gettime_ms();
    elapsed = end - start;

    rate = (n_loop * nb_points) * G_MSEC_PER_SEC / (end - start);
    printf("Transfert rate in points/seconds:\n");
    printf("* %d registers/s\n", rate);
    printf("\n");

    bytes = n_loop * nb_points * sizeof(uint16_t);
    rate = bytes / 1024 * G_MSEC_PER_SEC / (end - start);
    printf("Values:\n");
    printf("* %d x %d values\n", n_loop, nb_points);
    printf("* %.3f ms for %d bytes\n", elapsed, bytes);
    printf("* %d KiB/s\n", rate);
    printf("\n");

    // TCP:Query and reponse header and values
    bytes = 12 + 9 + (nb_points * sizeof(uint16_t));
    printf("Values and TCP Modbus overhead:\n");
    printf("* %d x %d bytes\n", n_loop, bytes);
    bytes = n_loop * bytes;
    rate = bytes / 1024 * G_MSEC_PER_SEC / (end - start);
    printf("* %.3f ms for %d bytes\n", elapsed, bytes);
    printf("* %d KiB/s\n", rate);
    printf("\n");
*/





    /* Free the memory */
    free(tab_bit);
    free(tab_reg);

    /* Close the connection */
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
