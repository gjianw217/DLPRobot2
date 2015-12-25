###########################################
# utils Makefile
#                            By Guo Jianwei
#                                2015-09-30
#                  EMAIL: gjianw217@163.com
###########################################
OBJ=   cdebug.o\
	cconverter.o\
	cdelay.o\
	casynchrtimer.o\
	casynctimer.o\
	ctaskthread.o\
	cprintattr.o
INC=-I../library/include
BBB=LINUX
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CFLAGS+=-DDLP_DEBUG -DDLP_LINUX 
else
	CXX=arm-linux-g++
	CFLAGS+=-DDLP_DEBUG -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ)
$(OBJ):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 

