###########################################
# parts Makefile
#                            By Guo Jianwei
#                                2015-09-29
#                  EMAIL: gjianw217@163.com
###########################################
OBJ= iparts.o\
	cfocuspart.o\
	czoompart.o\
	cpanpart.o\
	ctiltpart.o
INC=-I../library/include
BBB=LINUX
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CFLAGS+=-DDLP_DEBUG -DLP_LINUX 
else
	CXX=arm-linux-g++
	CFLAGS+=-DDLP_DEBUG -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ)
$(OBJ):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 
