###########################################
# Main Makefile
#                            By Guo Jianwei
#                                2015-10-12
#                  EMAIL: gjianw217@163.com
###########################################
OBJ=main.o\
	demo/drivers/gpio-output.o\
	demo/devices/coders.o\
	demo/devices/motors.o\
	demo/network/modbus-init.o\
	demo/robot/robot-init.o\
	demo/robot/modbus-sys.o\
	devices/motors/algorithm/irotation.o\
	devices/motors/algorithm/ctestrotation.o\
	devices/motors/algorithm/crotation360.o\
	devices/motors/algorithm/crotation720.o\
	devices/motors/algorithm/crotationany.o\
	devices/motors/algorithm/icurve.o\
	devices/motors/algorithm/ctestcurve.o\
	devices/motors/algorithm/clcurve.o\
	devices/motors/algorithm/ctcurve.o\
	devices/motors/algorithm/cscurve.o\
	devices/motors/algorithm/cbeziercurve.o\
	devices/motors/cdirection.o\
	devices/motors/correction/camend.o\
	devices/motors/correction/cpwmfeedbackcontrol.o\
	devices/motors/imotor.o\
	devices/motors/cstepmotor.o\
	devices/motors/calgorithm.o\
	devices/encoder/iencoder.o\
	devices/encoder/ccancoder.o\
	devices/encoder/crs485coder.o\
	devices/encoder/csensorcounter.o\
	devices/switch/cproximityswitch.o\
	drivers/prussdrv/prussdrv.o\
	drivers/ccan.o\
	drivers/cgpio.o\
	drivers/ci2c.o\
	drivers/cpru.o\
	drivers/cpwm.o\
	drivers/cserial.o\
	drivers/cserialboost.o\
	drivers/iserial.o\
	network/modbus/modbus.o\
	network/modbus/modbus-data.o\
	network/modbus/modbus-tcp.o\
	network/cdata-mapping.o\
	network/ccontrol.o\
	network/cmodbus.o\
	network/cnetwork.o\
	network/cparse.o\
	network/cselect.o\
	parts/cfocuspart.o\
	parts/cpanpart.o\
	parts/ctiltpart.o\
	parts/czoompart.o\
	parts/iparts.o\
	robot/crobot.o\
	robot/csystem.o\
	robot/camendpulse.o\
	robot/cdevpulses.o\
	robot/cmanagepulse.o\
	robot/csyspulses.o\
	robot/cconfig.o\
	task/local/cccd.o\
	task/local/crefresh.o\
	task/cfocustask.o\
	task/cpantask.o\
	task/csystask.o\
	task/ctilttask.o\
	task/czoomtask.o\
	task/itask.o\
	utils/cconverter.o\
	utils/cdebug.o\
	utils/cdelay.o\
	utils/casynchrtimer.o\
	utils/casynctimer.o\
	utils/ctaskthread.o\
	utils/cprintattr.o

DELETE= bin/UdpServer\
	bin/UdpClient\
	bin/ModbusClient

TARGET=bin/ModbusServer

INC=-I./library/include 
BBB=LINUX
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	LIB=-L/usr/local/lib
	CFLAGS+=-DDLP_DEBUG -DDLP_LINUX
else
	CXX =arm-linux-g++
	CFLAGS+=-DDLP_DEBUG -DDLP_ARM_LINX 
	LIB=-L./library/lib
endif
CFLAGS += -O2 -g -Wall -lboost_thread -lboost_system -lboost_atomic -lpthread -lboost_chrono -lboost_regex

all:demo devices drivers network parts robot task utils  $(TARGET)
demo:
	$(MAKE) -C demo
drivers:
	$(MAKE) -C drivers
devices:
	$(MAKE) -C devices
network:
	$(MAKE) -C network
parts:
	$(MAKE) -C parts
robot:
	$(MAKE) -C robot
task:
	$(MAKE) -C task
utils:
	$(MAKE) -C utils
$(TARGET):$(OBJ)
	$(CXX) -o $(TARGET)  $(OBJ) $(INC) $(LIB) $(CFLAGS)  
%.o:%.cpp
	$(CXX) -c $(INC) $(LIB) $(CFLAGS) $< 

.PHONY:demo devices drivers network parts robot task udp utils  $(TARGET)
clean:
	rm $(OBJ) $(TARGET) $(DELETE) 
