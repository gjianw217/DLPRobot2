###########################################
# drivers Makefile
#                            By Guo Jianwei
#                                2016-01-28
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
b=MYDEBUG
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CC=gcc
	CFLAGS+=-D$(b) -DDLP_LINUX 
else
	CXX=arm-linux-g++
	CC=arm-linux-gcc
	CFLAGS+=-D$(b) -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ) $(OBJCXX)
$(OBJCXX):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 
$(OBJ):%.o:%.c
	$(CC) -c $(CFLAGS)  $(INC) $< -o $@ 
