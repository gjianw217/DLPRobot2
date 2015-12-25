###########################################
# drivers Makefile
#                            By Guo Jianwei
#                                2015-09-29
#                  EMAIL: gjianw217@163.com
###########################################
OBJCXX=ccan.o\
	cgpio.o\
	ci2c.o\
	cpru.o\
	cpwm.o\
	cserial.o\
	cserialboost.o\
	iserial.o

OBJ= prussdrv/prussdrv.o
INC=-I../library/include
BBB=LINUX
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CC=gcc
	CFLAGS+=-DDLP_DEBUG -DDLP_LINUX 
else
	CXX=arm-linux-g++
	CC=arm-linux-gcc
	CFLAGS+=-DDLP_DEBUG -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ) $(OBJCXX)
$(OBJCXX):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 
$(OBJ):%.o:%.c
	$(CC) -c $(CFLAGS)  $(INC) $< -o $@ 
