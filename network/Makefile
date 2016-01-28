###########################################
# network Makefile
#                            By Guo Jianwei
#                                2016-01-28
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
b=MYDEBUG
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CC=gcc
	CFLAGS+=-D$(b) -DLP_LINUX 
else
	CXX=arm-linux-g++
	CC=arm-linux-gcc
	CFLAGS+=-D$(b) -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ) $(OBJCXX)
$(OBJ):%.o:%.c
	$(CC) -c $(CFLAGS)  $(INC) $< -o $@ 
$(OBJCXX):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 
