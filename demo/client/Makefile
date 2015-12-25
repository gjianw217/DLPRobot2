###########################################
# demo/client Makefile
#                            By Guo Jianwei
#                                2015-10-12
#                  EMAIL: gjianw217@163.com
###########################################
OBJ1=modbus-client.c
TARGET1=../../bin/ModbusClient

INC=-I../../library/include
LIB=-L/usr/local/lib

CC=gcc
CFLAGS += -O2 -g -Wall
CLFLAGS = -lmodbus

BBB=LINUX
ifeq ($(BBB),ARM)
	CFLAGS += -DDLP_ARM_LINUX
endif
#all:$(TARGET1)
$(TARGET1):
	$(CC) -o $(TARGET1) $(OBJ1) $(CFLAGS) $(CLFLAGS) $(INC) $(LIB) 
clean:
	rm -rf $(TARGET1)
