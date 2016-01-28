###########################################
# task Makefile
#                            By Guo Jianwei
#                                2016-01-28
#                  EMAIL: gjianw217@163.com
###########################################
OBJ=cfocustask.o\
    cpantask.o\
    csystask.o\
    ctilttask.o\
    czoomtask.o\
    local/cccd.o\
    local/crefresh.o\
    itask.o
INC=-I../library/include
BBB=LINUX
b=MYDEBUG
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CFLAGS+=-D$(b) -DLP_LINUX 
else
	CXX=arm-linux-g++
	CFLAGS+=-D$(b) -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ)
$(OBJ):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 

