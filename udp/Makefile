###########################################
# udp Makefile
#                            By Guo Jianwei
#                                2015-06-10
#                  EMAIL: gjianw217@163.com
###########################################
TARGET1 = ../RobotCodeBlock/bin/arm-Debug/UdpServer
TARGET2 = ../test/UdpClient

OBJ1=cudpserver.o\
     cipserver.o\
     ../robot/cconfig.o\
     ../utils/debug.o\
     udpServer.o
OBJ2=cudpclient.cpp\
     udpClient.cpp
INC=-I../library/include -I../serialization/
BBB=LINUX
CFLAGS=$(CFLAG)
ifeq ($(BBB),LINUX)
	CXX=g++
	CFLAGS+=-DDLP_DEBUG -DDLP_LINUX 
else
	CXX=arm-linux-g++
	CFLAGS+=-DDLP_DEBUG -DDLP_ARM_LINUX
	LIB=-L../library/lib/
endif
CC =g++
CFLAGS += -O2 -g -Wall -lboost_system -lboost_regex -lpthread
all:$(TARGET1) $(TARGET2) 
$(TARGET1):$(OBJ1)
	$(CXX) -o $(TARGET1) $(OBJ1)  $(CFLAGS) $(INC) $(LIB)
$(TARGET2):$(OBJ2)
	$(CC) -o $(TARGET2) $(OBJ2) $(CFLAGS) $(INC) 
%.o:%.cpp
	$(CXX) -c $(INC) $(LIB) $(CFLAGG) $<
clean:
	-rm -f $(TARGET1) $(TARGET2) *.o
