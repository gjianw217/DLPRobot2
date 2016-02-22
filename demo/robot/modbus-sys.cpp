#include "../../dlp/dlp.h"

#include "../../utils/cdelay.h"
#include "../../utils/casynchrtimer.h"
#include "../../network/cdata-mapping.h"
#include "../../robot/cconfig.h"
#include "../../robot/crobot.h"
//#include "../../robot/csyspulses.h"
//#include "../../robot/cdevpulses.h"
#include "../../robot/csystem.h"
#include "../../network/cmodbus.h"

#include "../../task/local/crefresh.h"
#include "../../task/cfocustask.h"
#include "../../task/cpantask.h"
#include "../../task/ctilttask.h"
#include "../../task/czoomtask.h"
#include "../../task/csystask.h"
#include "../../utils/ctaskthread.h"
#include "../../network/cnetwork.h"

//#include "../utils/csynchro2.h"
PCSysTask psys_task(new CSysTask());
PCSystem  psystem(new CSystem());
/********************************************/

void SyncHandler(int signum)
{
    //struct timeval start;
    //gettimeofday(&start,0);
    //printf("AF..%d..%d\n",start.tv_sec,start.tv_usec);

    //collection the data  of the coders
    std::cout<<"------------------------------------------------------------------------------------------------------"<<std::endl;
    psystem->CollectSysData();
    psystem->ConvertSysPulse();
    psystem->AmendSysPulse();
    psystem->ControlSysMotion();


    //update the drivers pulses at the frame
   /// pdev_pulses->ReadDevPulsesCurve(const DLPDevPulse &type,const uint8_t len,uint32_t *des)
    ///psys_pulses->WritePulseGroup(const uint32_t *src,const uint8_t &len);
    //driver the step motor movement
   /// psys_pulses->RunPulseGroups();


}
void SyncStart()
{
#ifdef DLP_EXT_SYNC

	int flag,fd;
    signal(SIGIO,SyncHandler);
  #ifdef DLP_ARM_LINUX
    fd = open("/dev/gpiop923",O_RDWR);
    if (fd < 0)
    {
        printf("open sync driver dev error\n");
    }
    fcntl(fd, F_SETOWN, getpid());
    flag = fcntl(fd,F_GETFL);
    fcntl(fd,F_SETFL,flag | FASYNC);
    printf("Startup Sync\n");
   #endif // DLP_ARM_LINUX
#endif // DLP_EXT_SYNC
}


/*******************************************/
void TestServer()
{

	PCConfig pconf(new CConfig());
	pconf->Init();

	PCDataMapping pdatamapping(new CDataMapping(pconf));
	PCRobot probot(new CRobot(pdatamapping));
	probot->Init();

	PCRefresh prefresh(new CRefresh());
	prefresh->SetConfig(pconf);
	prefresh->SetDataMapping(pdatamapping);

	PCModbus pmodbus(new CModbus(pdatamapping));

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	CSuspendThread mainThreadLoop;

//	PCSysTask psys_task(new CSysTask()); //define main external
	psys_task->SetRobot(probot);
	psys_task->SetDataMapping(pdatamapping);//must
	psys_task->SetRefresh(prefresh);
	//psys_task->Init();                      //init the all kinds of devices
	psys_task->SetSystem(psystem);
	PCTaskThread psys_thread(new CTaskThread());
	psys_thread->SetTask(boost::bind(&CSysTask::ExecTask,psys_task));

	PCFocusTask pfocus_task(new CFocusTask());
	pfocus_task->SetRobot(probot);;
	pfocus_task->SetRefresh(prefresh);
	pfocus_task->Init();
	PCTaskThread pfocus_thread(new CTaskThread());
	pfocus_thread->SetTask(boost::bind(&CFocusTask::ExecTask,pfocus_task));

	PCZoomTask pzoom_task(new CZoomTask());
	pzoom_task->SetRobot(probot);;
	pzoom_task->SetRefresh(prefresh);
	pzoom_task->Init();;
	PCTaskThread pzoom_thread(new CTaskThread());
	pzoom_thread->SetTask(boost::bind(&CZoomTask::ExecTask,pzoom_task));

	PCPanTask ppan_task(new CPanTask());
	ppan_task->SetRobot(probot);
	ppan_task->SetRefresh(prefresh);
	ppan_task->Init();
	PCTaskThread ppan_thread(new CTaskThread());
	ppan_thread->SetTask(boost::bind(&CPanTask::ExecTask,ppan_task));

	PCTiltTask ptilt_task(new CTiltTask());
	ptilt_task->SetRobot(probot);;
	ptilt_task->SetRefresh(prefresh);
	ptilt_task->Init();;
	PCTaskThread ptilt_thread(new CTaskThread());
	ptilt_thread->SetTask(boost::bind(&CTiltTask::ExecTask,ptilt_task));

	/*ÅäÖÃÂçÄ£¿é*/
	PCNetwork pnet(new CNetwork());                          /*<³õÊŒ»¯ÍøÂçÄ£¿é*/
	pnet->SetModbus(pmodbus);                               /*<ÉèÖÃModbusÄ£¿é£¬ÓÃÀŽÓëÉÏÎ»»úÍšÐÅ*/
	pnet->SetSysTask(psys_task);                    /*<ÉèÖÃ±àÂëÆ÷ÈÎÎñ¶ÔÏó£¬ÒÔ·œ±ãŽ«µÝÐÂœÓÊÕµœµÄÃüÁî·â×°Ìå*/
	pnet->SetSysThread(psys_thread);                  /*<ÉèÖÃ±àÂëÆ÷Ïß³Ì£¬ÒÔ·œ±ã¿ªÆô±àÂëÆ÷ÈÎÎñÏß³Ì*/
	pnet->SetFocusTask(pfocus_task);
	pnet->SetFocusThread(pfocus_thread);
	pnet->SetZoomTask(pzoom_task);
	pnet->SetZoomThread(pzoom_thread);
	pnet->SetPanTask(ppan_task);
	pnet->SetPanThread(ppan_thread);
	pnet->SetTiltTask(ptilt_task);
	pnet->SetTiltThread(ptilt_thread);

	pnet->Init(5);
	PCTaskThread pnet_thread(new CTaskThread());             /*<³õÊŒ»¯Ïß³ÌÄ£¿é*/
	pnet_thread->SetTask(boost::bind(&CNetwork::Run,pnet)); /*<ÉèÖÃÍøÂçÏß³Ì*/
 //   pnet_thread->SetTask(boost::bind(&CNetwork::Test,pnet)); /*<ÉèÖÃÍøÂçÏß³Ì*/
	delays(10); /*<ºÜÖØÒª*/
	pnet_thread->SigTask();

#ifdef DLP_EXT_SYNC
    SyncStart();

#elif DLP_TIMER_SYNC
    CAsyncTimer timer(3);
    timer.SetTimer(boost::bind(&CSysTask::CollectSysData,psys_task));;
    timer.Run();

#endif // DLP_EXT_SYNC
	/***/

    mainThreadLoop.Wait();
 #ifdef DLP_TIMER_SYNC
    timer.Stop();
 #endif // DLP_TIMER_SYNC

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	psys_thread->Close();
	pfocus_thread->Close();
	pzoom_thread->Close();
	ppan_thread->Close();
	ptilt_thread->Close();
	pnet_thread->Close();

}

/*******************************************/
void TestServer1() /*Test SensorCounter and Feedback Control Algorithm*/
{
	PCConfig pconf(new CConfig());
	pconf->Init();

	PCDataMapping pdatamapping(new CDataMapping(pconf));
	PCRobot probot(new CRobot(pdatamapping));
	probot->Init();

	PCRefresh prefresh(new CRefresh());
	prefresh->SetConfig(pconf);
	prefresh->SetDataMapping(pdatamapping);

	PCModbus pmodbus(new CModbus(pdatamapping));

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	CSuspendThread mainThreadLoop;

	PCSysTask psys_task(new CSysTask()); //define main external
	psys_task->SetDataMapping(pdatamapping);//must
	psys_task->SetRobot(probot);
	psys_task->SetRefresh(prefresh);
	psys_task->Init();                      //init the all kinds of devices
	PCTaskThread psys_thread(new CTaskThread());
	psys_thread->SetTask(boost::bind(&CSysTask::ExecTask,psys_task));

	PCPanTask ppan_task(new CPanTask());
	ppan_task->SetRobot(probot);
	ppan_task->SetRefresh(prefresh);
	ppan_task->Init();
	PCTaskThread ppan_thread(new CTaskThread());
	ppan_thread->SetTask(boost::bind(&CPanTask::ExecTask,ppan_task));

	PCFocusTask pfocus_task(new CFocusTask());
	pfocus_task->SetRobot(probot);;
	pfocus_task->SetRefresh(prefresh);
	pfocus_task->Init();
	PCTaskThread pfocus_thread(new CTaskThread());
	pfocus_thread->SetTask(boost::bind(&CFocusTask::ExecTask,pfocus_task));

	/*ÅäÖÃÂçÄ£¿é*/
	PCNetwork pnet(new CNetwork());                          /*<³õÊŒ»¯ÍøÂçÄ£¿é*/
	pnet->SetModbus(pmodbus);                               /*<ÉèÖÃModbusÄ£¿é£¬ÓÃÀŽÓëÉÏÎ»»úÍšÐÅ*/
	pnet->SetSysTask(psys_task);                    /*<ÉèÖÃ±àÂëÆ÷ÈÎÎñ¶ÔÏó£¬ÒÔ·œ±ãŽ«µÝÐÂœÓÊÕµœµÄÃüÁî·â×°Ìå*/
	pnet->SetSysThread(psys_thread);                  /*<ÉèÖÃ±àÂëÆ÷Ïß³Ì£¬ÒÔ·œ±ã¿ªÆô±àÂëÆ÷ÈÎÎñÏß³Ì*/
	pnet->SetFocusTask(pfocus_task);
	pnet->SetFocusThread(pfocus_thread);
	pnet->SetPanTask(ppan_task);
	pnet->SetPanThread(ppan_thread);
	pnet->Init(5);
	PCTaskThread pnet_thread(new CTaskThread());             /*<³õÊŒ»¯Ïß³ÌÄ£¿é*/
	pnet_thread->SetTask(boost::bind(&CNetwork::Run,pnet)); /*<ÉèÖÃÍøÂçÏß³Ì*/
	//pnet_thread->SetTask(boost::bind(&CNetwork::Test,pnet)); /*<ÉèÖÃÍøÂçÏß³Ì*/


	delays(1); /*<ºÜÖØÒª*/
	pnet_thread->SigTask();

#ifdef DLP_EXT_SYNC
    SyncStart();

#elif DLP_TIMER_SYNC
    CAsyncTimer timer(1);
    timer.SetTimer(boost::bind(&CSysTask::CollectSysData,psys_task));;
    timer.Run();

#endif // DLP_EXT_SYNC
	/***/

    mainThreadLoop.Wait();
 #ifdef DLP_TIMER_SYNC
    timer.Stop();
 #endif // DLP_TIMER_SYNC

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

//	psys_thread->Close();
//	pfocus_thread->Close();
//	pnet_thread->Close();

}
/**********************************************************************************/
void TestServer0()
{
    std::cout<<"Hellworld"<<std::endl;

	PCNetwork pnet(new CNetwork());                          /*<³õÊŒ»¯ÍøÂçÄ£¿é*/
CSuspendThread mainThreadLoop;
	PCTaskThread pnet_thread(new CTaskThread());             /*<³õÊŒ»¯Ïß³ÌÄ£¿é*/
	pnet_thread->SetTask(boost::bind(&CNetwork::Test,pnet)); /*<ÉèÖÃÍøÂçÏß³Ì*/
	delays(3); /*<ºÜÖØÒª*/
	pnet_thread->SigTask();
mainThreadLoop.Wait();

}

void TestServer2()
{

	PCConfig pconf(new CConfig());
	pconf->Init();

	PCDataMapping pdatamapping(new CDataMapping(pconf));
	PCModbus pmodbus(new CModbus(pdatamapping));
    PCNetwork pnet(new CNetwork());                          /*<初始化网络模块*/
	pnet->SetModbus(pmodbus);                               /*<设置Modbus模块，用来与上位机通信*/


	pnet->Init(5);
	PCTaskThread pnet_thread(new CTaskThread());             /*<初始化线程模块*/
	pnet_thread->SetTask(boost::bind(&CNetwork::Run,pnet)); /*<设置网络线程*/
	delays(1); ///*<很重要*/
	pnet_thread->SigTask();

	while(1);


}






void TestModbusNet()
{

	PCConfig pconf(new CConfig());
	pconf->Init();

	PCDataMapping pdatamapping(new CDataMapping(pconf));
	PCRobot probot(new CRobot(pdatamapping));
	probot->Init();

	PCRefresh prefresh(new CRefresh());
	prefresh->SetConfig(pconf);
	prefresh->SetDataMapping(pdatamapping);

	PCModbus pmodbus(new CModbus(pdatamapping));

	while(1);


}
