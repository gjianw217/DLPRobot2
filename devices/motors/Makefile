###########################################
# devices/motors Makefile
#                            By Guo Jianwei
#                                2016-01-28
#                  EMAIL: gjianw217@163.com
###########################################
OBJ=cdirection.o\
	imotor.o\
   	cstepmotor.o\
	calgorithm.o\
	correction/camend.o\
	correction/camendmotor.o\
	correction/ccontrolmotor.o\
	correction/cdrivermotor.o\
	algorithm/irotation.o\
	algorithm/ctestrotation.o\
	algorithm/crotation360.o\
	algorithm/crotation720.o\
	algorithm/crotationany.o\
	algorithm/icurve.o\
	algorithm/ctestcurve.o\
	algorithm/clcurve.o\
	algorithm/ctcurve.o\
	algorithm/cscurve.o\
	algorithm/cbeziercurve.o

INC=-I../../library/include
BBB=LINUX
b=MYDEBUG
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CFLAGS+=-D$(b) -DDLP_LINUX 
else
	CXX=arm-linux-g++
	CFLAGS+=-D$(b) -DDLP_ARM_LINUX
endif

CFLAGS += -O2 -g -Wall
all:$(OBJ)
$(OBJ):%.o:%.cpp
	$(CXX) -c $(CFLAGS)  $(INC) $< -o $@ 

