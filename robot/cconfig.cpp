#include "cconfig.h"
#include <iostream>

CConfig::CConfig()
{
    //Init();
}
CConfig::~CConfig()
{
	std::cout<<"~CConfig()"<<std::endl;
}

/*结点的值，皆为16进制，通过GetValue成员函数转成10进制*/
/************************************************************************/
/*  （1）生成配置文件，并为系统提供初始化运行参数                       */
/*  （2）如果是多个元素表示一个单项，则使用后缀为0-n的形式表示Key       */
/*  （3）为了扩展的需求，Key对应的Value皆用16进制数表示                 */
/*  （4）此函数最终将用本地文件替换掉                                   */
/*                                                                      */
/************************************************************************/
void CConfig::Init()
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_pi,doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(root);
	rapidxml::xml_node<>* node =   doc.allocate_node(rapidxml::node_element,"config","infomation");
	doc.append_node(node);
	//sys
	rapidxml::xml_node<>* sys =   doc.allocate_node(rapidxml::node_element,"sys",NULL);
	sys->append_node(doc.allocate_node(rapidxml::node_element,"name","sys"));
	sys->append_node(doc.allocate_node(rapidxml::node_element,"cip4","0"));   //controller ip
	sys->append_node(doc.allocate_node(rapidxml::node_element,"cip3","7F"));  //127
	sys->append_node(doc.allocate_node(rapidxml::node_element,"cip2","0"));
	sys->append_node(doc.allocate_node(rapidxml::node_element,"cip1","0"));
	sys->append_node(doc.allocate_node(rapidxml::node_element,"cip0","1"));

//	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip4","7F")); //master ip 127
//	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip3","0"));
//	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip2","0"));
//	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip1","1"));
    sys->append_node(doc.allocate_node(rapidxml::node_element,"id","2"));
    sys->append_node(doc.allocate_node(rapidxml::node_element,"mip4","C0"));  //192
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip3","A8"));  //168
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip2","0"));   //0
#ifndef DLP_ARM_LINUX
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip1","A"));   //10
#else
    sys->append_node(doc.allocate_node(rapidxml::node_element,"mip1","D9"));   //217
#endif // ARM_LINUX_DEGUG
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mip0","5DE")); //1502
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mac5","FF"));  //FF
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mac4","EE"));  //EE
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mac3","DD"));  //DD
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mac2","CC"));  //CC
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mac1","BB"));  //BB
	sys->append_node(doc.allocate_node(rapidxml::node_element,"mac0","AA"));  //AA
    sys->append_node(doc.allocate_node(rapidxml::node_element,"nameno","2")); //name=robot no=1-127

	sys->append_node(doc.allocate_node(rapidxml::node_element,"os","464"));  //1124
	sys->append_node(doc.allocate_node(rapidxml::node_element,"ver","464")); //1124
	sys->append_node(doc.allocate_node(rapidxml::node_element,"ft2","7DE")); //2014
	sys->append_node(doc.allocate_node(rapidxml::node_element,"ft1","B"));   //11
	sys->append_node(doc.allocate_node(rapidxml::node_element,"ft0","18"));  //24
	sys->append_node(doc.allocate_node(rapidxml::node_element,"model3","44"));//D==68
	sys->append_node(doc.allocate_node(rapidxml::node_element,"model2","4C"));//L==76
	sys->append_node(doc.allocate_node(rapidxml::node_element,"model1","50"));//P==80
	sys->append_node(doc.allocate_node(rapidxml::node_element,"model0","123"));
	sys->append_node(doc.allocate_node(rapidxml::node_element,"SN0","44c"));
	sys->append_node(doc.allocate_node(rapidxml::node_element,"SN1","b"));
	sys->append_node(doc.allocate_node(rapidxml::node_element,"P809","45")); //P809 ==69//indicator led
	sys->append_node(doc.allocate_node(rapidxml::node_element,"P810","44")); //P810==68
	sys->append_node(doc.allocate_node(rapidxml::node_element,"P815","2f"));  //P815==47
	sys->append_node(doc.allocate_node(rapidxml::node_element,"P816","2e"));  //P816==46
	sys->append_node(doc.allocate_node(rapidxml::node_element,"P817","1b"));  //P817==27
	sys->append_node(doc.allocate_node(rapidxml::node_element,"P818","41"));  //P818==65
	sys->append_node(doc.allocate_node(rapidxml::node_element,"P826","3d"));  //P826==61
	node->append_node(sys);

	//lens
	//focus motor
	rapidxml::xml_node<>* focusmotor =doc.allocate_node(rapidxml::node_element,"focusmotor",NULL);
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"name","focusmotor"));

	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmpin","342"));//834
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmvalue","0"));

	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"period1","3B9A"));//
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"period0","CA00"));
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"duty1","1DCD"));//
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"duty0","6500"));
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"polarity","1"));
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"run","0"));

	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"max","0"));
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"min","0"));
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"acc","0"));
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"subdivision","0"));
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","38"));//56
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","1"));
    focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"curve","0"));//0 CTestCurve
    focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"rotation","0"));//0 CTestRotation
    focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"type","4"));//0 CTestCurve
    focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"model","4"));//0 CTestRotation

	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"dirpin","9"));//P833
	focusmotor->append_node(doc.allocate_node(rapidxml::node_element,"dirvalue","0"));
	node->append_node(focusmotor);

	//lens focus sensor
	rapidxml::xml_node<>* focussensor =doc.allocate_node(rapidxml::node_element,"focussensor",NULL);
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"name","focussensor"));
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"id","1")); //0x01
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"type","1"));//
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"mode","1"));//
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"baud1","0"));//19200
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"baud0","4B00"));
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"databit","8"));
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"stopbit","0"));//1
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"flowbit","0"));
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"paritybit","0"));
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"origin1","0"));
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"origin0","0"));
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","63"));//99
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","11"));  //17
	focussensor->append_node(doc.allocate_node(rapidxml::node_element,"bits","10"));//16
	node->append_node(focussensor);

	//lens zoom motor
	rapidxml::xml_node<>* zoommotor =doc.allocate_node(rapidxml::node_element,"zoommotor",NULL);
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"name","zoommotor"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmpin","344"));//836
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmvalue","0"));

	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"period1","3B9A"));//
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"period0","CA00"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"duty1","1DCD"));//
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"duty0","6500"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"polarity","1"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"run","0"));

	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"max","0"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"min","0"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"acc","0"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"subdivision","0"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","1"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","1"));
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"curve","0")); //0 TestCurve
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"rotation","0"));//0 TestRotation
    zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"type","3")); //3 ZOOM
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"model","3"));//

	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"dirpin","8"));//P835
	zoommotor->append_node(doc.allocate_node(rapidxml::node_element,"dirvalue","0"));
	node->append_node(zoommotor);

	//sensor
	rapidxml::xml_node<>* zoomsensor =doc.allocate_node(rapidxml::node_element,"zoomsensor",NULL);
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"name","zoomsensor"));
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"id","2")); //0x02
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"type","2"));//
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"mode","2"));//
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"baud1","0"));//19200
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"baud0","4B00"));
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"type","2"));//
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"mode","2"));//
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"databit","8"));
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"stopbit","0"));//1
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"flowbit","0"));
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"paritybit","0"));
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","1"));
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","1"));
	zoomsensor->append_node(doc.allocate_node(rapidxml::node_element,"bits","10"));//16


	node->append_node(zoomsensor);

	//pan motor
	rapidxml::xml_node<>* panmotor =   doc.allocate_node(rapidxml::node_element,"panmotor",NULL);
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"name","0"));
    panmotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmpin","32C"));//PIN 812
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmvalue","0"));
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"origin1","0"));
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"origin0","0"));
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"max","2E4"));//740
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"min","8C"));//140
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"acc","12c"));//300
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"subdivision","0"));//128
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","38"));//37-0x25:11-0x17//56-0x38:1<==15:28x1:10x33:99
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","1"));//17
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"curve","2"));    //0 CTestCurve
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"rotation","0")); //0 CTestRotation
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"type","1"));    //0 CTestCurve
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"model","1")); //0 CTestRotation

	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"dirvalue","2"));
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"dirpin","1A"));//26
	panmotor->append_node(doc.allocate_node(rapidxml::node_element,"dirvalue","0"));//0
	node->append_node(panmotor);

	//pan sensor
	rapidxml::xml_node<>* pansensor =   doc.allocate_node(rapidxml::node_element,"pansensor",NULL);
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"name","pansensor"));
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"id","21")); //0x21==31
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"type","2"));//
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"mode","22"));//34
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"baud1","F"));//1M
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"baud0","4240"));
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"origin1","0"));
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"origin0","0"));
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","63"));//37-0x25:11-0x17//99-0x63:17-0x11
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","11")); //17
	pansensor->append_node(doc.allocate_node(rapidxml::node_element,"bits","E"));//14
	node->append_node(pansensor);

	//pan origin
	rapidxml::xml_node<>* panorigin =   doc.allocate_node(rapidxml::node_element,"panorigin",NULL);
	panorigin->append_node(doc.allocate_node(rapidxml::node_element,"name","panorigin"));
	panorigin->append_node(doc.allocate_node(rapidxml::node_element,"pin","17"));//P813==23
	node->append_node(panorigin);

	//tilt motor
	rapidxml::xml_node<>* tiltmotor =   doc.allocate_node(rapidxml::node_element,"tiltmotor",NULL);
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"name","1"));
    tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmpin","34E"));//PIN 846
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"pwmvalue","0"));
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"origin1","0"));
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"origin0","0"));
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"max","c"));
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"min","2"));
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"acc","12c"));//acceleration300
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"subdivision","7"));//128
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","26"));//gear numerator38
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","E"));// gear denominator14
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"curve","0"));   //0 CTestCurve
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"rotation","0"));//0 CTestRotation
    tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"type","2"));   //0 CTestCurve
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"model","2"));//0 CTestRotation
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"direction","1"));
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"dirpin","49"));//73
	tiltmotor->append_node(doc.allocate_node(rapidxml::node_element,"dirvalue","0"));//0
	node->append_node(tiltmotor);

	//tilt sensor
	rapidxml::xml_node<>* tiltsensor =   doc.allocate_node(rapidxml::node_element,"tiltsensor",NULL);
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"name","tiltsensor"));
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"id","20"));//0x20
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"type","2"));
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"mode","23"));
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"baud1","F"));//1M
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"baud0","4240"));
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"origin1","0"));
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"origin0","0"));
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"gear1","30"));//30
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"gear0","a"));//10
	tiltsensor->append_node(doc.allocate_node(rapidxml::node_element,"bits","E"));
	node->append_node(tiltsensor);

	//tilt origin
	rapidxml::xml_node<>* tiltorigin =   doc.allocate_node(rapidxml::node_element,"tiltorigin",NULL);
	tiltorigin->append_node(doc.allocate_node(rapidxml::node_element,"name","tiltorigin"));
	tiltorigin->append_node(doc.allocate_node(rapidxml::node_element,"pin","2F"));//P815==47
	node->append_node(tiltorigin);

	std::ofstream config("config.xml");
	config << doc;
}

/*
*@brief  从配置文件中得到数据
*@param  参数1表示设备节点，参数2表示功能节点
*@return 返回正整数：获取到的节点值
         返回-1：配置文件有误
		 返回-2：设备节点不正确或不存在
		 返回-3：功能节点不正确或不存在
*/
uint16_t CConfig::GetValue( const std::string &device_node,const std::string &sub_node)
{
	rapidxml::file<> fdoc("config.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(fdoc.data());

	rapidxml::xml_node<>* root=doc.first_node();
	if(0==root)
	{
		return -1;
	}
	rapidxml::xml_node<>* device=root->first_node(device_node.c_str());
	if(0==device)
	{
		return -2;
	}
	rapidxml::xml_node<>* app=device=device->first_node(sub_node.c_str());
	if(0==app)
	{
		return -3;
	}
	return Str2Hex(app->value());
}

/*
*@brief  重新设置已有节点的值
*@param  参数1表示设备节点，参数2表示功能节点，参数3表示要设置的值
*@return 返回0：设置正确或设置完成
         返回-1：配置文件有误
		 返回-2：设备节点不正确或不存在
		 返回-3：功能节点不正确或不存在
*/
int CConfig::SetValue(const std::string &device_node,const std::string &sub_node,const uint16_t &value)
{
	char str[6]={'\0'};
	rapidxml::file<> fdoc("config.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(fdoc.data());

	rapidxml::xml_node<>* root=doc.first_node();    //root --->config
	if(0==root)
	{
		return -1;
	}
	rapidxml::xml_node<>* device=root->first_node(device_node.c_str());
	if(0==device)
	{
		return -2;
	}
	rapidxml::xml_node<>* app=device->first_node(sub_node.c_str());
	if(0==app)
	{
		return -3;
	}

	device->remove_node(app);
	sprintf(str,"%d",value);
	//rapidxml::xml_node<>* new_node = doc.allocate_node(rapidxml::node_element,app_node.c_str(),"0x30");
	rapidxml::xml_node<>* new_node = doc.allocate_node(rapidxml::node_element,sub_node.c_str(),str);
	device->append_node(new_node);

	std::ofstream config("config.xml");
	config << doc;
	return 0;
}


void CConfig::PrintXml(const std::string &file_name)
{
	PrintInfo(file_name);
}

void CConfig::PrintInfo(const std::string &file_name)
{
	rapidxml::file<> fdoc(file_name.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(fdoc.data());


	std::string info;
	rapidxml::print(std::back_inserter(info), doc, 0);
	std::cout<<info<<std::endl;

}


int CConfig::Str2Hex(char *num_str)
{
    int num_hex=0;
    while(*num_str)
    {
        if(*num_str>='0' && *num_str<='9') num_hex=num_hex*16+(*num_str-'0');
        else if(*num_str>='a' && *num_str<='f')num_hex=num_hex*16+*num_str-'a'+10;
        else if(*num_str>='A' && *num_str<='Z')num_hex=num_hex*16+*num_str-'A'+10;
        else return 0;

    num_str++;
    }

    return num_hex;
}
