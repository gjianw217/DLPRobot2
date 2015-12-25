###########################################
# network Makefile
#                            By Guo Jianwei
#                                2015-06-10
#                  EMAIL: gjianw217@163.com
###########################################
OBJCXX=cdata-mapping.o\
    cmodbus.o\
    ccontrol.o\
    cnetwork.o\
    cparse.o\
    cselect.o
OBJ= modbus/modbus.o\
     modbus/modbus-data.o\
     modbus/modbus-tcp.o
INC=-I../library/include
BBB=LINUX
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CC=gcc
	CFLAGS+=-DDLP_DEBUG -DLP_LINUX 
else
	CXX=arm-linux-g++
	CC=arm-linux-gcc
	CFLAGS+=-DDLP_DEBUG -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ) $(OBJCXX)
$(OBJ):%.o:%.c
	$(CC) -c $(CFLAGS)  $(INC) $< -o $@ 
$(OBJCXX):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 
